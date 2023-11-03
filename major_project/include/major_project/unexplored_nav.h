#ifndef UNEXPLORED_NAV
#define UNEXPLORED_NAV

#include <utility>
#include <queue>
#include <vector>
#include <iostream>

#include "odom.h"
#include "ros/ros.h"
#include "maps.h"
#include "mb_interface.h"
#include "odom.h"


// ----- Forward Declarations -----
class CMaps;
class Cmb_interface;
class COdom;

/*
 * Unexplored navigation class uses the move base interface and the maps interface to 
 * find unexplored points on the surroundings of the rescue bot. 
 */
class CUnexploredNav
{
  public:
    CUnexploredNav(ros::NodeHandlePtr nh_);
    ~CUnexploredNav();

    /**
     * @brief handles the unepxlored navigation for the rescue bot
     * 
     * @return true if there is a valid unexplored grid cell
     * @return false if there is no more unexplored grid cells
     */
    bool handler();

  private:
    // ----- Interfaces -----
    CMaps mapInterface;
    Cmb_interface mbInterface;
    COdom odomInterface;

    // For conveniance
    typedef std::vector<std::vector<signed char>> _2DVector;

    
    // ----- Member Functions -----
    // Checks if a boundary grid point is valid
    bool isValid(int xGrid, int yGrid);

    // Returns true if there are unexplored boundaries on the costmap
    bool searchBoundaries(_2DVector* gridPtr, _2DVector* costmapPtr);

    // Calculates the euclidiean between (x,y) and (row,col)
    double calculateDistance(int x, int y, int row, int col);

    // Returns the closest point 
    std::pair<int, int> closestPoint(int xGrid,int yGrid);

    // Returns the closest boundary pixel to the given pair
    std::pair<double, double> grid2Cartesian(std::pair<int, int> gridCoords);

    // Converts the given cartesian coordinates to grid coordinates
    std::pair<int, int> cartesian2Grid(std::pair<double, double> cartCoords);

    // ----- Variables -----
    // Number of rows and columns in the given occupancy grids
    int mROW = 0;
    int mCOL = 0;

    //
    const int _max_wall_threshold = 50;
    const int _unexplored_cell = 0;

    // Resolution for distance per grid element
    const double resolution = 0.025; 

    // Masks used to search the adjacent pixels
    const int dRow[4] = { -1, 0, 1, 0 };
    const int dCol[4] = { 0, 1, 0, -1 };

    // Vector of pairs for storing the boundary pixels
    std::vector<std::pair<int, int>> boundaryPixels;
};

#endif // UNEXPLORED_NAV