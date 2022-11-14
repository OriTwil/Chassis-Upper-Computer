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

#define PI 3.141592653
#define P_speed_y -0
#define P_pose_y -1.31
#define P_speed_x -0
#define P_pose_x -0
#define P_pose_z 1.7

ros::Publisher path_pub;
ros::Publisher path_ref_pub; 
ros::Publisher send_publisher;
ros::Publisher ref_publisher;
ros::Subscriber xbox_sub;
nav_msgs::Path path_real;
nav_msgs::Path path_reference;
float speed[3];
float pose[3];
geometry_msgs::Quaternion orientation;
geometry_msgs::Quaternion orientation_ref;
bool safe = true;


void xboxCallback(const geometry_msgs::Twist::ConstPtr& xbox)
{
    if(xbox->angular.z != 0 || speed[0] > 1 || speed[1] > 1 || speed[2] > 1)
    {
        safe = false;
    }
    else if(xbox->angular.z == 0)
    {
        safe = true;
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

    //获取当前里程计数据
    pose[0] = odom -> pose.pose.position.x;
    pose[1] = odom -> pose.pose.position.y;
    pose[2] = odom -> pose.pose.position.z;

    speed[0] = odom -> twist.twist.linear.x;
    speed[1] = odom -> twist.twist.linear.y;
    speed[2] = odom -> twist.twist.linear.z;
    //获取四元数
    orientation.z = odom -> pose.pose.orientation.z;

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
    double vx = 0.5;//真实速度0.25m/s
    double vy = 0.25;//最大速度0.2m/s
    double vth = 0.5;
    ros::Rate loop_rate(50);
    while (ros::ok())
    {
        ROS_INFO("drawing...");
        t1 ++;
        current_time = ros::Time::now();
        //compute odometry in a typical way given the velocities of the robot
        //路径
        if(t1 == 800)
        {
            vx = -vx;
        }

        double dt = 0.02;
        double delta_x = vx * dt;
        double delta_y = vy * PI * cos(th*PI/2) * dt;
        double delta_th = vth * dt;

        x += delta_x;
        y += delta_y;
        th += delta_th;

        geometry_msgs::PoseStamped this_pose_stamped;
        this_pose_stamped.pose.position.x = x;
        this_pose_stamped.pose.position.y = y;

        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th);//位姿，四元数与欧拉角的转化
        
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
        if(t1 >= 1600)
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
    ref_publisher = speed_control_nh.advertise<mavros_msgs::SpeedControlSet_sub>("ref_topic",1000);
    //订阅t265，并发布
    path_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory", 10, true);
    ros::Subscriber odomSub = speed_control_nh.subscribe<nav_msgs::Odometry>("/camera/odom/sample", 10, odomCallback);  //订阅t265里程计话题信息
    //订阅xbox
    xbox_sub = speed_control_nh.subscribe<geometry_msgs::Twist>("xbox",10,xboxCallback);
    //初始化被发布消息
    mavros_msgs::SpeedControlSet_sub pub;
    mavros_msgs::SpeedControlSet_sub ref;
    pub.vw_set_sub= 0;
    pub.vx_set_sub = 0.5;
    pub.vy_set_sub = 0;
    //初始化参考消息
    ref.vx_set_sub = 0.5;
    ref.vy_set_sub = 0;
    ref.vw_set_sub = 0;
    ref.x_set_sub = 0;
    ref.y_set_sub = 0;

    //时间
    int t = 0;
    //定初始方向
    orientation_ref.w = orientation.w;

    // 发布参考路径
    ShowPath_ref();
 
    //组织被发布消息
    ros::Rate r(50);//两次sleep之间0.02s
    while(ros::ok())
    {
        //时间
        t++;

        //紧急刹车
        if(safe != true)
        {
            pub.vw_set_sub = 0;
            pub.vx_set_sub = 0;
            pub.vy_set_sub = 0;
            send_publisher.publish(pub);
            ROS_INFO("emergency braking!");
            break;
        }
        //前半段时间
        if(t < 800)
        {
            //ref
            ref.vx_set_sub = 0.5;
            ref.vy_set_sub = 0.25 * PI*cos(t*0.02*PI/4);
            ref.vw_set_sub = 0;
            ref.x_set_sub = 0.5*t*0.02;
            ref.y_set_sub = sin(t*0.02*PI/4);
            ref_publisher.publish(ref);
            //pub
            pub.vx_set_sub = 0.5;
            pub.vy_set_sub = 0.25 * PI*cos(t*0.02*PI/4) 
                            + P_pose_y * (pose[1] - ref.y_set_sub);
            pub.vw_set_sub = 0 + P_pose_z * (orientation.z - 0);

            //发布速度控制底盘
            send_publisher.publish(pub);
            ROS_INFO("control successfully!");
        }
        else if(t == 800)
        {
            pub.vx_set_sub = -pub.vx_set_sub;
        }
        else if(t > 800 && t <1600)
        {
            //ref
            ref.vx_set_sub = -0.5;
            ref.vy_set_sub = 0.25 * PI*cos(t*0.02*PI/4);
            ref.vw_set_sub = 0;
            ref.x_set_sub = 8 - 0.5*(t-800)*0.02;
            ref.y_set_sub = sin(t*0.02*PI/4);
            ref_publisher.publish(ref);
            //pubs
            pub.vx_set_sub = -0.5;
            pub.vy_set_sub = 0.25 * PI*cos(t*0.02*PI/4) 
                            + P_pose_y * (pose[1] - ref.y_set_sub);
            pub.vw_set_sub = 0 + P_pose_z * (orientation.z - 0);
            //发布速度控制底盘
            send_publisher.publish(pub);
            ROS_INFO("control successfully!");
        }
        else if(t >= 800 )//完成任务后停车
        {
            pub.vw_set_sub = 0;
            pub.vx_set_sub = 0;
            pub.vy_set_sub = 0;
            send_publisher.publish(pub);
            ROS_INFO("control end!");
            break;
        }
        r.sleep();
        ros::spinOnce();


    } 
}

