#ifndef EMEGENCY_H
#define EMEGENCY_H

#include "maps.h"
#include "odom.h"
#include "ros/ros.h"
#include <utility>
#include <math.h>
#include <vector>
#include "mb_interface.h"

/**
 * This is a base class used for the fire and person classes.
 * The main functionality of ths
 */
class Cemergency 
{
  public:
    // purely virtual handler for derived classes to implement
    virtual bool handler() = 0;
    Cemergency(ros::NodeHandlePtr nh_);
    ~Cemergency();
  private:
    // Cell resolution in m (const)
    double resolution = 0.025; // 2.5 cm

    // Rows and column counters
    double mROW = 0.0;
    double mCOL = 0.0;

    // Converts the grid coordinates to cartesian 
    std::pair<double, double> grid2Cartesian(std::pair<int, int> gridCoords);
    // Converts carteasian coordinates to the closest gird coordinates
    std::pair<int, int> cartesian2Grid(std::pair<double, double> cartCoords);

    // Converts an input angle (rad) to rise and run integers
    void AngleToRiseRun(double angle, int* rise, int* run);
    
    // Returns true if the given grid coordinates are valid
    bool isValid(int xGrid, int yGrid);

    // 2D Vector typedef
    typedef std::vector<std::vector<signed char>> _2DVector;

    // 
    const int _cost_map_wall_threshold = 15;

  protected:
    /**
     * @brief returns the cartesian coordinates of the emergency to go to.
     * 
     * @return std::pair<double, double> the coordates of the emergency to go to.
     * 
     * If no valid wall is found between the bot and the emergency it will return the 
     * coordinates of the current bot location.
     * 
     * This function will quantise the yaw of the emergency into rise and run grid integers
     * a search will then look for the closest wall in the cost map using the calculated rise and run.
     */
    std::pair<double, double> findEmergency();

    // Cancels the goal
    void cancelGoal();

    // ---- interfaces ----
    Cmb_interface mbInterface;
    CMaps mapInterface;
    COdom odomInterface;
};

#endif // EMERGENCY_H