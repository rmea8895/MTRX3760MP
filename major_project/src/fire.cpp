#include "../include/major_project/fire.h"

bool CFire::handler()
{
  mbInterface.sendGoal(findEmergency());
  return true;
}

CFire::CFire(ros::NodeHandlePtr nh_): Cemergency(nh_)
{}

CFire::~CFire()
{
}