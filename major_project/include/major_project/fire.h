#ifndef FIRE_H
#define FIRE_H

#include "emergency.h"

/**
 * Derived class of the emergency class.
 * Is called apon sucesfull identification of fire april-tag
 */
class CFire: public Cemergency
{
  public:
    CFire(ros::NodeHandlePtr nh_);
    ~CFire();

    bool handler();
};

#endif //FIRE_H