#include "../include/major_project/FSM.h"

CFSM::CFSM()
{
  // allocate node handler
  nh_.reset(new ros::NodeHandle);
}

bool CFSM::nextStateLogic()
{
  static int counter = 0;
  // ------ Next state logic ------ 
  switch(currentState)
  {
    case States::INIT:
    {
      // put in function for FSM
      nextState = States::INIT;
      static int counter = 0;
      counter ++;

      if (counter == 100)
      {
        // tester.test1();
        nextState = States::UNAV;
      }
      #ifndef DEBUG
        ROS_INFO("State [%d]", int(currentState));
      #endif
      break;
    }
    case States::UNAV:
    {
      nextState = uNavI.handler() ? States::UNAV : States::END;
      #ifndef DEBUG
        ROS_INFO("State [%d]", int(currentState));
      #endif
      break;
    }
    case States::FIRE:
    {
      fireInterface.handler();
    }
    case States::PERSON:
    {
      personInterface.handler();
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

