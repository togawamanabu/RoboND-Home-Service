#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

const double pick_pose[3] = {2.0, 3.0, 1.0};
const double drop_pose[3] = {-3.0, 1.0, 0};

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void odom_callback(const nav_msgs::Odometry odom) {
  double robo_x = odom.pose.pose.position.x;
  double robo_y = odom.pose.pose.position.y;

  double dx = robo_x-pick_pose[0];
  double dy = robo_y-pick_pose[1];

  dx*=dx;
  dy*=dy;

  double delta = 1.5;

  const bool is_pick_zone = dx < delta && dy < delta;

  dx = robo_x-drop_pose[0];
  dy = robo_y-drop_pose[1];

  dx*=dx;
  dy*=dy;

  ROS_INFO("robo %.3f, %3f drop dist : %.3f, %.3f", robo_x, robo_y, dx, dy);
  const bool is_drop_zone = dx < delta && dy < delta;


  if(is_pick_zone) {
    ROS_INFO("Waiting 5 second..");
    ros::Duration(5.0).sleep();

    ROS_INFO("Publishng Delete pick marker");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
  }

  if(is_drop_zone) {
    ROS_INFO("Publishing Drop pick marker");
    
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = drop_pose[0];
    marker.pose.position.y = drop_pose[1];
    marker.pose.position.z = drop_pose[2];    
    marker_pub.publish(marker);
  } 
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "add_makers");
  ros::NodeHandle n;
  ros::Rate r(1);

  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber subscriber_odom = n.subscribe("odom", 1000, &odom_callback);

  uint32_t shape = visualization_msgs::Marker::CUBE;



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

  ros::Duration pause_duration(0.1);

  while (ros::ok()) {
    ros::spinOnce();
    pause_duration.sleep();
  }

  return 0;
}
  
  



  
