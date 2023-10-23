#ifndef FSM_H
#define FSM_H

// ----- includes ----- 
#include "ros/ros.h"
#include "odom.h"
#include "test.h"

// ----- macros ----- 
#define DEBUG

// ----- foward declarations ----- 
class COdom;
class CTEST;
//class CSLAM;      // ONLY FOR EXAMPLE AT THE MOMENT

/**
 * Finite State Machine, contains interfaces to standard topics
*/
class CFSM 
{
  public:
    CFSM();
    ~CFSM();

    /// ROS node handle
    ros::NodeHandle nh_;

    /// states enum 
    enum class States : int
    {
      INIT,
      STATE1,
      END
    };

    /// Next state logic function
    bool nextStateLogic();

    // ---- your class here ----
    CTEST tester;

    // ---- subscriber topic interfaces ----
    COdom odomInterface{*nh_};

  private:
    // ---- state history ----
    States currentState = States::INIT;
    States prevState = States::INIT;
    States nextState;
};


#endif // FSM_H