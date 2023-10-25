#include "../include/major_project/test.h"


CTEST::CTEST(ros::NodeHandlePtr nh_)
 : cmdvelInterface(nh_)
 , mapInterface(nh_)
 , unexploredNav(nh_)
{
}

void CTEST::test1()
{
  //std::cout << "Turtlebot yaw:" << Yaw << std::endl;
  // std::cout << "In test" << std::endl;
  // std::vector<std::vector<signed char>>* test =  mapInterface.getCostMapPtr();
  // int ROW = test->size();
  // int COL = test[0].size();
  // for (int i = 0; i < ROW; i++)
  // {
  //   for (int j=0; j < COL; j++)
  //   {
  //     if (static_cast<int>(test->at(i).at(j) > 0))
  //     {
  //     std::cout << static_cast<int>(test->at(i).at(j)) << " ";
  //     }
  //   }
  //    std::cout << std::endl;
  // }
  std::cout << "In test" << std::endl;
  bool result = unexploredNav.handler();
  if (result)
    std::cout << "True" << std::endl; 
  else 
    std::cout << "False" << std::endl; 

}

void CTEST::test2()
{
  //std::cout << "Test 2: tesing movement" << std::endl;
  cmdvelInterface.updateCmdVel(0.01, 0.2);
}

CTEST::~CTEST()
{
}