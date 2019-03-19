#include "ros/ros.h"
#include "ros_test_pkg/MsgTest.h"

void msgCallback(const ros_test_pkg::MsgTest::ConstPtr& smg)
{
  ROS_INFO("receive msg = %d", msg->stamp.sec);
  ROS_INFO("receive msg = %d", msg->stamp.nsec);
  ROS_INFO("receive msg = %d", msg->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "topic_publisher");
  ros::NodeHandle nh;

  ros::Publisher ros_test_pub = nh.advertise("ros_test_msg", 100, msgcallback);
  ros::spin();
  return 0;
}
