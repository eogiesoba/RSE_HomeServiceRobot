#!/bin/sh
#Launch turtlebot_world.launch file
xterm  -e  " source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 4

#Launch amcl_demo.launch file
xterm -e " source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 4

#Launch view_navigation.launch to observe the map in rviz
xterm -e " source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" 
