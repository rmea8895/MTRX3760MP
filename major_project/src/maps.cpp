#include "../include/major_project/maps.h"

CMaps::CMaps(ros::NodeHandle *nh_)
{
  ROS_INFO("Map subscribers init");
  bool ret = init(ros::NodeHandle *nh_);
  // check initialization
  ROS_ASSERT(ret);
}

bool CMaps::init(ros::NodeHandle *nh_)
{
  map_sub__ = nh_->subscribe("/map", 2, &CMaps::mapCallBack, this);
  costMap_sub_ = nh_->subscribe("/move_base/global_costmap/costmap", 2, &CMaps::costMapCallBack, this);
  return true;
}

void CMaps::mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  // cell size is default 0.05m/cell or 5cm per cell resolution
  // probably want 2cm per cell res, can modify this in the yaml config
  
}

void CMaps::costMapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  

}
