#!/bin/sh

xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5

xterm  -e  " export ROBOT_INITIAL_POSE='-x .555830 -y 4.469885 -Y 1.431852' && roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 5

xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find wall_follower_pkg)/map/personal_map.yaml" & 

sleep 5

xterm  -e  "  roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

xterm  -e  "  rosrun pick_objects pick_objects_node" &