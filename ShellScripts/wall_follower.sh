#!/bin/sh

xterm -e "export ROBOT_INITIAL_POSE='-x 1 -y -4' && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find wall_follower)/worlds/myworld.world" &
sleep 5

#xterm -e "rosparam set /slam_gmapping/minimumScore 1000" &
#sleep 3

#'angularUpdate: 0.1 linearUpdate: 0.1 maxRange: 15 maxUrange: 10 minimumScore: 1000 particles: 300'; rosparam get/slam_gmapping/minimumScore" &

#xterm -e " rosrun gmapping slam_gmapping" &
xterm -e "roslaunch ../turtlebot_simulator/turtlebot_gazebo/launch/gmapping_demo.launch custom_gmapping_launch_file:=./wall.launch" &
sleep 5

xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm -e "source /home/workspace/setup.sh; rosrun wall_follower wall_follower"
