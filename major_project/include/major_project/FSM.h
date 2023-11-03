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
class CUnexploredNav;
class CTEST;

/**
 * Finite State Machine, contains interfaces to standard topics
*/
class CFSM 
{
  public:
    CFSM();
    ~CFSM();

    // ROS node handle pointer
    ros::NodeHandlePtr nh_ = ros::NodeHandlePtr(new ros::NodeHandle());

    // Next state logic function
    bool nextStateLogic();

  private:
    // ----- state interfaces -----
    // Test interface for debugging
    CTEST tester{nh_};

    // Unexplored nav
    CUnexploredNav uNavI{nh_};

    // Fire state
    CFire fireInterface{nh_};
    
    // ----- private variables -----
    // inital state used to wait until callbacks return non-zero values
    bool init_state();

    // ----- state history -----
    States currentState = States::INIT;
    States prevState = States::INIT;
    States nextState;
};


#endif // FSM_H