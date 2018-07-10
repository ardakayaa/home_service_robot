#!/bin/sh

xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5

xterm  -e  "  roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 5

xterm  -e  "  roslaunch turtlebot_teleop keyboard_teleop.launch" &

sleep 5

xterm  -e  "  roslaunch turtlebot_gazebo gmapping_demo.launch" 


