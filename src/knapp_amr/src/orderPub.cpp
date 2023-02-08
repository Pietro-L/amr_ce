#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "knapp_amr/msg/order.hpp"
/*
Publisher which publishes a single order #. order # can be given as input to node.
*/

int main(int argc, char * argv[])
{
	
	rclcpp::init(argc, argv);
	rclcpp::Node::SharedPtr nh_ =rclcpp::Node::make_shared("publish_order_once");

	rclcpp::QoS qos = rclcpp::QoS(rclcpp::KeepLast(1));
	qos.reliable();
	bool send=true;
	rclcpp::Publisher<knapp_amr::msg::Order>::SharedPtr publisher_;
	publisher_=nh_->create_publisher<knapp_amr::msg::Order>("nextOrder",qos);
    int orderid;
	(argv[1]!=NULL)?orderid=atoi(argv[1]):orderid=1000001;
	auto message = knapp_amr::msg::Order();
    
	while (rclcpp::ok()){
        message.order_id=orderid;
        message.description="order n# "+std::to_string(orderid);;
		if (send){
			RCLCPP_INFO(nh_->get_logger(), "Publishing order");
			publisher_->publish(message);
			send = false;
			//RCLCPP_INFO(nh_->get_logger(), "Publishing position");
		}

		rclcpp::sleep_for(std::chrono::milliseconds(500));
	}
	rclcpp::shutdown();
	return 0;
}