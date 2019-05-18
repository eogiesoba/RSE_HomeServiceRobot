#!/bin/sh
#Launch turtlebot_world.launch file
xterm  -e  " source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 4

#Launch gmapping_demo.launch file
xterm -e " source devel/setup.bash && roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 4

#Launch view_navigation.launch to observe the map in rviz
xterm -e " source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 4

#Launch the keyboard_teleop.launch to manulally control the robot with keyboard commands
xterm -e " source devel/setup.bash && roslaunch turtlebot_teleop keyboard_teleop.launch" 
