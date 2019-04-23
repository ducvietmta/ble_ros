
#include "ros/ros.h"
#include <ble_scanner/BLEData.h>
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include "SimpleKalmanFilter.h"
#include <string>
using namespace std;
string data;
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
void getdata(const ble_scanner::BLEData::ConstPtr& msg, ros::Publisher* pub_rssi_raw, ros::Publisher* pub_rssi_data)
{   
	string mac_addr;
	std_msgs::Int32 rssi;
	for (int i=0; i<msg->data.size(); ++i){
		mac_addr = msg->data[i].mac_address;
		if(mac_addr == "c3:72:10:1b:73:e8"){
			rssi.data = msg->data[i].rssi;	
			pub_rssi_raw->publish(rssi);
			rssi.data = simpleKalmanFilter.updateEstimate(rssi.data);
			rssi.data = simpleKalmanFilter.updateEstimate(rssi.data);
			pub_rssi_data->publish(rssi);				
		}
	}	
}

int main(int argc, char** argv)
{
    // setting
    ros::init(argc, argv, "test_ble");
    ros::NodeHandle nh_;
    ros::Publisher pub_rssi_raw = nh_.advertise<std_msgs::Int32>("/rssi_raw", 1);
    ros::Publisher pub_rssi_data = nh_.advertise<std_msgs::Int32>("/rssi_data", 1);
    ros::Subscriber pose_subscriber = nh_.subscribe<ble_scanner::BLEData> ("/ble_data",1,boost::bind(getdata, _1,&pub_rssi_raw, &pub_rssi_data));
    ros::spin();
    ros::Time::init(); 
	
   return 0;
}
