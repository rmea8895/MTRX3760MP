#ifndef FSM_H
#define FSM_H

// ----- includes ----- 
#include "ros/ros.h"
#include "odom.h"
#include "test.h"
#include "states.h"
#include "move_base_client.h"
#include <memory.h>

// ----- macros ----- 
#define DEBUG

// ----- foward declarations ----- 
class COdom;
class CTEST;
class Cmove_baseCI;
//class CSLAM;      // ONLY FOR EXAMPLE AT THE MOMENT

/**
 * Finite State Machine, contains interfaces to standard topics
*/
class CFSM 
{
  public:
    CFSM();
    ~CFSM();

    /// ROS node handle pointer
    ros::NodeHandlePtr nh_ = ros::NodeHandlePtr(new ros::NodeHandle());

    /// Next state logic function
    bool nextStateLogic();

    // ---- your class here ----
    CTEST tester{nh_};

    // ---- subscriber topic interfaces ----
    COdom odomInterface{nh_};

    // ---- move_base_client ----
    Cmove_baseCI move_baseCI{nh_};

  private:
    // ---- state history ----
    States currentState = States::INIT;
    States prevState = States::INIT;
    States nextState;
};


#endif // FSM_H