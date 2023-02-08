#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
/*
Publisher which repeatedly publishes a pose message.
*/


class MinimalPublisher : public rclcpp::Node
{
public:
	MinimalPublisher() : Node("publish_pose"), count_(0){
		publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("currentPosition",10);
		timer_ = this->create_wall_timer(
			std::chrono::milliseconds(500), std::bind(&MinimalPublisher::timer_callback, this));
	}
private:
	void timer_callback(){
		auto message = geometry_msgs::msg::PoseStamped();
		message.header.frame_id="/myframe";
		message.header.stamp=this->get_clock()->now();
		message.pose.position.x=0.0;
		message.pose.position.y=0.0;
		message.pose.position.z=0.0;
		message.pose.orientation.w=1.0;
		message.pose.orientation.x=0.0;
		message.pose.orientation.y=0.0;
		message.pose.orientation.z=0.0;
		RCLCPP_INFO(this->get_logger(), "Publishing position");
		publisher_->publish(message);
	}
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
	size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
/*
//change to this if you only want to send one message. 
int main(int argc, char * argv[])
{
	
	rclcpp::init(argc, argv);
	rclcpp::Node::SharedPtr nh_ =rclcpp::Node::make_shared("publish_pose_once");

	rclcpp::QoS qos = rclcpp::QoS(rclcpp::KeepLast(5));
	qos.reliable();
	bool send=true;
	rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
	publisher_=nh_->create_publisher<geometry_msgs::msg::PoseStamped>("currentPosition",qos);
	
	
	auto message = geometry_msgs::msg::PoseStamped();
	while (rclcpp::ok()){
		
		message.header.frame_id="/myframe";
		message.header.stamp=nh_->get_clock()->now();
		message.pose.position.x=0.0;
		message.pose.position.y=0.0;
		message.pose.position.z=0.0;
		message.pose.orientation.w=1.0;
		message.pose.orientation.x=0.0;
		message.pose.orientation.y=0.0;
		message.pose.orientation.z=0.0;
		if (send){
			RCLCPP_INFO(nh_->get_logger(), "Publishing position");
			publisher_->publish(message);
			send = false;
			//RCLCPP_INFO(nh_->get_logger(), "Publishing position");
			
		}

		rclcpp::sleep_for(std::chrono::milliseconds(500));
	}

	rclcpp::shutdown();
	return 0;
}*/