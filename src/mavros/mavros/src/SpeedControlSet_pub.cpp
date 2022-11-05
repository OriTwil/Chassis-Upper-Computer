#include <ros/ros.h>
#include "mavros_msgs/SpeedControlSet_sub.h"
#include <mavros_msgs/SpeedControlStatus.h>
#include <mavros_msgs/SpeedControlSet.h>
#include <math.h>

#include <ros/console.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <ros/console.h>

#include<geometry_msgs/Twist.h>
#include<iostream>

#define PI 3.14159265
#define P_speed_y 0.001
#define P_pose_y 2
#define P_speed_x 0.001
#define P_pose_x 0.001

ros::Publisher path_pub;
ros::Publisher path_ref_pub; 
ros::Publisher send_publisher;
ros::Subscriber xbox_sub;
nav_msgs::Path path_real;
nav_msgs::Path path_reference;
float speed[3];
float pose[3];
float pose_cal[3];
int safe = 0;


void xboxCallback(const geometry_msgs::Twist::ConstPtr& xbox)
{
    if(xbox->angular.z != 0)
    {
        safe = 1;
    }
    else if(xbox->angular.z == 0)
    {
        safe = 0;
    }
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    //里程计path
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.pose.position.x = odom -> pose.pose.position.x;
    this_pose_stamped.pose.position.y = odom -> pose.pose.position.y;
    this_pose_stamped.pose.position.z = odom -> pose.pose.position.z;

    this_pose_stamped.pose.orientation = odom -> pose.pose.orientation;

    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id = "camera_odom_frame";

    path_real.poses.push_back(this_pose_stamped);

    path_real.header.stamp = ros::Time::now();
    path_real.header.frame_id = "camera_odom_frame";
    path_pub.publish(path_real);
    ROS_INFO("11111");
    // printf("path_pub");
    // printf("odom %.3lf %.3lf %.3lf\n", odom->pose.pose.position.x, odom->pose.pose.position.y, odom->pose.pose.position.z);
    //获取当前位姿进行
    pose[0] = odom -> pose.pose.position.x;
    pose[1] = odom -> pose.pose.position.y;
    pose[2] = odom -> pose.pose.position.z;

    speed[0] = odom -> twist.twist.linear.x;
    speed[1] = odom -> twist.twist.linear.y;
    speed[2] = odom -> twist.twist.linear.z;
}

void ShowPath_ref()
{
     
    int t1 = 0;
    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();
    //nav_msgs::Path path;
    path_reference.header.stamp=current_time;
    path_reference.header.frame_id="camera_odom_frame";

    double x = 0.0;
    double y = 0.0;
    double th = 0.0;
    double vx = 0.0520;
    double vy = 0.0260;
    double vth = 0.2;
    ros::Rate loop_rate(50);
    while (ros::ok())
    {
        ROS_INFO("drawing...");
        t1 ++;
        current_time = ros::Time::now();
        //compute odometry in a typical way given the velocities of the robot
        //路径
        if(t1 == 720)
        {
            vy = -vy;
        }

        double dt = 0.1;
        double delta_x = vx * cos(th*50*PI/180) * dt;
        double delta_y = vy * dt;
        double delta_th = vth * dt;

        x += delta_x;
        y += delta_y;
        th += delta_th;

        geometry_msgs::PoseStamped this_pose_stamped;
        this_pose_stamped.pose.position.x = x;
        this_pose_stamped.pose.position.y = y;

        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th);
        this_pose_stamped.pose.orientation.x = goal_quat.x;
        this_pose_stamped.pose.orientation.y = goal_quat.y;
        this_pose_stamped.pose.orientation.z = goal_quat.z;
        this_pose_stamped.pose.orientation.w = goal_quat.w;

        this_pose_stamped.header.stamp=current_time;
        this_pose_stamped.header.frame_id="camera_odom_frame";
        path_reference.poses.push_back(this_pose_stamped);

        path_ref_pub.publish(path_reference);

        // check for incoming messages
        ros::spinOnce();               

        last_time = current_time;
        loop_rate.sleep();
        if(t1 >= 1440)
        {
            break;
        }
    }
}


int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");

    //初始化节点
    ros::init(argc,argv,"SpeedControlPublisher");

    //创建ROS句柄
    ros::NodeHandle speed_control_nh;

    //创建发布者
    send_publisher = speed_control_nh.advertise<mavros_msgs::SpeedControlSet_sub>("/mavros/speed_control/send_topic",1000);
    path_ref_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory_ref", 10, true);
    //订阅t265，并发布
    path_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory", 10, true);
    ros::Subscriber odomSub = speed_control_nh.subscribe<nav_msgs::Odometry>("/camera/odom/sample", 10, odomCallback);  //订阅t265里程计话题信息
    //订阅xbox
    xbox_sub = speed_control_nh.subscribe<geometry_msgs::Twist>("xbox",10,xboxCallback);
    //初始化被发布消息
    mavros_msgs::SpeedControlSet_sub pub;
    pub.vw_set_sub= 0;
    pub.vx_set_sub = 150;
    pub.vy_set_sub = 0;
   
    //时间
    int t = 0;

    //初始化位置坐标为零
    for(int i = 0;i<3;i++)
    {
        pose_cal[i] = 0; 
    }
 
    // 发布参考路径
    ShowPath_ref();
 
    //组织被发布消息
    ros::Rate r(50);//两次sleep之间0.02s
    while(ros::ok())
    {
        //急刹车
        if(safe != 0)
        {
            pub.vw_set_sub = 0;
            pub.vx_set_sub = 0;
            pub.vy_set_sub = 0;
            send_publisher.publish(pub);
            ROS_INFO("publish end!");
            break;
        }
        //x方向，两个周期时掉头
        if(t % 720 == 0)
        {
            pub.vx_set_sub = -pub.vx_set_sub;
        }
        //时间
        t++;
        //计算理论位置
        // pose_cal[1] += pub.vy_set_sub * 0.000413 * 0.02 ;//理论y位置(m)
        // pose_cal[0] += pub.vx_set_sub * 0.000413 * 0.02 ;//理论x位置(m)
        // pub.vx_set_sub =  pub.vx_set_sub 
        //                 + P_speed_x * (pub.vx_set_sub - speed[1] * 1200)
        //                 + P_pose_x * (pose[1] - pose_cal[0]);//x方向速度，保持恒定；根据速度位置闭环控制
        pub.vy_set_sub = P_pose_y * (pose[2] - 300*sin(PI*t/180));//y方向速度，余弦函数;根据速度位置闭环控制
        // pub.vy_set_sub =  cos(t*PI/180) * 300;
        //发布速度控制底盘
        send_publisher.publish(pub);
        ROS_INFO("publish success!");
        //完成任务后停车
        if(t >= 1440 )
        {
            pub.vw_set_sub = 0;
            pub.vx_set_sub = 0;
            pub.vy_set_sub = 0;
            send_publisher.publish(pub);
            ROS_INFO("publish end!");
            break;
        }
        r.sleep();
        ros::spinOnce();


    } 
}

