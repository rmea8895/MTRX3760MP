#ifndef FSM_H
#define FSM_H

// ----- macros ----- 
#define DEBUG

// ----- includes ----- 
#include "ros/ros.h"
#include "odom.h"
#include "cmdvel.h"
//#include "laser.h" // not implemented yet
//#include "SLAM.h"  // not implemented yet


// ----- foward declarations ----- 
class COdom;
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
      STATE2,
      END
    };

    /// Next state logic function
    bool nextStateLogic();

    // ---- your class here ----
    // EXAMPLE !!
    // CSLAM test;

    // ---- subscriber topic interfaces ----
    COdom odomInterface(ros::NodeHandle *nh_);

  private:
    // ---- state history ----
    States currentState = States::INIT;
    States prevState = States::INIT;
    States nextState;
};


#endif // FSM_H