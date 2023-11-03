#ifndef ODOM_H
#define ODOM_H

#include "ros/ros.h"
#include <memory.h>
#include <nav_msgs/Odometry.h> 
#include <utility>

/**
 * @brief Odometry subscriber interface
 * Subscribes to the odom topic
 */
class COdom 
{
  public:
    // Constructor takes pointer to the node handler
    COdom(ros::NodeHandlePtr nh_);
    ~COdom();

    // Returns the yaw of the turtlebot in radians (0-360)
    double getYaw();

    // Returns position of the turtlebot (x, y)
    std::pair<double, double> getPos();

  private:
    // Subscriber node handler
    ros::Subscriber odom_sub_;

    // Initialisation function
    bool init(ros::NodeHandlePtr nh_);

    // Callback function for odom topic
    void callBack(const nav_msgs::Odometry::ConstPtr &msg);

    // Yaw of the turtlebot
    double mYaw = 0.0;

    // X coordinate of the turtlebot
    double mX = 0.0;

    // Y coorinate of the turltebot
    double mY = 0.0;
};

#endif