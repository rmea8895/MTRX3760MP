#ifndef TEST_H
#define TEST_H

#include "cmdvel.h"
#include "maps.h"
#include "mb_interface.h"
#include "unexplored_nav.h"
#include "fire.h"
#include "ros/ros.h"
#include <memory.h>
#include "odom.h"
#include <vector>
#include <iostream>

/*
 * Test class used to test new topic/subscriber structure
*/
class CTEST
{
  public:
    CTEST(ros::NodeHandlePtr nh_);
    ~CTEST();

    // Tests odom subscribing
    void test1();
    // Tests cmd velocity publishing
    void test2();
  private:
    // Example Interfaces
    CCmdVel cmdvelInterface;
    CMaps mapInterface;
    CUnexploredNav unexploredNav;
    CFire fireInterface;



};

#endif // TEST_H