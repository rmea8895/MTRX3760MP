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
      nextState = init_state() ? States::UNAV : States::INIT;
      break;
    }
    case States::UNAV:
    {
      nextState = uNavI.handler() ? States::UNAV : States::END;
      break;
    }
    case States::FIRE:
    {
      fireInterface.handler();
    }
    case States::END:
    {
      ROS_INFO("End State", int(currentState));
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


bool CFSM::init_state(){
  static int counter = 0;
  counter ++;

  if (counter == 100)
    return true
  else
    return false
}

CFSM::~CFSM()
{
  ros::shutdown();
}

