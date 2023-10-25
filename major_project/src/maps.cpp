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
  std::cout << "Map Callback" << std::endl;
  // cell size is default 0.05m/cell or 5cm per cell resolution
  // probably want 2cm per cell res, can modify this in the yaml config
  unsigned int width = msg->info.width;
  unsigned int height = msg->info.height;

  std::cout << msg->data[0] << std::endl;
  // for(int i = 0; i < width; i++)
  // {
  //   for(int j = 0; j < height; j++)
  //   {
  //     std::cout << i << ", " << j << std::endl;
  //     map[i][j] = msg->data[i+j*width];
  //   }
  // }
  std::cout << "Map Callback end" << std::endl;
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

std::vector<std::vector<signed char>>* CMaps::getMapPtr()
{
  std::vector<std::vector<signed char>>* mapPtr = &map;
  return mapPtr;
}

std::vector<std::vector<signed char>>* CMaps::getCostMapPtr()
{
  std::vector<std::vector<signed char>>* costMapPtr = &costMap;
  return costMapPtr;
}

CMaps::~CMaps()
{
}