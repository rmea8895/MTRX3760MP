#ifndef EMEGENCY_H
#define EMEGENCY_H

#include "maps.h"
#include "odom.h"
#include "ros/ros.h"
#include <utility>
#include <vector>
#include "mb_interface.h"

class Cemergency 
{
  public:
    virtual bool handler() = 0;
  private:
    double resolution = 0.025; // 2.5 cm
    double mROW = 0.0;
    double mCOL = 0.0;
    
    std::pair<double, double> grid2Cartesian(std::pair<int, int> gridCoords);
    std::pair<int, int> cartesian2Grid(std::pair<double, double> cartCoords);

    typedef std::vector<std::vector<signed char>> _2DArray;
  protected:
    // returns the cartesian coordinates of the 
    // emergency to go to
    std::pair<double, double> findEmergency();

    // Cancels the goal
    void cancelGoal();
    
    

    // ---- interfaces ----
    Cmb_interface mbInterface;
    CMaps mapInterface;
    COdom odomInterface;
};

#endif // EMERGENCY_H