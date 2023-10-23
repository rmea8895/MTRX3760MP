#ifndef TEST_H
#define TEST_H

#include "cmdvel.h"
//#include "laser.h"
#include "odom.h"

/*
 * Test class used to test new topic/subscriber structure
*/
class CTEST
{
  public:
    // Tests cmd velocity publishing
    void test1();
    // Tests laser and odom subscribing
    void test2();
  private:
    // Nodehandle pointer
    ros::NodeHandle *nh_;
    // Example
    COdom odomInterface();


};

#endif // TEST_H