#include "../include/major_project/odom.h"

COdom::COdom(ros::NodeHandlePtr nh_)
{
  ROS_INFO("Odom Init");
  bool ret = init(nh_);
  // check initialization
  ROS_ASSERT(ret);
}

std::pair<double, double> COdom::getPos()
{
  return std::pair<double, double>(mX, mY);
}

bool COdom::init(ros::NodeHandlePtr nh_)
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

  mX = msg->pose.pose.position.x;
  mY = msg->pose.pose.position.y;
}

double COdom::getYaw()
{
  return mYaw;
}

// double Codom::getYaw360() {

//     if (mYaw < 0) {
//         return 2*M_PI + mYaw;
//     } else {
//         return mYaw;
//     }
// }

COdom::~COdom()
{ 
}