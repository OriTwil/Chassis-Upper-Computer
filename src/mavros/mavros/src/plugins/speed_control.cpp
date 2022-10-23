/**
 * @brief CrawlControls plugin
 * @file crawl_controls.cpp
 * @author Yanfeng <962353916@qq.com>
 *
 * @addtogroup plugin
 */
 
#include <mavros/mavros_plugin.h>
#include <mavros_msgs/SpeedControlStatus.h>
#include <mavros_msgs/SpeedControlSet.h>


namespace mavros {
namespace std_plugins {
/**
 * @brief Crawl Control plugin
 */
class SpeedControlPlugin : public plugin::PluginBase {
public:
	SpeedControlPlugin() : PluginBase(),
		speed_control_nh("~speed_control")
	{ }
 
	void initialize(UAS &uas_)
	{
		PluginBase::initialize(uas_);

		control_pub = speed_control_nh.advertise<mavros_msgs::SpeedControlStatus>("status", 10);
		send_service = speed_control_nh.advertiseService("send", &SpeedControlPlugin::send_cb, this);

		// // Set Thrust scaling in px4_config.yaml, setpoint_raw block.
		// if (!speed_control_nh.getParam("thrust_scaling", thrust_scaling))
		// {
		// 	ROS_WARN_THROTTLE_NAMED(5, "setpoint_raw", "thrust_scaling parameter is unset. Attitude (and angular rate/thrust) setpoints will be ignored.");
		// 	thrust_scaling = -1.0;
		// }//add

	}
    //用来获取mavlink解析到的消息
	Subscriptions get_subscriptions() {
		ROS_INFO("HIHI");
		return {
			make_handler(&SpeedControlPlugin::handle_speed_control),
		};
	}

private:
	ros::NodeHandle speed_control_nh;
 
	ros::Publisher control_pub;
	ros::ServiceServer send_service;
 
	/* -*- rx handlers -*- */
    // mavlink::crawl_control_status::msg::CRAWL_CONTROL_STATUS为自动生成的消息头文件中所定义的，也是依据此来解析收到的mavlink消息。
	void handle_speed_control(const mavlink::mavlink_message_t *msg, mavlink::common::msg::SPEED_CONTROL_STATUS &speed_control)
	{
		auto speed_control_msg = boost::make_shared<mavros_msgs::SpeedControlStatus>();
		ROS_INFO("HAHA");
		// crawl_control_msg->header.stamp = ros::Time::now();
		speed_control_msg->vx_state = speed_control.vx_state;
		speed_control_msg->vy_state = speed_control.vy_state;
		speed_control_msg->vx_state = speed_control.vw_state;
		//将解析到的消息发布至topic
		control_pub.publish(speed_control_msg);
	}
 
	/* -*- callbacks -*- */
 
	bool send_cb(mavros_msgs::SpeedControlSet::Request &req, mavros_msgs::SpeedControlSet::Response &responce)
	{
		ROS_INFO("HEHE");
		mavlink::common::msg::SPEED_CONTROL_SET msg;
		// mavlink_speed_control_set_t msg;
		//讲server收到的request赋值给mavlink消息
		msg.vx_set = req.vx_set;
		msg.vy_set = req.vy_set;
		msg.vw_set = req.vw_set;
		//响应发送成功
		responce.send_success = true;
		//调用mavlink消息发送API
		UAS_FCU(m_uas)->send_message_ignore_drop(msg);
		return true;
	}
};
}	// namespace std_plugins
}	// namespace mavros
 
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::SpeedControlPlugin, mavros::plugin::PluginBase)
 