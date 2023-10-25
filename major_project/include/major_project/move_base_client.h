#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <utility>
#include "states.h"
#include <iostream>
#include <geometry_msgs/PoseStamped.h>
// typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

/**
 * move_base client interface
*/
class Cmove_baseCI
{
  public:
    Cmove_baseCI(ros::NodeHandlePtr nh_);
    ~Cmove_baseCI(); 

    ros::Publisher move_base_pub;
    // move to xy coordinate function 
    // States moveXY(
    //   std::pair<int, int> coords, 
    //   States currentState, 
    //   States nextState,
    //   States errorState);
    void sendGoal();
    
  private:
    bool init(ros::NodeHandlePtr nh_);
  // spin::once handled by main 
    //MoveBaseClient ac;

    

};
