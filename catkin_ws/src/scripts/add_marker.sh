#!/bin/sh
# Path to catkin ws.
catkin_workspace="/home/workspace/RSE_HomeServiceRobot/catkin_ws"

# Launch turtlebot_world.launch file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
# Launch gmapping demo file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
# Launch custom rviz launch file
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && roslaunch rviz_markers rviz.launch" &
sleep 3
# Launch the pick_objects node
xterm -e "cd ${catkin_workspace} && source devel/setup.bash && rosrun add_markers add_markers"

