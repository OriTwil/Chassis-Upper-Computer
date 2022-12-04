/**
 * @brief SpeedControls plugin 插件功能主要为实现mavlink数据包与mavros自定义消息之间的转化
 * @file speed_control.cpp
 * @author szf
 *
 * @addtogroup plugin
 */
 
#include <mavros/mavros_plugin.h>
#include <mavros_msgs/SpeedControlStatus.h>
#include "mavros_msgs/SpeedControlSet.h"
#include "mavros_msgs/SpeedControlSet_sub.h"
#include "mavros_msgs/Posture.h"
#include "mavlink/v2.0/common/mavlink_msg_control_set.hpp"
#include "mavlink/v2.0/common/mavlink_msg_speed_control_status.hpp"

namespace mavros {
namespace std_plugins {
/**
 * @brief Speed Control plugin
 */
class SpeedControlPlugin : public plugin::PluginBase {
public:
	SpeedControlPlugin() : PluginBase(),
		speed_control_nh("~speed_control")
	{ }
 
	void initialize(UAS &uas_)
	{
		PluginBase::initialize(uas_);
		//实例化 发布者、订阅者、客户端、服务端 对象
		control_pub = speed_control_nh.advertise<mavros_msgs::SpeedControlStatus>("status", 10);
		send_service = speed_control_nh.advertiseService("send", &SpeedControlPlugin::send_cb_service, this);
		send_subscriber = speed_control_nh.subscribe<mavros_msgs::SpeedControlSet_sub>("send_topic", 10, &SpeedControlPlugin::send_callback_subscribe, this);
		pos_publisher = speed_control_nh.advertise<mavros_msgs::Posture>("posture", 10);
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
			make_handler(&SpeedControlPlugin::handle_speed_control),
		};
	}

private:
	//实例化 ROS 句柄
	ros::NodeHandle speed_control_nh;

	//创建发布者、订阅者、服务端、客户端
	ros::Publisher control_pub;
	ros::ServiceServer send_service;
	ros::Subscriber send_subscriber;
	ros::Publisher pos_publisher;
 
	/**
	 * @brief rx handlers 接收到mavlink包后调用此函数，将mavlink数据包解析为mavros中的自定义消息，并发布到话题
	 * 
	 * @attention common::msg::SPEED_CONTROL_STATUS为自动生成的消息头文件中所定义的，也是依据此来解析收到的mavlink消息
	 * @param msg 
	 * @param speed_control 
	 */

	void handle_speed_control(const mavlink::mavlink_message_t *msg, mavlink::common::msg::SPEED_CONTROL_STATUS &speed_control)
	{
		auto speed_control_msg = boost::make_shared<mavros_msgs::SpeedControlStatus>();
		speed_control_msg->header.stamp = ros::Time::now(); 
		speed_control_msg->vx_state = speed_control.vx_state;
		speed_control_msg->vy_state = speed_control.vy_state;
		speed_control_msg->vx_state = speed_control.vw_state;

		control_pub.publish(speed_control_msg);
		//posture
		// auto mavros_msg_posture = boost::make_shared<mavros_msgs::Posture>();
		// mavros_msg_posture->header.stamp = ros::Time::now();
		// mavros_msg_posture->pos_x_state = mavlink_posture.
		// mavros_msg_posture -> 

	}
 
	/**
	 * @brief callbacks 服务端或者订阅者获得消息后进入callback，将消息转化为mavlink数据包，通过mavlink消息发送API，发送给下位机
	 * 
	 * @param req 
	 * @param responce 
	 * @return true 
	 * @return false 
	 */
 
	bool send_cb_service(mavros_msgs::SpeedControlSet::Request &req , mavros_msgs::SpeedControlSet::Response &responce)
	{
		mavlink::common::msg::CONTROL_SET msg;
		//将server收到的request赋值给mavlink消息
		msg.vx_set = req.vx_set;
		msg.vy_set = req.vy_set;
		msg.vw_set = req.vw_set;
		//响应发送成功
		responce.send_success = true;
		//调用mavlink消息发送API
		UAS_FCU(m_uas)->send_message_ignore_drop(msg);
		return true;
	}

	void send_callback_subscribe(const mavros_msgs::SpeedControlSet_sub::ConstPtr& speed_p)
	{
		mavlink::common::msg::CONTROL_SET msg;
		msg.vw_set = speed_p->vw_set_sub;
		msg.vy_set = speed_p->vy_set_sub;
		msg.vx_set = speed_p->vx_set_sub;

		msg.x_set = speed_p->x_set_sub;
		msg.y_set = speed_p->y_set_sub;
		// ROS_INFO("send_callback succcess!");
		UAS_FCU(m_uas)->send_message_ignore_drop(msg);

	} 
};
}	// namespace std_plugins
}	// namespace mavros
 
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::SpeedControlPlugin, mavros::plugin::PluginBase)
 