#include "../include/major_project/test.h"


CTEST::CTEST(ros::NodeHandlePtr nh_)
 : cmdvelInterface(nh_)
 , mapInterface(nh_)
 , unexploredNav(nh_)
 , fireInterface(nh_)
{
}

void CTEST::test1()
{

  std::cout << "In test" << std::endl;

  bool result = fireInterface.handler();
  if (result)
    std::cout << "True" << std::endl; 
  else 
    std::cout << "False" << std::endl; 

}

void CTEST::test2()
{
  cmdvelInterface.updateCmdVel(0.01, 0.2);
}

CTEST::~CTEST()
{
}