#ifndef TEST_H
#define TEST_H

#include "cmdvel.h"
#include "ros/ros.h"
#include <memory.h>
#include "odom.h"
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
    void test1(double Yaw);
    // Tests cmd velocity publishing
    void test2();
  private:
    // Example
    CCmdVel cmdvelInterface;


};

#endif // TEST_H