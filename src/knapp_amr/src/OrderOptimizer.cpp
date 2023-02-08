#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <filesystem>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "knapp_amr/msg/order.hpp"
#include "knapp_amr/TSP.hpp"

/*
ROS2 node solving AMR candidate evaluation problem as described in package.xml
*/


struct coords{
  float x;
  float y;
  bool operator==(const coords& other) {return (x == other.x && y == other.y);}
};

struct part{
  int product;
  std::string partName;
  coords location;
};

class OrderOptimizer : public rclcpp::Node
{
public:
	OrderOptimizer(char * direc);

private:
	//callback function for robot pose message
	void pose_callback(const geometry_msgs::msg::PoseStamped & msg) {
		robot.x=msg.pose.position.x;
		robot.y=msg.pose.position.y;
		// std::string msgstr = "got position: x pos: " + std::to_string(msg.pose.position.x) + "y pos: " + std::to_string(msg.pose.position.y);
		// RCLCPP_INFO(this->get_logger(), msgstr.c_str());
	}
	//callback function for newOrder message 
	void order_callback(const knapp_amr::msg::Order & msg) {
		newOrder=true;
		std::string msgstr = "obtained order id: " + std::to_string(msg.order_id);
		RCLCPP_INFO(this->get_logger(), msgstr.c_str());
		std::vector<std::thread> threads;
		RCLCPP_INFO(this->get_logger(), "parsing database");		
		products.clear();
		for (unsigned int i = 0; i<orderfiles.size(); ++i){
    		threads.push_back(std::thread(&OrderOptimizer::YamlParserOrder,this,std::ref(orderfiles[i]) ,std::ref(msg.order_id)));
  		}
  		for(auto& t: threads){
    		t.join();
  		}
		YamlParserProduct();
		RCLCPP_INFO(this->get_logger(), "finished parsing");
		// msgstr = "products size: " + std::to_string(products.size());
		// RCLCPP_INFO(this->get_logger(), msgstr.c_str());
		//msgstr = "parts size: " + std::to_string(partList.size());
		//RCLCPP_INFO(this->get_logger(), msgstr.c_str());
		std::vector<std::vector<float>> adj= makeAdj();      
  		TSP tsp(adj);
  		std::vector<int> path = tsp.solve();
		if(path[1]==1)
			std::reverse(path.begin(),path.end());
		path.pop_back();
		msgstr = "Working on order "+std::to_string(msg.order_id)+ " ("+msg.description+")";
		RCLCPP_INFO(this->get_logger(), msgstr.c_str());
		int counter=1;
		std::ostringstream ss;
		for(unsigned int i:path){
			for(auto j:partList){
				if(j.location.x==uniqueCoords[i].x && j.location.y==uniqueCoords[i].y){
					ss<<counter<< ". Fetching part '"<<j.partName<<"' for product '"<<j.product<< "' at x: "<<j.location.x<< ", y: "<<j.location.y;
					counter++;
					RCLCPP_INFO(this->get_logger(),ss.str().c_str());
					ss.str(std::string());
				}
			}
		}
		ss<<counter<< ". Delivering to destination x: " <<delivery.x<<" y: "<<delivery.y;
		RCLCPP_INFO(this->get_logger(),ss.str().c_str());
		ss.str(std::string());
	}
	//function to publish markers
	void publish_markers(){
		auto arrayMarkers = visualization_msgs::msg::MarkerArray();
		//if new order publish clear markers message
		if(newOrder){
			auto marker= visualization_msgs::msg::Marker();
			marker.action=3;
			arrayMarkers.markers.push_back(marker);
			publisher_->publish(arrayMarkers);
			newOrder=false;
		}
		//create markers and publish
		if(uniqueCoords.size()){
			
			int id=0;
			auto marker= visualization_msgs::msg::Marker();
			marker.header.frame_id="/my_frame";
			marker.header.stamp=this->get_clock()->now();
			marker.ns="shapes";
			marker.id=id;
			marker.type=1;
			marker.action=0;
			marker.pose.position.x = robot.x;
  			marker.pose.position.y = robot.y;
  			marker.pose.position.z = 0;
  			marker.pose.orientation.x = 0.0;
  			marker.pose.orientation.y = 0.0;
  			marker.pose.orientation.z = 0.0;
  			marker.pose.orientation.w = 1.0;
			marker.scale.x = 10;
			marker.scale.y = 10;
			marker.scale.z = 10;
			marker.color.r = 0.0f;
			marker.color.g = 0.0f;
			marker.color.b = 1.0f;
			marker.color.a = 1.0;
			//RCLCPP_INFO(this->get_logger(),"here");
			arrayMarkers.markers.push_back(marker);
			marker.header.stamp=this->get_clock()->now();
			marker.color.r = 1.0f;
			marker.color.g = 0.0f;
			marker.color.b = 0.0f;
			marker.color.a = 1.0;
			marker.id=++id;
			marker.pose.position.x = delivery.x;
  			marker.pose.position.y = delivery.y;
			marker.type=3;
			arrayMarkers.markers.push_back(marker);
			marker.color.r = 0.0f;
			marker.color.g = 1.0f;
			marker.color.b = 0.0f;
			for(unsigned int i = 2;i<uniqueCoords.size();++i){
				marker.header.stamp=this->get_clock()->now();
				marker.id=++id;
				marker.pose.position.x = uniqueCoords[i].x;
  				marker.pose.position.y = uniqueCoords[i].y;
				arrayMarkers.markers.push_back(marker);
			}
			publisher_->publish(arrayMarkers);
		}
	}

