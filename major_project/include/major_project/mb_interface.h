#ifndef MB_INTERFACE
#define MB_INTERFACE

#include <ros/ros.h>
#include "states.h"
#include <iostream>
#include <utility>
#include <actionlib_msgs/GoalID.h> // for canceling the goal
#include <actionlib_msgs/GoalStatus.h> 
#include <geometry_msgs/PoseStamped.h>


/**
 * @brief ROS move_base node interface
 * This class allows users to publish goals to the move_base interface
 * and cancel the goals
 */
class Cmb_interface
{
  public:
    Cmb_interface(ros::NodeHandlePtr nh_);
    ~Cmb_interface(); 

    // Sends the (x, y) goal coordinates to the 
    void sendGoal(std::pair<double, double> coords);

    void cancelGoal();
    
  private:
    // move base goal publisher
    ros::Publisher move_base_goal_pub;

    // actionlib cancel goal publisher
    ros::Publisher actionlib_cancel_pub;
    
    // initialises ROS subscribers and publishes
    bool init(ros::NodeHandlePtr nh_);
};

#endif // MB_INTERFACE
