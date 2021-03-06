#!/bin/sh

xterm -e " export ROBOT_INITIAL_POSE='-x -0 -y -3.0' && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find wall_follower)/worlds/myworld.world" &
sleep 5

xterm -e " roslaunch ../turtlebot_simulator/turtlebot_gazebo/launch/amcl_demo.launch map_file:=/home/workspace/src/World/map.yaml" &
sleep 5

xterm -e "roslaunch add_makers add_markers.launch" &
sleep 5

xterm -e "rosrun add_makers add_makers_node" &
sleep 3

xterm -e "source /home/workspace/devel/setup.sh; rosrun pick_objects pick_objects"
