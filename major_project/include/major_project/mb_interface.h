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
 * move_base client interface
*/
class Cmb_interface
{
  public:
    Cmb_interface(ros::NodeHandlePtr nh_);
    ~Cmb_interface(); 

    
    void sendGoal(std::pair<double, double> coords);

    void cancelGoal();
    
  private:

    ros::Publisher move_base_goal_pub;

    ros::Publisher actionlib_cancel_pub;

    ros::Subscriber actionlib_status;

    void statusCB(const actionlib_msgs::GoalStatus::ConstPtr &msg);

    int STATUS = 0;
    bool init(ros::NodeHandlePtr nh_);

};

#endif // MB_INTERFACE
