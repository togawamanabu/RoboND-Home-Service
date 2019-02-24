#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "pick_objects");

  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  //Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 2;
  goal.target_pose.pose.position.y = 3;
  goal.target_pose.pose.orientation.w = 1.0;

  //Send the goal position and orientation for the robot to reach
  ROS_INFO("sending goal");
  ac.sendGoal(goal);

  //Wait an infinite time for the results
  ac.waitForResult();

  //Check if the robot reachd its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The base moved to the first goal");
    ros::Duration(5.0).sleep();
  } else {
    ROS_INFO("Faild to move the first goal");
  }

  ROS_INFO("Moving to next goal");
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = -3.0;
  goal.target_pose.pose.position.y = 1;
  goal.target_pose.pose.orientation.w = -1.0;

  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("moved to the second goal");
    
  } else {
    ROS_INFO("The base failed to move");
  }

  return 0;
}
    

  

