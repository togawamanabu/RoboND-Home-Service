#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "add_makers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  const double pick_pose[3] = {2.0, 3.0, 1.0};
  const double drop_pose[3] = {-3.0, 0.0, -1.0};

  visualization_msgs::Marker marker;

  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "basic_shapes";
  marker.id = 0;

  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = pick_pose[0];
  marker.pose.position.y = pick_pose[1];
  marker.pose.position.z = pick_pose[2];
  marker.pose.orientation.x = 0;
  marker.pose.orientation.y = 0;
  marker.pose.orientation.z = 0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  //publich the marker
  while (marker_pub.getNumSubscribers() < 1) {
    if(!ros::ok()) {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }

  ROS_INFO("Publishing marker pick position");
  marker_pub.publish(marker);
  ros::Duration(5.0).sleep();

  marker.action = visualization_msgs::Marker::DELETE;

  ROS_INFO("Publishng Delete pick marker");
  marker_pub.publish(marker);
  ros::Duration(5.0).sleep();

  marker.action = visualization_msgs::Marker::ADD;  
  marker.pose.position.x = drop_pose[0];
  marker.pose.position.y = drop_pose[1];
  marker.pose.position.z = drop_pose[2];

  ROS_INFO("Publishing Drop marker");
  marker_pub.publish(marker);

  return 0;
}
  
  



  
