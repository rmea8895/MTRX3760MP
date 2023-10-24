#include "../include/major_project/maps.h"

CMaps::CMaps(ros::NodeHandlePtr nh_)
{
  ROS_INFO("Map subscribers init");
  bool ret = init(nh_);
  // check initialization
  ROS_ASSERT(ret);
}

bool CMaps::init(ros::NodeHandlePtr nh_)
{
  map_sub_ = nh_->subscribe("/map", 2, &CMaps::mapCallBack, this);
  costMap_sub_ = nh_->subscribe("/move_base/global_costmap/costmap", 2, &CMaps::costMapCallBack, this);
  return true;
}

void CMaps::mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  // cell size is default 0.05m/cell or 5cm per cell resolution
  // probably want 2cm per cell res, can modify this in the yaml config
  unsigned int width = msg->info.width;
  unsigned int height = msg->info.height;

  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      map[i][j] = msg->data[i+j*width];
    }
  }
  #ifdef MAP_DEBUG
    ROS_INFO("State [%d]", msg);
  #endif
}

void CMaps::costMapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  unsigned int width = msg->info.width;
  unsigned int height = msg->info.height;

  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      costMap[i][j] = msg->data[i+j*width];
    }
  }
}

auto CMaps::getMapPtr()
{
  auto mapPtr = &map;
  return mapPtr;
}

auto CMaps::getCostMapPtr()
{
  auto costMapPtr = &costMap;
  return costMapPtr;
}

CMaps::~CMaps()
{
}