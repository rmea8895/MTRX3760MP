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
      // Fill in
      // EXAMPLE!!!
      nextState = States::INIT;
      
      counter++;
      if (counter > 100)
      {
        move_baseCI.sendGoal();
        nextState = States::STATE1;
      }
      // counter++;
      // if (counter > 100)
      // {
      //   nextState = move_baseCI.moveXY(
      //     std::pair<int, int>(1,0.5),
      //     States::INIT,
      //     States::STATE1,
      //     States::ERROR);
      // }
      // test.handler(odomInterface.getYaw(), ... )
      // tester.test1(odomInterface.getYaw());
      break;
    }
    case States::STATE1:
    {
      // tester.test2();
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

