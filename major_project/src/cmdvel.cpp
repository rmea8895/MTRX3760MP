#include "../include/major_project/cmdvel.h"

CCmdVel::CCmdVel(ros::NodeHandlePtr nh_)
{
  ROS_INFO("CmdVel Init");
  bool ret = init(nh_);
  // check initialization
  ROS_ASSERT(ret);
}

bool CCmdVel::init(ros::NodeHandlePtr nh_)
{
  cmd_vel_pub_  = nh_->advertise<geometry_msgs::Twist>( "/cmd_vel", 10 );  return true;
  return true;
}

void CCmdVel::updateCmdVel(double linear, double angular)
{
  geometry_msgs::Twist cmd_vel;

  cmd_vel.linear.x  = linear;
  cmd_vel.angular.z = angular;

  cmd_vel_pub_.publish(cmd_vel);
}

CCmdVel::~CCmdVel()
{ 
}