	//function to parse Order yaml files
	void YamlParserOrder(const std::string & orderFile,const int & order_id){
		YAML::Node config = YAML::LoadFile(orderFile);
		for (const auto &order : config) {
			if (order["order"].as<int>()==order_id){
				mylock.lock();
				delivery.x = order["cx"].as<float>();
				delivery.y = order["cy"].as<float>();
				for (const auto &product : order["products"]) {
					products.push_back(product.as<int>());
				}
				mylock.unlock();
			}
		}

	}
	//function to parse products yaml file
	void YamlParserProduct(){
		//std::sort(products.begin(),products.end());
		try {
			YAML::Node config = YAML::LoadFile(std::string(dir)+"/configuration/products.yaml");
			uniqueCoords.clear();
			partList.clear();
			uniqueCoords.push_back(robot);
			uniqueCoords.push_back(delivery);
			for(int product_id:products){
				for (const auto &product : config) {
					if (product["id"].as<int>()==product_id){
						for (const auto &part : product["parts"]) {
							std::string partname = part["part"].as<std::string>();
							coords location;
							location.x = part["cx"].as<float>();
							location.y = part["cy"].as<float>();
							partList.push_back({product_id,partname,location});

							if(uniqueCoords.empty()){uniqueCoords.push_back(location);}
							else{
								bool unique=true;
								for(auto i:uniqueCoords){
									if(location==i){unique=false;break;}
								}
								if(unique){
									uniqueCoords.push_back(location);
								}
							}							
						}
						break;
					}
				}
			}
		} catch (const YAML::Exception &e) {
			std::cerr << "Error: " << e.what() << "\n";
		}
	}

	float distTwoPoints(const coords& a, const coords& b){
		float dx = b.x-a.x;
		float dy = b.y-a.y;
		return sqrt(dx*dx + dy*dy) ;
	}

	std::vector<std::vector<float>> makeAdj(){
		std::vector<std::vector<float>> adj(uniqueCoords.size(), std::vector<float>(uniqueCoords.size(), 0.0));

		for(unsigned int i =0; i<adj.size();i++){
			for(unsigned int j = i;j<adj.size();j++){
				adj[i][j]=distTwoPoints(uniqueCoords[i],uniqueCoords[j]);
				adj[j][i]=distTwoPoints(uniqueCoords[i],uniqueCoords[j]);
			}
		}
		adj[0][1]=0;
		adj[1][0]=0;
		return adj;
	}


	//class members
	bool newOrder=true;
	coords delivery;
	coords robot;
	std::string dir;
	//vectors to store products and parts as well as vector of unique coordinates
	std::vector<int> products;
	std::vector<part> partList;
	std::vector<coords> uniqueCoords;
	std::mutex mylock;
	//vector with order database files
	std::vector<std::string> orderfiles;
	//subscriptions and publisher
	rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr poseSub_;
	rclcpp::Subscription<knapp_amr::msg::Order>::SharedPtr orderSub_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_;
};

OrderOptimizer::OrderOptimizer(char * direc):Node("Order_Optimizer"),dir((std::string)direc){
	for (const auto & entry : std::filesystem::directory_iterator(dir+"/orders"))
        orderfiles.push_back(entry.path());

	rclcpp::QoS qos(rclcpp::KeepLast(7));
	poseSub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("/currentPosition", qos, std::bind(&OrderOptimizer::pose_callback, this, std::placeholders::_1));
	orderSub_ = this->create_subscription<knapp_amr::msg::Order>("/nextOrder", qos, std::bind(&OrderOptimizer::order_callback, this, std::placeholders::_1));
	publisher_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("order_path",10);
	timer_ = this->create_wall_timer(
			std::chrono::milliseconds(2000), std::bind(&OrderOptimizer::publish_markers, this));
}


int main(int argc, char * argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<OrderOptimizer>(argv[1]));
	rclcpp::shutdown();

  	return 0;
}