/**
 * @brief 底盘控制 发布者的实现
 * @file SpeedControlSet_pub.cpp
 * @author szf
 *
 * @addtogroup src
 */

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
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <ros/console.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
#include<robot_pose_ekf/GetStatus.h>
#include<robot_pose_ekf/GetStatusRequest.h>

#define PI 3.141592653
#define P_speed_y -0
#define P_pose_y -1.31
#define P_speed_x -0
#define P_pose_x -0
#define P_pose_z 1.7

/**
 * @brief 实例化发布者、订阅者对象
 * 
 */
ros::Publisher path_pub;
ros::Publisher path_ref_pub; 
ros::Publisher send_publisher;
ros::Publisher ref_publisher;
ros::Subscriber xbox_sub;
ros::Subscriber odomSub;
ros::Subscriber path_ekf;
/**
 * @brief 创建变量
 * 
 */

nav_msgs::Path path_real;//用来接收T265的里程计数据，便于在rviz可视化
nav_msgs::Path path_reference;//用来在rviz中画参考路径
geometry_msgs::Quaternion orientation;//用来接收T265的位姿数据
geometry_msgs::Quaternion orientation_ref;//暂时没用到
mavros_msgs::SpeedControlSet_sub pub;//自定义的mavros消息
mavros_msgs::SpeedControlSet_sub ref;
bool safe = true;//用来设置急刹车
float speed[3];
float pose[3];//用来接收T265卡尔曼滤波后的里程计数据，做闭环控制
int t = 0;//时间

/**
 * @brief callbacks
 * 
 * @param xbox 
 */

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

    speed[0] = odom -> twist.twist.linear.x;
    speed[1] = odom -> twist.twist.linear.y;
    speed[2] = odom -> twist.twist.linear.z;

    //获取四元数
    orientation.z = odom -> pose.pose.orientation.z;

}
void efk_Callback(const geometry_msgs::PoseWithCovarianceStampedConstPtr& efk)
{
    //获取当前里程计数据
    pose[0] = efk -> pose.pose.position.x;
    pose[1] = efk -> pose.pose.position.y;
    pose[2] = efk -> pose.pose.position.z;
    ROS_INFO("pose_x = %f",pose[0]);
    //获取四元数
    orientation.z = efk -> pose.pose.orientation.w;

}

/**
 * @brief 在rviz中画参考路径
 * 
 */
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
    double vx = PI * 0.25;//真实最大速度
    double vy = PI * PI * 0.1;//最大速度
    double vth = 1;
    ros::Rate loop_rate(50);
    while (ros::ok())
    {
        ROS_INFO("drawing...");
        t1 ++;
        current_time = ros::Time::now();
 
        //路径

        double dt = 0.02;
        double delta_x = vx * sin(PI / 16 * th) * dt;
        double delta_y = vy * cos(x * PI/2) * sin(PI/16 * th) * dt;
        double delta_th = vth * dt;
        if(t1>=800)
        {
            vy = -PI * PI * 0.1;
        }
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

/**
 * @brief 主函数
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
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

    //订阅t265里程计话题信息，并发布
    path_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory", 10, true);
    odomSub = speed_control_nh.subscribe<nav_msgs::Odometry>("/camera/odom/sample", 10, odomCallback); 

    //订阅扩展卡尔曼滤波后的话题
    path_ekf = speed_control_nh.subscribe<geometry_msgs::PoseWithCovarianceStamped>("robot_pose_ekf/odom_combined",10,efk_Callback);

    //订阅xbox
    xbox_sub = speed_control_nh.subscribe<geometry_msgs::Twist>("xbox",10,xboxCallback);
   
    //初始化被发布消息
    pub.vw_set_sub= 0;
    pub.vx_set_sub = 0.5;
    pub.vy_set_sub = 0;
   
    //初始化参考消息
    ref.vx_set_sub = 0.5;
    ref.vy_set_sub = 0;
    ref.vw_set_sub = 0;
    ref.x_set_sub = 0;
    ref.y_set_sub = 0;
  
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
        //前半程
        if(t < 800)
        {
            //ref
            ref.vx_set_sub = PI/4 * sin(PI/16 * t * 0.02);
            ref.vy_set_sub = PI * PI * 0.1 * sin(PI/16*t*0.02) * cos(PI/2*ref.x_set_sub) ;
            ref.vw_set_sub = 0;
            ref.x_set_sub = PI/4 * sin(PI/16 * t*0.02) * t*0.02;
            ref.y_set_sub = 0.8*sin(PI/2*ref.x_set_sub);
            ref_publisher.publish(ref);
            //pub
            pub.vx_set_sub = ref.vx_set_sub + P_pose_x * (pose[0] - ref.x_set_sub);//还未调参
            pub.vy_set_sub = ref.vy_set_sub 
                            + P_pose_y * (pose[1] - ref.y_set_sub);//闭环控制,修正估计 最优估计
            pub.vw_set_sub = ref.vw_set_sub + P_pose_z * (orientation.z - ref.vw_set_sub);

            //发布速度控制底盘
            send_publisher.publish(pub);
            ROS_INFO("control successfully!");
        }
        //后半程
        else if(t > 800 && t <1600)
        {
            //ref
            ref.vx_set_sub = PI/4 * sin(PI/16 * t * 0.02);
            ref.vy_set_sub = -PI * PI * 0.1 * sin(PI/16*t*0.02) * cos(PI/2*ref.x_set_sub) ;
            ref.vw_set_sub = 0;
            ref.x_set_sub = PI/4 * sin(PI/16 * t*0.02) * t*0.02;
            ref.y_set_sub = 0.8*sin(PI/2*ref.x_set_sub);
            ref_publisher.publish(ref);
            //pub
            pub.vx_set_sub = ref.vx_set_sub + P_pose_x * (pose[0] - ref.x_set_sub);//还未调参
            pub.vy_set_sub = ref.vy_set_sub 
                            + P_pose_y * (pose[1] - ref.y_set_sub);//闭环控制,修正估计 最优估计
            pub.vw_set_sub = ref.vw_set_sub + P_pose_z * (orientation.z - ref.vw_set_sub);
            //发布速度控制底盘
            send_publisher.publish(pub);
            ROS_INFO("control successfully!");
        }
        //完成任务后停车
        else if(t >= 1600 )
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

