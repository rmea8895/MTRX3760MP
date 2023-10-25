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




// Forward declare CMaps
class CMaps;
class Cmb_interface;
class COdom;
/*
 * Unexplored navigation class
 * 1) finds boundary points ...
 */

class CUnexploredNav
{
  public:
    CUnexploredNav(ros::NodeHandlePtr nh_);
    ~CUnexploredNav();
    // Handler runs the BFS and calculateDistance to find closest point
    bool handler();

  private:
    // Interfaces
    CMaps mapInterface;
    Cmb_interface mbInterface;
    COdom odomInterface;
    // For conveniance
    typedef std::vector<std::vector<signed char>> _2DArray;
    
    // -- Function declarations ------------------------------------------------
    bool isValid(int xGrid, int yGrid);
    //bool BFS(_2DArray* gridPtr, _2DArray* costmapPtr, std::pair<double, double> currentPosCart);  // Will need to change function input data types
    bool searchBoundaries(_2DArray* gridPtr, _2DArray* costmapPtr);
    double calculateDistance(int x, int y, int row, int col);
    std::pair<int, int> closestPoint(int xGrid,int yGrid);
    std::pair<double, double> grid2Cartesian(std::pair<int, int> gridCoords);
    std::pair<int, int> cartesian2Grid(std::pair<double, double> cartCoords);
    // -- Data declarations ----------------------------------------------------
    int mROW = 0;
    int mCOL = 0;
    //
    //_2DArray visited;
    //

    double resolution = 0.025; // Resolution for distance per grid element
    const int dRow[4] = { -1, 0, 1, 0 };
    const int dCol[4] = { 0, 1, 0, -1 };

    // Vector of pairs for storing the boundary pixels
    std::vector<std::pair<int, int>> boundaryPixels;

};

#endif // UNEXPLORED_NAV