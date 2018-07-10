#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects_node");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  // Update Robot Status using paramter server
  ros::param::set("/robot_position", "Start_Point");

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseGoal goal_2;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal_2.target_pose.header.frame_id = "map";
  goal_2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -7.0;
  goal_2.target_pose.pose.position.y = 0.0;
  goal.target_pose.pose.orientation.w = 1;
  goal_2.target_pose.pose.position.x = 0.0;
  goal_2.target_pose.pose.position.y = 7.0;
  goal_2.target_pose.pose.orientation.w = 1;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal_1");
  ac.sendGoal(goal);
  
  // Update Robot Status using paramter server
  ros::param::set("/robot_position", "Move_To_Pick");

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the first goal has reached!!!");
    // Update Robot Status using paramter server
    ros::param::set("/robot_position", "Picked_Up");
  }
  else
  {
    ROS_INFO("The base failed while tryinh to reach the first goal :(");
    // Update Robot Status using paramter server
    ros::param::set("/robot_position", "Faild_Pick");
  	return 0;
  }
  // Wait 5 Sec
  ros::Duration(5.0).sleep();
  
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal_2");
  ac.sendGoal(goal_2);
  
  // Update Robot Status using paramter server
  ros::param::set("/robot_position", "Move_To_Drop");
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the second goal has reached!!!");
    // Update Robot Status using paramter server
    ros::param::set("/robot_position", "Dropped_Off");
  }
  else
  {
    ROS_INFO("The base failed while tryinh to reach the second goal :(");
    // Update Robot Status using paramter server
    ros::param::set("/robot_position", "Failed_Drop");
  }
}