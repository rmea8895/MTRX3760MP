#include "../include/major_project/main.h"

// ------------------------ Main -----------------------------------------------
int main(int argc, char* argv[])
{
  ros::init(argc, argv, NODE_NAME);
  
  CFSM FSM;

  ros::Rate loop_rate(LOOP_RATE); // 30 Hz

  ROS_INFO("Main Whileloop Start");
  
  while (ros::ok())
  {
    // Ensure FSM logic is okay
    ROS_ASSERT(FSM.nextStateLogic());
    // call callbacks
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}