#ifndef MAPS_H
#define MAPS_H

#include "ros/ros.h"
#include <nav_msgs/OccupancyGrid.h> 

/**
 * Class that subscribes to /map and 
 * /move_base/global_costmap/costmap
*/

class CMaps
{
  public:
    CMaps(ros::NodeHandle *nh_);
    ~CMaps();

  private:
    /// Subscriber node handlers
    ros::Subscriber map_sub_;
    ros::Subscriber costMap_sub_;

    bool init(ros::NodeHandle *nh_);
    
    void mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg);
    void costMapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg);
};

#endif // MAPS_H