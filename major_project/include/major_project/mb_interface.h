#ifndef MB_INTERFACE
#define MB_INTERFACE

#include <ros/ros.h>
#include "states.h"
#include <iostream>
#include <actionlib_msgs/GoalID> // for canceling the goal
#include <geometry_msgs/PoseStamped.h>

/**
 * move_base client interface
*/
class Cmb_interface
{
  public:
    Cmb_interface(ros::NodeHandlePtr nh_);
    ~Cmb_interface(); 

    
    void sendGoal();

    void cancelGoal();
  private:
    ros::Publisher move_base_goal_pub;

    ros::Publisher actionlib_cancel_pub;

    bool init(ros::NodeHandlePtr nh_);

};

#endif // MB_INTERFACE