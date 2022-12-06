#include "ros/ros.h"
#include "amtraj/am_traj.hpp"
#include "geometry_msgs/PoseStamped.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <vector>
#include <string>


using namespace Eigen;
using namespace std;
using namespace ros;

class Config
{
    public:
        Config(const ros::NodeHandle &nh_priv)
        {
            nh_priv.getParam("TrajectoryTopic", trajectoryTopic);
            nh_priv.getParam("WayPointsTopic", wayPointsTopic);
            nh_priv.getParam("RouteTopic", routeTopic);
            nh_priv.getParam("AccTopic", accTopic);
            nh_priv.getParam("FrameName", frameName);
            nh_priv.getParam("WeightT", weightT);
            nh_priv.getParam("WeightAcc", weightAcc);
            nh_priv.getParam("WeightJerk", weightJerk);
            nh_priv.getParam("MaxAccRate", maxAccRate);
            nh_priv.getParam("MaxVelRate", maxVelRate);
            nh_priv.getParam("Iterations", iterations);
            nh_priv.getParam("Epsilon", epsilon);
        }
    // Advertised Topics
    string trajectoryTopic;
    string wayPointsTopic;
    string routeTopic;
    string accTopic;
    // Frame Name
    std::string frameName;
    // Params
    double weightT;
    double weightAcc;
    double weightJerk;
    double maxAccRate;
    double maxVelRate;
    int iterations;
    double epsilon;
};

class Visualizer                //可视化工具   Marker标记
{
public:
    Visualizer(const Config &conf, ros::NodeHandle &nh) : config(conf)
    {
        trajectoryPub = nh.advertise<visualization_msgs::Marker>(config.trajectoryTopic, 1);
        wayPointsPub = nh.advertise<visualization_msgs::Marker>(config.wayPointsTopic, 1);
        routePub = nh.advertise<visualization_msgs::Marker>(config.routeTopic, 1);
        accPub = nh.advertise<visualization_msgs::MarkerArray>(config.accTopic, 1);
    }

private:
    Config config;                              //加载配置的参数
    ros::Publisher routePub;                    //发布轨迹
    ros::Publisher wayPointsPub;                //发布鼠标点下的坐标点
    ros::Publisher trajectoryPub;               //发布弹道
    ros::Publisher accPub;                      //发布加速度

public:
    void visualize(const Trajectory &traj, const vector<Vector3d> &route, int id = 0)
    {
        visualization_msgs::Marker routeMarker, wayPointsMarker, trajMarker, accMarker;
        visualization_msgs::MarkerArray accMarkers;

        routeMarker.id = id;
        routeMarker.type = visualization_msgs::Marker::LINE_LIST;
        routeMarker.header.stamp = ros::Time::now();
        routeMarker.header.frame_id = config.frameName;
        routeMarker.pose.orientation.w = 1.00;
        routeMarker.action = visualization_msgs::Marker::ADD;
        routeMarker.ns = "route";
        routeMarker.color.r = 1.00;
        routeMarker.color.g = 0.00;
        routeMarker.color.b = 0.00;
        routeMarker.color.a = 1.00;
        routeMarker.scale.x = 0.05;

        wayPointsMarker = routeMarker;
        wayPointsMarker.type = visualization_msgs::Marker::SPHERE_LIST;
        wayPointsMarker.ns = "waypoints";
        wayPointsMarker.color.r = 1.00;
        wayPointsMarker.color.g = 1.00;
        wayPointsMarker.color.b = 1.00;
        wayPointsMarker.scale.x = 0.30;
        wayPointsMarker.scale.y = 0.30;
        wayPointsMarker.scale.z = 0.30;

        trajMarker = routeMarker;
        trajMarker.ns = "trajectory";
        trajMarker.scale.x = 0.15;
        if (id == 0)
        {
            trajMarker.color.r = 1.00;
            trajMarker.color.g = 0.00;
            trajMarker.color.b = 0.00;
        }
        else if (id == 1)
        {
            trajMarker.color.r = 0.00;
            trajMarker.color.g = 1.00;
            trajMarker.color.b = 0.00;
        }
        else
        {
            trajMarker.color.r = 0.00;
            trajMarker.color.g = 0.00;
            trajMarker.color.b = 1.00;
        }

        accMarker = routeMarker;
        accMarker.type = visualization_msgs::Marker::ARROW;
        accMarker.header.stamp = ros::Time::now();
        accMarker.ns = "acc";
        if (id == 0)
        {
            accMarker.color.r = 255.0 / 255.0;
            accMarker.color.g = 20.0 / 255.0;
            accMarker.color.b = 147.0 / 255.0;
        }
        else if (id == 1)
        {
            accMarker.color.r = 60.0 / 255.0;
            accMarker.color.g = 179.0 / 255.0;
            accMarker.color.b = 113.0 / 255.0;
        }
        else
        {
            accMarker.color.r = 30.0 / 255.0;
            accMarker.color.g = 144.0 / 255.0;
            accMarker.color.b = 255.0 / 255.0;
        }
        accMarker.scale.x = 0.05;
        accMarker.scale.y = 0.15;
        accMarker.scale.z = 0.30;

        if (route.size() > 0)
        {
            bool first = true;
            Vector3d last;
            for (auto it : route)
            {
                if (first)
                {
                    first = false;
                    last = it;
                    continue;
                }
                geometry_msgs::Point point;

                point.x = last(0);
                point.y = last(1);
                point.z = last(2);
                routeMarker.points.push_back(point);
                point.x = it(0);
                point.y = it(1);
                point.z = it(2);
                routeMarker.points.push_back(point);
                last = it;

                wayPointsMarker.points.push_back(point);
            }

            routePub.publish(routeMarker);
        }

        if (route.size() > 0)
        {
            for (auto it : route)
            {
                geometry_msgs::Point point;
                point.x = it(0);
                point.y = it(1);
                point.z = it(2);
                wayPointsMarker.points.push_back(point);
            }

            wayPointsPub.publish(wayPointsMarker);
        }

        if (traj.getPieceNum() > 0)
        {
            double T = 0.01;
            Vector3d lastX = traj.getPos(0.0);
            for (double t = T; t < traj.getTotalDuration(); t += T)
            {
                geometry_msgs::Point point;
                Vector3d X = traj.getPos(t);
                point.x = lastX(0);
                point.y = lastX(1);
                point.z = lastX(2);
                trajMarker.points.push_back(point);
                point.x = X(0);
                point.y = X(1);
                point.z = X(2);
                trajMarker.points.push_back(point);
                lastX = X;
            }
            trajectoryPub.publish(trajMarker);
        }

        if (traj.getPieceNum() > 0)
        {
            if (id == 0)
            {
                accMarker.action = visualization_msgs::Marker::DELETEALL;
                accMarkers.markers.push_back(accMarker);
                accPub.publish(accMarkers);
                accMarkers.markers.clear();
                accMarker.action = visualization_msgs::Marker::ADD;
            }

            double T = 0.08;
            for (double t = 0; t < traj.getTotalDuration(); t += T)
            {
                accMarker.id += 3;
                accMarker.points.clear();
                geometry_msgs::Point point;
                Vector3d X = traj.getPos(t);
                point.x = X(0);
                point.y = X(1);
                point.z = X(2);
                accMarker.points.push_back(point);
                X += traj.getAcc(t);
                point.x = X(0);
                point.y = X(1);
                point.z = X(2);
                accMarker.points.push_back(point);
                accMarkers.markers.push_back(accMarker);
            }
            accPub.publish(accMarkers);
        }
    }
};

