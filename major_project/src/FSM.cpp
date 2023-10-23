#include "../include/major_project/FSM.h"

bool CFSM::nextStateLogic()
{
  // ------ Next state logic ------ 
  switch(currentState)
  {
    case States::INIT:
    {
      // Fill in
      // EXAMPLE!!!
      
      // test.handler(odomInterface.getYaw(), ... )
    }
    case States::STATE1:
    {
      // Fill in
    }
    case States::END:
    {
      ROS_INFO("State [%d]", int(currentState));
      break;
    }
    default:
      nextState = States::INIT;
    break;
  }

  // update current State
  prevState = currentState;
  currentState = nextState;

  return true;
}

CFSM::~CFSM()
{
  ros::shutdown();
}

