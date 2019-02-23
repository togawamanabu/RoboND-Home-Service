#!/bin/sh

xterm -e "export ROBOT_INITIAL_POSE='-x -0 -y -3.0' && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find wall_follower)/worlds/myworld.world" &
sleep 5

xterm -e " rosrun gmapping slam_gmapping" &
sleep 5

xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 5


xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
