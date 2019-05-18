#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  //Define 2 goal messages
  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseGoal goal2;

  //Create the 2 zones necessary for publishing
  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot in order to arrive at each goal respectively.
  goal.target_pose.pose.position.x = 0.5;
  goal.target_pose.pose.position.y = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;
  goal2.target_pose.pose.position.x = 0.0;
  goal2.target_pose.pose.position.y = 0.5;
  goal2.target_pose.pose.orientation.w = 1.0;

  // Send the 1st goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Yay! First Robot zone has been reached!");
    // 5 Second pause will also be required after reaching pickpu zone. 
    sleep(5);
  }
  else{
    ROS_INFO("Robot is unable to reach the first zone...");
    return 0;
  }

  // Send the 2nd goal position and orientation for the robot to reach
  ROS_INFO("Sending goal2");
  ac.sendGoal(goal2);

  // Wait an infinite time for the results
  ac.waitForResult();
   
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Alright! Second Robot zone has been reached!");
    sleep(7);
  }
  else{
    ROS_INFO("Robot is unable to reach the second zone...");
  }

  return 0;
}
