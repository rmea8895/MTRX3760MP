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
  static int counter = 0;
  // ------ Next state logic ------ 
  switch(currentState)
  {
    case States::INIT:
    {
    
      nextState = States::INIT;
      static int counter = 0;
      counter ++;

      if (counter == 100)
      {
        // tester.test1();
        nextState = States::UNAV;
      }
      break;
    }
    case States::UNAV:
    {
      nextState = uNavI.handler() ? States::UNAV : States::END;

      static int counter = 0;
      counter++;
      if(counter == 500)
      {
        nextState = States::FIRE;
      }
      ROS_INFO("State [%d]", int(currentState));
      break;
    }
    case States::FIRE:
    {
      fireInterface.handler();
    }
    case States::END:
    {
      ROS_INFO("State [%d]", int(currentState));
      break;
    }
    case States::ERROR:
    {
      ROS_INFO("Error! undefined behaviour");
      break;
    }
    default:
    {
      nextState = States::ERROR;
      break;
    }
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

