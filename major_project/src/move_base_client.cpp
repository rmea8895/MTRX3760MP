#include "../include/major_project/move_base_client.h"

// Cmove_baseCI::Cmove_baseCI(ros::NodeHandlePtr nh_)
//   : ac("move_base", true)
//   /*: ac(*nh_, "move_base", false)*/ /* Want to use our own thread to spin*/
// {
//   bool ret = init();
//   ROS_ASSERT(ret);
// }
Cmove_baseCI::Cmove_baseCI(ros::NodeHandlePtr nh_)
{
  ROS_INFO("cancer init");
  bool ret = init(nh_);
  ROS_ASSERT(ret);
}




Cmove_baseCI::~Cmove_baseCI()
{
}

bool Cmove_baseCI::init(ros::NodeHandlePtr nh_)
{
  move_base_pub = nh_->advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
  return true;
  // ROS_INFO("Waiting for the move_base action server to come up");
  // return ac.waitForServer(ros::Duration(0.5));
  // while(!ac.waitForServer(ros::Duration(5.0))){
  //   ROS_INFO("Waiting for the move_base action server to come up");
  // }
  // return true;
}

void Cmove_baseCI::sendGoal()
{
  geometry_msgs::PoseStamped bruh;
  bruh.header.frame_id = "map";
  bruh.pose.position.x = 0.0;
  bruh.pose.position.y = 0.0;
  bruh.pose.orientation.w = 0.7514451452616765;
  bruh.pose.orientation.z = 0.659795569599143;
  move_base_pub.publish(bruh);
}

// States Cmove_baseCI::moveXY(
//   std::pair<int, int> coords, 
//   States currentState, 
//   States nextState,
//   States errorState)
// {

//   States ret = currentState;
//   // States might be fucked up idk we will see
//   //ROS_INFO("State: %s", ac.getState().toString())
//   std::cout << "State:" << ac.getState().toString() << std::endl;

//   move_base_msgs::MoveBaseGoal goal;

//   //we'll send a goal to the robot to move 1 meter forward
//   goal.target_pose.header.frame_id = "base_link";
//   goal.target_pose.header.stamp = ros::Time::now();

//   goal.target_pose.pose.position.x = 1.0;
//   goal.target_pose.pose.orientation.w = 1.0;

//   ROS_INFO("Sending goal");
//   ac.sendGoal(goal);

//   ac.waitForResult();

//   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//     ROS_INFO("Hooray, the base moved 1 meter forward");
//   else
//     ROS_INFO("The base failed to move forward 1 meter for some reason");


//     // if(ac.getState().isDone())
//     // {
//     //   ret = currentState;
//     //   // pending or active means it is not done
//     //   // waiting for result, continue in this state, not done
//     // }
//     // else if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//     // {
//     //   ret = nextState;
//     //   // Transition to next state,
//     // }
//     // else if(ac.getState() == actionlib::SimpleClientGoalState::PENDING)
//     // {
//     //   move_base_msgs::MoveBaseGoal goal;
//     //   goal.target_pose.header.frame_id = "base_link";
//     //   goal.target_pose.header.stamp = ros::Time::now();

//     //   goal.target_pose.pose.position.x = coords.first;
//     //   goal.target_pose.pose.orientation.w = coords.second;

//     //   ROS_INFO("Sending goal");
//     //   ac.sendGoal(goal);
//     //   ret = nextState;
//     // }
//     // else 
//     // {
//     //   ROS_INFO("goal failed!!!");
//     //   ret = errorState;
//     // }

//   return ret;
// }