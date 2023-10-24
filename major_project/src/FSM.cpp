#include "../include/major_project/FSM.h"

CFSM::CFSM()
{
  // allocate node handler
  nh_.reset(new ros::NodeHandle);

  // // construct odometer intergace
  // odomInterface(nh_);
  // // construct tester
  // tester(nh_);
}

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
      tester.test1(odomInterface.getYaw());
      break;
    }
    case States::STATE1:
    {
      tester.test2();
      // Fill in
      ROS_INFO("State [%d]", int(currentState));
      nextState = States::STATE1;
      break;
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

