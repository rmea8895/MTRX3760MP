#ifndef FIRE_H
#define FIRE_H

#include "emergency.h"

class CFire: public Cemergency
{
  public:
    CFire(ros::NodeHandlePtr nh_);
    ~CFire();

    bool handler();
};

#endif //FIRE_H