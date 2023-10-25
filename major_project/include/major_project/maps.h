#ifndef MAPS_H
#define MAPS_H

#include "ros/ros.h"
#include <nav_msgs/OccupancyGrid.h> 
#include <utility>
#include <vector>

//#define MAP_DEBUG

/**
 * Class that subscribes to /map and 
 * /move_base/global_costmap/costmap
 * note both of these maps are the global maps
*/

class CMaps
{
  public:
    CMaps(ros::NodeHandlePtr nh_);
    ~CMaps();

    // Returns pointer to map
    auto getMapPtr();
    // Returns pointer to cost map
    auto getCostMapPtr();
    /// 2d Vector
    std::vector<std::vector<signed char>> map;
    std::vector<std::vector<signed char>> costMap;

  private:
    /// Subscriber node handlers
    ros::Subscriber map_sub_;
    ros::Subscriber costMap_sub_;

    bool init(ros::NodeHandlePtr nh_);
    
    void mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg);
    void costMapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg);
};

#endif // MAPS_H