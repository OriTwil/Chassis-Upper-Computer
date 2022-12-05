/*
 * @Author: szf01 2176529058@qq.com
 * @Date: 2022-11-21 15:45:32
 * @LastEditors: szf01 2176529058@qq.com
 * @LastEditTime: 2022-12-05 20:48:00
 * @FilePath: /catkin_ws_3/src/mavros/mavros/src/plugins/posture.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @brief Posture plugin 插件功能主要为实现mavlink数据包与mavros自定义消息之间的转化
 * @file posture.cpp
 * @author szf
 *
 * @addtogroup plugin
 */
 
#include <mavros/mavros_plugin.h>
#include "mavlink/v2.0/common/mavlink_msg_posture.hpp"
#include "mavros_msgs/Posture.h"

namespace mavros {
namespace std_plugins {
/**
 * @brief Posture plugin
 */
class PosturePlugin : public plugin::PluginBase {
public:
	PosturePlugin() : PluginBase(),
		posture_nh("~posture")
	{ }
 
	void initialize(UAS &uas_)
	{
		PluginBase::initialize(uas_);
		//实例化 发布者、订阅者、客户端、服务端 对象

		pos_publisher = posture_nh.advertise<mavros_msgs::Posture>("posture", 10);
	}

    /**
     * @brief Get the subscriptions object
	 *        用来获取mavlink消息
	 * 		  获取到mavlink包后进入handle_speed_control进行解析
     * 
     * @return Subscriptions 
     */
	Subscriptions get_subscriptions() {
		ROS_INFO("get_subscriptions success!");
		return {
			make_handler(&PosturePlugin::handle_posture),
		};
	}

private:
	//实例化 ROS 句柄
	ros::NodeHandle posture_nh;

	//创建发布者、订阅者、服务端、客户端
	ros::Publisher pos_publisher;
 
	/**
	 * @brief rx handlers 接收到mavlink包后调用此函数，将mavlink数据包解析为mavros中的自定义消息，并发布到话题
	 * 
	 * @attention mavlink::common::msg::POSTURE为自动生成的消息头文件中所定义的，也是依据此来解析收到的mavlink消息
	 * @param msg 
	 * @param speed_control 
	 */

	void handle_posture(const mavlink::mavlink_message_t *msg, mavlink::common::msg::POSTURE &mavlink_posture)
	{
		//posture
		auto mavros_msg_posture = boost::make_shared<mavros_msgs::Posture>();
		mavros_msg_posture -> header.stamp = ros::Time::now();
		mavros_msg_posture -> pos_x_state = mavlink_posture.pos_x ;
		mavros_msg_posture -> pos_y_state = mavlink_posture.pos_y ;
        mavros_msg_posture -> w_z_state = mavlink_posture.w_z ;
        mavros_msg_posture -> xangle_state = mavlink_posture.xangle ;
        mavros_msg_posture -> yangle_state = mavlink_posture.yangle ;
        mavros_msg_posture -> zangle_state = mavlink_posture.zangle ;

        pos_publisher.publish(mavros_msg_posture);
	}
 
 
};
}	// namespace std_plugins
}	// namespace mavros
 
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::PosturePlugin, mavros::plugin::PluginBase)
 