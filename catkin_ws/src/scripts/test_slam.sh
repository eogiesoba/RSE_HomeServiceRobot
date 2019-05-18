#!/bin/sh
# Path to catkin ws.
catkin_workspace="/home/workspace/RSE_HomeServiceRobot/catkin_ws"

# Launch turtlebot_world.launch file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 4
# Launch gmapping demo file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 4
# Launch view navigation launch file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 4
# Launch the keyboard teleop launch file.
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_teleop keyboard_teleop.launch"

