#include "../include/major_project/test.h"


CTEST::CTEST(ros::NodeHandle *nh_)
 : cmdvelInterface(nh_)
{

}
void CTEST::test1(double Yaw)
{
  std::cout << "Turtlebot yaw:" << Yaw << std::endl;
}

void CTEST::test2()
{
  std::cout << "Test 2: tesing movement" << std::endl;
  cmdvelInterface.updateCmdVel(0.2, 0.2);
}