class TrajPlan
{
    public:
        TrajPlan();
        void pointCallBack(const geometry_msgs::PoseStamped::ConstPtr &point_msg);
    private:
        ros::NodeHandle nh_ ;
        ros::Subscriber point_sub;
        Trajectory traj;
        std::vector<Eigen::Vector3d> wPs;
        void motion_plan_callback(const ros::TimerEvent &e);
        int point_count ;
};

TrajPlan::TrajPlan()
{
    point_sub = nh_.subscribe<geometry_msgs::PoseStamped>("/goal",10,&TrajPlan::pointCallBack,this);
    point_count = 1;
}

void TrajPlan::pointCallBack(const geometry_msgs::PoseStamped::ConstPtr &point_msg)
{
    ros::Rate rate(10);
    float x = point_msg->pose.position.x;
    float y = point_msg->pose.position.y;
    float z = point_msg->pose.position.z;

    if(point_count==5)
    {
        // wPs.emplace_back(0.0, 0.0, 0.0);
        wPs.pop_back();
        wPs.pop_back();
        wPs.pop_back();
        wPs.pop_back();
        point_count = 1;
    }
    if(point_count<=4)
    {
        wPs.emplace_back(x,y,z);
        point_count ++;
    }
    std::cout<<"Receive x = "<<x<<"y = "<<y<<"z = "<<z<<std::endl;
    std::cout<<"count = "<<point_count<<std::endl;

    ros::NodeHandle nh_priv("~");
    Config config(nh_priv);
    Visualizer viz(config, nh_);
    AmTraj amTrajOpt(config.weightT, config.weightAcc, config.weightJerk,config.maxVelRate, config.maxAccRate, config.iterations, config.epsilon);
    Eigen::Vector3d iV(0,0,0), fV(0,0,0);
    Eigen::Vector3d iA(0,0,0), fA(0,0,0);

    if(point_count==5)
    {
        int time_count = 0;
        while (ros::ok())
        {
            time_count++;
            ROS_INFO("Draw trail start");
            traj = amTrajOpt.genOptimalTrajDTC(wPs, iV, iA, fV, fA);
            viz.visualize(traj, wPs, 0);
            rate.sleep();
            if(time_count>=50){break;}
        }
    }
}

int main(int argc,char **argv)
{
    ros::init(argc, argv, "traj_node");

    // ros::NodeHandle nh_, nh_priv("~");
    // Config config(nh_priv);
    // Visualizer viz(config, nh_);
    // ros::Rate r(10);
    // while(ros::ok())
    // {
    //     AmTraj amTrajOpt(1024.0, 16.0, 0.4, 7.00, 4.00, 23, 0.02);
    //     Eigen::Vector3d iV(2.0, 1.0, 0.0), fV(0.0, 0.0, 0.0);
    //     Eigen::Vector3d iA(0.0, 0.0, 2.0), fA(0.0, 0.0, 0.0);
    //     std::vector<Eigen::Vector3d> wPs;
    //     wPs.emplace_back(0.0, 0.0, 0.0);
    //     wPs.emplace_back(4.0, 2.0, 1.0);
    //     wPs.emplace_back(9.0, 7.0, 5.0);
    //     wPs.emplace_back(1.0, 3.0, 2.0);
    //     Trajectory traj = amTrajOpt.genOptimalTrajDTC(wPs, iV, iA, fV, fA);
    //     viz.visualize(traj, wPs, 0);
    //     r.sleep();
    // }

    ROS_INFO("Traj_plan start");
    TrajPlan tp;
    ros::spin();
    
    return 0;
}