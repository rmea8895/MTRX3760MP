#include "../include/major_project/odom.h"

COdom::COdom(ros::NodeHandle *nh_)
{
  ROS_INFO("Odom Init");
  bool ret = init(ros::NodeHandle *nh_);
  // check initialization
  ROS_ASSERT(ret);
}

bool COdom::init(ros::NodeHandle *nh_)
{
  odom_sub_ = nh_->subscribe("odom", 10, &COdom::callBack, this);
  return true;
}

void COdom::callBack(const nav_msgs::Odometry::ConstPtr &msg)
{
  // Calculate the rotation angle in yaw using euler angles
  double siny = 2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.z + msg->pose.pose.orientation.x * msg->pose.pose.orientation.y);
	double cosy = 1.0 - 2.0 * (msg->pose.pose.orientation.y * msg->pose.pose.orientation.y + msg->pose.pose.orientation.z * msg->pose.pose.orientation.z);
  double yaw = std::atan2(siny, cosy);
  
  // Change yaw to 0 to 360 from 0-180 -> -180-0
  if (yaw < 0)
    yaw += 2*M_PI;

  mYaw = yaw;
}

double COdom::getYaw()
{
  return mYaw;
}
