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
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <robot_pose_ekf/GetStatus.h>
#include <robot_pose_ekf/GetStatusRequest.h>
#include <stdio.h>
#include <math.h>
#include "mavros_msgs/Posture.h"
#include "amtraj/am_traj.hpp"
#include <ros/time.h>
#include <ros/duration.h>

#define FP64 double
#define PI 3.141592653
#define P_speed_y -0
#define P_pose_y -0.45
#define P_speed_x -0
#define P_pose_x -0.4
#define P_pose_z 1

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
ros::Subscriber posture_sub;

/**
 * @brief 创建变量
 *
 */
nav_msgs::Path path_real;                  //用来接收T265的里程计数据，便于在rviz可视化
nav_msgs::Path path_reference;             //用来在rviz中画参考路径
geometry_msgs::Quaternion orientation;     //用来接收T265的位姿数据
geometry_msgs::Quaternion orientation_ref; //暂时没用到
mavros_msgs::SpeedControlSet_sub pub;      //自定义的mavros消息
mavros_msgs::SpeedControlSet_sub ref;
bool safe = true; //用来设置急刹车
float speed[3];
float pose[3]; //用来接收T265卡尔曼滤波后的里程计数据，做闭环控制
int t = 0;     //时间
typedef struct
{
    /* data */
    double v_cur;
    double s_cur;
    double t_sum;
} current;

/**
 * @brief callbacks
 *
 * @param xbox
 */

void xboxCallback(const geometry_msgs::Twist::ConstPtr &xbox)
{
    if (xbox->angular.z != 0 || speed[0] > 1 || speed[1] > 1 || speed[2] > 1)
    {
        safe = false;
    }
    else if (xbox->angular.z == 0)
    {
        safe = true;
    }
}

void odomCallback(const nav_msgs::Odometry::ConstPtr &odom)
{
    //里程计path
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.pose.position.x = odom->pose.pose.position.x;
    this_pose_stamped.pose.position.y = odom->pose.pose.position.y;
    this_pose_stamped.pose.position.z = odom->pose.pose.position.z;

    this_pose_stamped.pose.orientation = odom->pose.pose.orientation;

    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.header.frame_id = "camera_odom_frame";

    path_real.poses.push_back(this_pose_stamped);

    path_real.header.stamp = ros::Time::now();
    path_real.header.frame_id = "camera_odom_frame";
    path_pub.publish(path_real);

    speed[0] = odom->twist.twist.linear.x;
    speed[1] = odom->twist.twist.linear.y;
    speed[2] = odom->twist.twist.linear.z;

    //获取四元数
    // orientation.z = odom -> pose.pose.orientation.z;
}
void efk_Callback(const geometry_msgs::PoseWithCovarianceStampedConstPtr &efk)
{
    //获取当前里程计数据
    pose[0] = efk->pose.pose.position.x;
    pose[1] = efk->pose.pose.position.y;
    pose[2] = efk->pose.pose.position.z;
    ROS_INFO("pose_x = %f", pose[0]);
    //获取四元数
    orientation.z = efk->pose.pose.orientation.z;
}
void Poseture_Callback(const mavros_msgs::PostureConstPtr &poseture)
{
    pose[0] = poseture->pos_x_state;
    pose[1] = poseture->pos_y_state;
    orientation.z = poseture->zangle_state;
}
/**
 * @brief S型曲线 速度规划函数
 *
 * @param t 当前时间 单位与速度等一致
 * @param v_start 初速度
 * @param v_end 末速度
 * @param s_target 目标距离
 * @param v_target 最大速度
 * @param a_target 最大加速度
 * @param d_target 最大减速度
 * @param j_max 目标加加速度(小于系统能受到的最大冲击，反映了系统的柔性，柔性越大，过冲越大)
 */

