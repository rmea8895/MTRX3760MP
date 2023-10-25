#ifndef FSM_H
#define FSM_H

// ----- includes ----- 
#include "ros/ros.h"
#include "odom.h"
#include "test.h"
#include "states.h"
#include "mb_interface.h"
#include "unexplored_nav.h"
#include <memory.h>
#include <iostream>

// ----- macros ----- 
#define DEBUG

// ----- foward declarations ----- 
class COdom;
class CTEST;
class Cmb_interface;
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

    // ---- move_base interface ----
    Cmb_interface mbI{nh_};

    // Unexplored nav
    CUnexploredNav uNavI{nh_};


  private:
    // ---- state history ----
    States currentState = States::INIT;
    States prevState = States::INIT;
    States nextState;
};


#endif // FSM_H