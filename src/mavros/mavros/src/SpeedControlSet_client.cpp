/**
 * @brief 服务端的实现
 * @file SpeedControlSet_client.cpp
 * @author szf
 *
 * @addtogroup src
 */

#include "ros/ros.h"
#include "mavros_msgs/SpeedControlSet.h"
#include <mavros/mavros_plugin.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    // // 调用时动态传值,如果通过 launch 的 args 传参，需要传递的参数个数 +3
    // if (argc != 4)
    // // if (argc != 5)//launch 传参(0-文件路径 1传入的参数 2传入的参数 3节点名称 4日志路径)
    // {
    //     ROS_ERROR("请提交三个数");
    //     return 1;
    // }


    // 2.初始化 ROS 节点
    ros::init(argc,argv,"SpeedControl_Client");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建 客户端 对象
    ros::ServiceClient client = nh.serviceClient<mavros_msgs::SpeedControlSet>("send");
    //等待服务启动成功
    //方式1
    ros::service::waitForService("/mavros/speed_control/send");
    //方式2
    // client.waitForExistence();
    // 5.组织请求数据
    mavros_msgs::SpeedControlSet ai;
    // ai.request.vw_set = atoll(argv[1]);
    // ai.request.vx_set = atoll(argv[2]);
    // ai.request.vy_set = atoll(argv[3]);
    ai.request.vw_set = 0;
    ai.request.vx_set = 0;
    ai.request.vy_set = 0;

    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(ai);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("请求正常处理 :%d",ai.response.send_success);
    }
    else
    {
        ROS_ERROR("请求处理失败....");
        return 1;
    }

    return 0;
}
