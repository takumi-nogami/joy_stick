#include "ros/ros.h"
#include "ros_test_pkg/MsgTest.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "topic_publisher");
  ros::NodeHandle nh;

  ros::Publisher ros_test_pub = nh.advertise<ros_test_pkg::MsgTest> ("ros_test_msg", 100);
  ros::Rate loop_rate(10);

  ros_test_pkg::MsgTest msg;
  int count = 0;

  while(ros::ok())
  {
    msg.stamp = ros::Time::now();
    msg.data = count;

    ROS_INFO("send msg = %d", msg.stamp.sec);
    ROS_INFO("send msg = %d", msg.stamp.nsec);
    ROS_INFO("send msg = %d", msg.data);
    ros_test_pub/publish(msg);
    loop_rata.sleep();
    ++count;
  }

  return 0;
}
