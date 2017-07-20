
#include <ros/ros.h>
//#include <geometry_msgs/Twist.h>
#include <aruco_msgs/MarkerArray.h>

/*make a publisher and a subscriber
The publisher publishes cmd_vel the same name [done]
and the subscriber listens to teleop_key on a remapped topic so the turtle doesn't know it , [remap the teleop topic through launch file]
the subscriber of the turtle listens to our node which publishes the same topic [do nothing] */

ros::Publisher *pubPtr;

void poseReceived(const aruco_msgs::MarkerArray &msgIn)
{
  aruco_msgs::MarkerArray msgOut;
  msgOut=msgIn;
  //msgOut.linear.x=-msgIn.linear.x;
  //msgOut.angular.z=-msgIn.angular.z;
  //pubPtr->publish(msgOut);
  ROS_INFO_STREAM(msgOut.markers[0].pose.pose.orientation);

}
int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "pose_est_node");
  ros::NodeHandle nh;

  //the subsriber
  ros::Subscriber sub= nh.subscribe("aruco_marker_publisher/markers",1000,poseReceived);//name the topic original_cmd_vel

  //the publisher
  ros::Publisher pub=nh.advertise<aruco_msgs::MarkerArray>("/pose_est/pose_diff",1000);
  pubPtr = &pub;

  ros::spin();

  ros::Rate rate(30);

  rate.sleep();
  //ROS_INFO("Hello world!");
}
