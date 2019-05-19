#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

// Create initial odometry values to be used in add_markers node.
float x_Odom = 0.0;
float y_Odom = 0.0;
// Create callback function for updated odometry values to be outputed.
void odom_callback(const nav_msgs::Odometry::ConstPtr& msg) {
  ::x_Odom = msg->pose.pose.position.x;
  ::y_Odom = msg->pose.pose.position.y;
}
//This will run the main virtual object logic to place object in 1st and 2nd location.
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber Odom_sub = n.subscribe("/odom", 1000, odom_callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  // Create initial x,y,delta, and radius values
  float x_length = 0.0;
  float y_length = 0.0;
  float delta = 0.5;
  float rad = 0.0;
  // Define position and orientation of 2 robot location goals. 
  float x_goal = 0.5;
  float y_goal = 0.0;
  float w_goal = 1.0;
  float x_goal2 = 0.0;
  float y_goal2 = 0.5;
  float w_goal2 = 1.0;

  // Initialize marker
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Give the marker a color of orange.
  marker.color.r = 1.0f;
  marker.color.g = 0.65f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  // Give the marker a 0.27 cubic meter size. 
  marker.scale.x = 0.27;
  marker.scale.y = 0.27;
  marker.scale.z = 0.27;

  // Create state vairable.
  uint32_t state_var = 0;

  while (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker.lifetime = ros::Duration();
    marker.header.stamp = ros::Time::now();
    switch (state_var) {
      // Publish the marker at the pickup zone
      case 0:
        ROS_INFO("Publishing marker to be picked up.");
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;
        // Set position and orientation of marker. 
        marker.pose.position.x = x_goal;
        marker.pose.position.y = y_goal;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = w_goal;
        //Publish the marker.
        marker_pub.publish(marker);
        ROS_INFO("Going to state 1...");
        state_var = 1;
        break;
      case 1:
        ROS_INFO("Waiting for robot to pick up marker.");
        sleep(1);
        //See if radius is less than delta and then move to next state. 
        x_length = fabs(marker.pose.position.x - x_Odom);
        y_length = fabs(marker.pose.position.y - y_Odom);
        rad = sqrt(pow(x_length, 2) + pow(x_length, 2));
        if (rad < delta) { 
             ROS_INFO("Radius is less than delta. Going to state 2...");
            state_var = 2;
        }
        break;

      case 2:
        ROS_INFO("Marker has just been picked up. Now Hiding marker.");
        sleep(2);
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::DELETE;
        // Publish marker
        marker_pub.publish(marker);
        ROS_INFO("Going to state 3...");
        state_var = 3;
        break;
      case 3:
        ROS_INFO("Waiting for marker to be dropped off at final location.");
        sleep(2);
        //See if radius is less than delta and then move to next state. 
        x_length = fabs(marker.pose.position.x - x_Odom);
        y_length = fabs(marker.pose.position.y - y_Odom);
        rad = sqrt(pow(x_length, 2) + pow(x_length, 2));
        if (rad < delta) { 
             ROS_INFO("Radius is less than delta. Going to state 4...");
            state_var = 4;
        }
        break;

      case 4:
        ROS_INFO("Final Destination Reached. Dropping of marker now.");
        sleep(2);
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;
        // Set position and orientation of marker. 
        marker.pose.position.x = x_goal2;
        marker.pose.position.y = y_goal2;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = w_goal2;
        // Publish marker
        marker_pub.publish(marker);
        ROS_INFO("Congratulations! Marker has successfully reached it's final destination!");
      default:
        ROS_INFO("No valid state variable has been found.");
    }
    ros::spinOnce();
    r.sleep();
  }
}