current S_type_Speed_Curve_Planning(double t, FP64 v_start, FP64 v_end, FP64 s_target, FP64 v_target, FP64 a_target, FP64 d_target, FP64 j_max)
{
    /****************************  定义相关变量   ***********************/
    FP64 v_max = 0; //最大速度(有匀速段时,v_max = v_target)

    FP64 L;      //算出的位移量
    FP64 v_real; //实际的最大速度

    FP64 s_max; // L>s_target时候规划的位移

    /*可以根据需要修改*/

    FP64 t_aver; //匀速区时间
    FP64 t1;     //加加速时间
    FP64 t2;     //匀加速时间
    FP64 t3;     //减加速时间
    FP64 t4;     //匀速运行时间
    FP64 t5;
    FP64 t6;
    FP64 t7;

    FP64 v1;
    FP64 v2;
    FP64 v3;
    FP64 v4;
    FP64 v5;
    FP64 v6;
    FP64 v7;

    FP64 a_max; //加速度最大值(拥有匀加速段时 a_max = a_target)
    FP64 d_max;

    FP64 s1; //加加速位移 s1
    FP64 s2; //匀加速位移 s2
    FP64 s3; //减加速位移 s3
    FP64 s4; //匀速位移   s4
    FP64 s5; //加减速位移 s5
    FP64 s6; //匀减速位移 s6
    FP64 s7; //减减速位移 s7

    FP64 s_acc; //加速区位移
    FP64 s_dec; //减速区位移

    FP64 j_cur; //当前加加速度
    FP64 a_cur; //当前加速度
    current cur = {0, 0, 0};
    FP64 v_down;

    FP64 v_low;
    FP64 v_high;

    short int end_count = 0;
    short int flag = 0;
    short int flag1 = 0;
    short int count = 0;

    if (v_max == 0) //只有第一遍
    {
        /***********************************根据目标速度,加速度,加加速度等规划出加速区和减速区******************/
        if ((v_target - v_start) > a_target * a_target / j_max) //匀加速段
        {
            a_max = a_target;

            t1 = a_max / j_max;
            v1 = v_start + 0.5 * j_max * t1 * t1;
            s1 = v_start * t1 + (j_max * t1 * t1 * t1) / 6;

            t2 = (v_target - v_start) / a_max - t1;
            v2 = v1 + a_target * t2;
            s2 = v1 * t2 + 0.5 * a_max * t2 * t2;

            t3 = t1;
            v3 = v2 + a_max * t3 - 0.5 * j_max * t3 * t3;
            s3 = v2 * t3 + j_max * t3 * t3 * t3 / 3;
        }
        else
        {
            a_max = sqrt((v_target - v_start) * j_max);
            t1 = sqrt((v_target - v_start) / j_max);
            s1 = v_start * t1 + (j_max * t1 * t1 * t1) / 6;
            v1 = v_start + 0.5 * j_max * t1 * t1;
            t2 = 0;
            v2 = v1;
            s2 = 0;
            t3 = t1;
            s3 = v2 * t3 + j_max * t3 * t3 * t3 / 3;
            v3 = v2 + a_max * t3 - 0.5 * j_max * t3 * t3;
        }
        if (v_target - v_end > (d_target * d_target) / j_max)
        {
            d_max = d_target;

            t7 = d_max / j_max;
            s7 = v_end * t7 + (j_max * t7 * t7 * t7) / 6;
            v6 = v_end + 0.5 * j_max * t7 * t7;
            t6 = (v_target - v_end) / d_max - t7;
            s6 = v6 * t6 + 0.5 * d_max * t6 * t6;
            v5 = v6 + d_target * t6;
            t5 = t7;
            s5 = v5 * t5 + j_max * t5 * t5 * t5 / 3;
        }
        else
        {
            d_max = sqrt((v_target - v_end) * j_max);
            t7 = sqrt((v_target - v_end) / j_max);
            s7 = v_end * t7 + (j_max * t7 * t7 * t7) / 6;
            v6 = v_end + 0.5 * j_max * t7 * t7;
            t6 = 0;
            s6 = 0;
            t5 = t7;
            v5 = v6;
            s5 = v3 * t5 - j_max * t5 * t5 * t5 / 6;
        }

        L = 0.5 * ((v_start + v_target) * (t1 + t2 + t3) + (v_end + v_target) * (t5 + t6 + t7));
    }

    if (L >= s_target && v_max == 0) //如果 L >= s_target,那么达不到目标速度,需要规划出实际最大速度,只有第一遍循环会进这个程序
    {
        t4 = 0;
        s4 = 0;
        v4 = v3;

        v_high = v_target;

        /*初速度较大*/
        if (v_start > v_end)
        {
            v_low = v_start;
        }
        /*末速度较大*/
        else if (v_end > v_start)
        {
            v_low = v_end;
            end_count += 1;
        }

        v_max = 0.5 * (v_low + v_high);
    }
    /*如果 L < s_target 那么可以正常进行规划(有匀速段),标志位flag1=1*/
    else if (L < s_target)
    {
        v_max = v_target;
        flag1 = 1;
    }

    /***********************************  根据二分处理后的速度再算位移  ******************/
    if ((v_max - v_start) > a_target * a_target / j_max) //匀加速段
    {
        a_max = a_target;

        t1 = a_max / j_max;
        v1 = v_start + 0.5 * j_max * t1 * t1;
        s1 = v_start * t1 + (j_max * t1 * t1 * t1) / 6;

        t2 = (v_max - v_start) / a_max - t1;
        v2 = v1 + a_target * t2;
        s2 = v1 * t2 + 0.5 * a_max * t2 * t2;

        t3 = t1;
        v3 = v2 + a_max * t3 - 0.5 * j_max * t3 * t3;
        s3 = v2 * t3 + j_max * t3 * t3 * t3 / 3;
    }
    else
    {
        a_max = sqrt((v_max - v_start) * j_max);
        t1 = sqrt((v_max - v_start) / j_max);
        s1 = v_start * t1 + (j_max * t1 * t1 * t1) / 6;
        v1 = v_start + 0.5 * j_max * t1 * t1;
        t2 = 0;
        v2 = v1;
        s2 = 0;
        t3 = t1;
        s3 = v2 * t3 + j_max * t3 * t3 * t3 / 3;
        v3 = v2 + a_max * t3 - 0.5 * j_max * t3 * t3;
    }
    if (v_max - v_end > (d_target * d_target) / j_max) //匀减速段
    {
        d_max = d_target;

        t7 = d_max / j_max;
        s7 = v_end * t7 + (j_max * t7 * t7 * t7) / 6;
        v6 = v_end + 0.5 * j_max * t7 * t7;
        t6 = (v_max - v_end) / d_max - t7;
        s6 = v6 * t6 + 0.5 * d_max * t6 * t6;
        v5 = v6 + d_target * t6;
        t5 = t7;
        s5 = v5 * t5 + j_max * t5 * t5 * t5 / 3;
    }
    else
    {
        d_max = sqrt((v_max - v_end) * j_max);
        t7 = sqrt((v_max - v_end) / j_max);
        s7 = v_end * t7 + (j_max * t7 * t7 * t7) / 6;
        v6 = v_end + 0.5 * j_max * t7 * t7;
        t6 = 0;
        s6 = 0;
        t5 = t7;
        v5 = v6;
        s5 = v3 * t5 - j_max * t5 * t5 * t5 / 6;
    }

    s_max = s1 + s2 + s3 + s5 + s6 + s7; // s_max是二分后的位移

    /*二分后的位移无限接近目标位移,则标志位flag=1,开始规划*/
    if (s_max - s_target < 0.001 && s_max - s_target > 0)
    {
        flag = 1;
    }
    /*否则继续二分*/
    else
    {
        //二分法思想：改变上下限
        if (s_max < s_target) //如果规划出来的位移偏小
        {
            v_low = v_max;
        }
        else
        { //如果规划出来的位移偏大
            v_high = v_max;
        }
        v_max = 0.5 * (v_low + v_high);
    }

    /***********************************  只有在标志位置位时才规划  ******************/
    if (flag == 1 || flag1 == 1)
    {
        if (flag1 == 1)
        {
            /*正常进行规划*/
            t4 = (s_target - s1 - s2 - s3 - s5 - s6 - s7) / v_target; //本来应该是v_max,但这里为了避开二分法
            v4 = v3;
            s4 = v4 * t4;
        }
        else if (flag == 1)
        {
            t4 = 0;
            v4 = v3;
            s4 = 0;
        }

        cur.t_sum = t1 + t2 + t3 + t4 + t5 + t6 + t7;

        if (t >= 0 && t < t1)
        {
            j_cur = j_max;
            a_cur = j_cur * t;
            cur.v_cur = v_start + 0.5 * j_cur * t * t;
            cur.s_cur = v_start * t + j_cur * t * t * t / 6;
        }
        else if (t >= t1 && t < t1 + t2 && t2 != 0)
        {
            j_cur = 0;
            a_cur = a_max;
            cur.v_cur = v1 + a_cur * (t - t1);
            cur.s_cur = s1 + v1 * (t - t1) + 0.5 * a_cur * (t - t1) * (t - t1);
        }
        else if (t >= t1 + t2 && t < t1 + t2 + t3)
        {
            j_cur = -j_max;
            a_cur = a_max - j_max * (t - t1 - t2);
            cur.v_cur = v2 + a_max * (t - t1 - t2) - 0.5 * j_max * (t - t1 - t2) * (t - t1 - t2);
            cur.s_cur = s1 + s2 + v2 * (t - t1 - t2) + 0.5 * a_max * (t - t1 - t2) * (t - t1 - t2) - j_max * (t - t1 - t2) * (t - t1 - t2) * (t - t1 - t2) / 6;
        }
        else if (t >= t1 + t2 + t3 && t < t1 + t2 + t3 + t4 && t4 != 0)
        {
            j_cur = 0;
            a_cur = 0;
            cur.v_cur = v3;
            cur.s_cur = s1 + s2 + s3 + v3 * (t - t1 - t2 - t3);
        }
        else if (t >= t1 + t2 + t3 + t4 && t < t1 + t2 + t3 + t4 + t5)
        {
            j_cur = -j_max;
            a_cur = -j_max * (t - t1 - t2 - t3 - t4);
            cur.v_cur = v4 - 0.5 * j_max * (t - t1 - t2 - t3 - t4) * (t - t1 - t2 - t3 - t4);
            cur.s_cur = s1 + s2 + s3 + s4 + v4 * (t - t1 - t2 - t3 - t4) - j_max * (t - t1 - t2 - t3 - t4) * (t - t1 - t2 - t3 - t4) * (t - t1 - t2 - t3 - t4) / 6;
        }
        else if (t >= t1 + t2 + t3 + t4 + t5 && t < t1 + t2 + t3 + t4 + t5 + t6 && t6 != 0)
        {
            j_cur = 0;
            a_cur = -d_max;
            cur.v_cur = v5 - d_target * (t - t1 - t2 - t3 - t4 - t5);
            cur.s_cur = s1 + s2 + s3 + s4 + s5 + v5 * (t - t1 - t2 - t3 - t4 - t5) - 0.5 * d_target * (t - t1 - t2 - t3 - t4 - t5) * (t - t1 - t2 - t3 - t4 - t5);
        }
        else if (t >= t1 + t2 + t3 + t4 + t5 + t6 && t <= t1 + t2 + t3 + t4 + t5 + t6 + t7)
        {
            j_cur = j_max;
            a_cur = -d_max + j_max * (t - t1 - t2 - t3 - t4 - t5 - t6);
            cur.v_cur = v6 - d_max * (t - t1 - t2 - t3 - t4 - t5 - t6) + 0.5 * j_max * (t - t1 - t2 - t3 - t4 - t5 - t6) * (t - t1 - t2 - t3 - t4 - t5 - t6);
            cur.s_cur = s1 + s2 + s3 + s4 + s5 + s6 + v6 * (t - t1 - t2 - t3 - t4 - t5 - t6) - 0.5 * d_max * (t - t1 - t2 - t3 - t4 - t5 - t6) * (t - t1 - t2 - t3 - t4 - t5 - t6) + j_max * (t - t1 - t2 - t3 - t4 - t5 - t6) * (t - t1 - t2 - t3 - t4 - t5 - t6) * (t - t1 - t2 - t3 - t4 - t5 - t6) / 6;
        }
        else if (t > t1 + t2 + t3 + t4 + t5 + t6 + t7)
        {
            a_cur = 0;
            j_cur = 0;
            cur.v_cur = v_end;
        }
    }

    return cur;
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
    // nav_msgs::Path path;
    path_reference.header.stamp = current_time;
    path_reference.header.frame_id = "camera_odom_frame";

    double x = 0.0;
    double y = 0.0;
    double th = 0.0;
    double vx = PI * 0.25;     //真实最大速度
    double vy = PI * PI * 0.1; //最大速度
    double vth = 1;
    ros::Rate loop_rate(50);
    while (ros::ok())
    {
        ROS_INFO("drawing...");
        t1++;
        current_time = ros::Time::now();

        //路径

        double dt = 0.02;
        double delta_x = vx * sin(PI / 16 * th) * dt;
        double delta_y = vy * cos(x * PI / 2) * sin(PI / 16 * th) * dt;
        double delta_th = vth * dt;

        x += delta_x;
        if (t1 <= 800)
        {
            y += delta_y;
        }
        else if (t1 > 800)
        {
            y -= delta_y;
        }

        th += delta_th;

        geometry_msgs::PoseStamped this_pose_stamped;
        this_pose_stamped.pose.position.x = x;
        this_pose_stamped.pose.position.y = y;

        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th); //位姿，四元数与欧拉角的转化

        this_pose_stamped.pose.orientation.x = goal_quat.x;
        this_pose_stamped.pose.orientation.y = goal_quat.y;
        this_pose_stamped.pose.orientation.z = goal_quat.z;
        this_pose_stamped.pose.orientation.w = goal_quat.w;

        this_pose_stamped.header.stamp = current_time;
        this_pose_stamped.header.frame_id = "camera_odom_frame";
        path_reference.poses.push_back(this_pose_stamped);

        path_ref_pub.publish(path_reference);

        // check for incoming messages
        ros::spinOnce();

        last_time = current_time;
        loop_rate.sleep();
        if (t1 >= 1600)
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
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    //初始化节点
    ros::init(argc, argv, "SpeedControlPublisher");

    //创建ROS句柄
    ros::NodeHandle speed_control_nh;

    //创建发布者
    send_publisher = speed_control_nh.advertise<mavros_msgs::SpeedControlSet_sub>("/mavros/speed_control/send_topic", 1000);
    path_ref_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory_ref", 10, true);
    ref_publisher = speed_control_nh.advertise<mavros_msgs::SpeedControlSet_sub>("ref_topic", 1000);

    //订阅t265里程计话题信息，并发布
    path_pub = speed_control_nh.advertise<nav_msgs::Path>("trajectory", 10, true);
    odomSub = speed_control_nh.subscribe<nav_msgs::Odometry>("/camera/odom/sample", 10, odomCallback);

    //订阅扩展卡尔曼滤波后的话题
    path_ekf = speed_control_nh.subscribe<geometry_msgs::PoseWithCovarianceStamped>("robot_pose_ekf/odom_combined", 10, efk_Callback);

    //订阅xbox
    xbox_sub = speed_control_nh.subscribe<geometry_msgs::Twist>("xbox", 10, xboxCallback);
    //订阅码盘
    posture_sub = speed_control_nh.subscribe<mavros_msgs::Posture>("/mavros/posture/posture", 10, Poseture_Callback);
    //初始化被发布消息
    pub.vw_set_sub = 0;
    pub.vx_set_sub = 0;
    pub.vy_set_sub = 0;
    pub.x_set_sub = 0;
    pub.y_set_sub = 0;

    //初始化参考消息
    ref.vx_set_sub = 0;
    ref.vy_set_sub = 0;
    ref.vw_set_sub = 0;
    ref.x_set_sub = 0;
    ref.y_set_sub = 0;

    // 可视化
    // ShowPath_ref();

    //计算S曲线信息
    double t_reverse = S_type_Speed_Curve_Planning(0, 0, 0, 4, 0.25, 0.1, 0.2, 1).t_sum;
    double x_reverse = S_type_Speed_Curve_Planning(t_reverse, 0, 0, 4, 0.25, 0.1, 0.2, 1).s_cur;

    //组织被发布消息
    /*     ros::Rate r(50); //两次sleep之间0.02s
        while (ros::ok())
        {
            t++;
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
            if(t*0.02 < t_reverse)
            {
                //ref
                ref.vx_set_sub = S_type_Speed_Curve_Planning(t*0.02,0,0,4,0.25,0.1,0.2,1).v_cur;
                ref.vy_set_sub = 0.5*PI*cos(PI*ref.x_set_sub)*ref.vx_set_sub;
                ref.vw_set_sub = 0;
                ref.x_set_sub = S_type_Speed_Curve_Planning(t*0.02,0,0,4,0.25,0.1,0.2,1).s_cur;
                ref.y_set_sub = 0.5*sin(PI*ref.x_set_sub);
                ref_publisher.publish(ref);
                //pub
                pub.vx_set_sub = ref.vx_set_sub + P_pose_x * (pose[0] - ref.x_set_sub);//还未调参
                pub.vy_set_sub = ref.vy_set_sub
                                + P_pose_y * (pose[1] - ref.y_set_sub);//闭环控制,修正估计 最优估计
                pub.vw_set_sub = 0 + P_pose_z * (orientation.z - 0);

                //发布速度控制底盘
                send_publisher.publish(pub);
                ROS_INFO("control successfully!");
                ROS_INFO("x_reverse = %lf",x_reverse);
            }

            //后半程
            else if(t*0.02 >= t_reverse && t*0.02 < (t_reverse*2))
            {
                //ref
                ref.vx_set_sub = - S_type_Speed_Curve_Planning(t*0.02 - t_reverse,0,0,4,0.25,0.1,0.2,1).v_cur;
                ref.vy_set_sub = - 0.5*PI*cos(PI*ref.x_set_sub)*ref.vx_set_sub;
                ref.vw_set_sub = 0;
                ref.x_set_sub =x_reverse - S_type_Speed_Curve_Planning(t*0.02 - t_reverse,0,0,4,0.25,0.1,0.2,1).s_cur;
                ref.y_set_sub = - 0.5*sin(PI*(ref.x_set_sub));
                ref_publisher.publish(ref);
                //pub
                pub.vx_set_sub = ref.vx_set_sub + P_pose_x * (pose[0] - ref.x_set_sub);
                pub.vy_set_sub = ref.vy_set_sub
                                + P_pose_y * (pose[1] - ref.y_set_sub);
                pub.vw_set_sub = 0 + P_pose_z * (orientation.z - 0);
                //发布速度控制底盘
                send_publisher.publish(pub);
                ROS_INFO("control successfully!");
            }
            //完成任务后停车
            if(t*0.02 >= (t_reverse * 2))
            {
                pub.vw_set_sub = 0;
                pub.vx_set_sub = 0;
                pub.vy_set_sub = 0;
                send_publisher.publish(pub);
                ROS_INFO("control end!,t = %d,t_reverse = %lf,x_reverse = %lf",t,t_reverse,x_reverse);
                break;
            }



            r.sleep();
            ros::spinOnce();
        } */

    //创建轨迹生成对象
    AmTraj amTrajOpt(1024.0, 32.0, 1.0, 2.0, 2.0, 32, 0.02);

    //轨迹规划

    Eigen::Vector3d iV(2.0, 1.0, 0.0), fV(0.0, 0.0, 0.0);
    Eigen::Vector3d iA(0.0, 0.0, 2.0), fA(0.0, 0.0, 0.0); //规定航点处的速度和加速度

    std::vector<Eigen::Vector3d> wPs;
    wPs.emplace_back(0.0, 0.0, 0.0);
    wPs.emplace_back(4.0, 2.0, 1.0);
    wPs.emplace_back(9.0, 7.0, 5.0);
    wPs.emplace_back(1.0, 3.0, 2.0); //规定轨迹的固定航点

    Trajectory traj = amTrajOpt.genOptimalTrajDTC(wPs, iV, iA, fV, fA); //生成轨迹

    ros::Time begin = ros::Time::now();//初始时刻

    ros::Rate r(100);//100Hz
    while (ros::ok)
    {
        ros::Duration time = ros::Time::now() - begin;//时间

        pub.vw_set_sub = 0;
        pub.vx_set_sub = traj.getVel(time.toSec())(1);
        pub.vy_set_sub = traj.getVel(time.toSec())(2);
        pub.x_set_sub = traj.getPos(time.toSec())(1);
        pub.y_set_sub = traj.getPos(time.toSec())(2);

        send_publisher.publish(pub);

        if (time.toSec() > traj.getTotalDuration())
        {
            pub.vw_set_sub = 0;
            pub.vx_set_sub = 0;
            pub.vy_set_sub = 0;

            ROS_INFO("stop!");
            break;
        }

        r.sleep();
    }
}
