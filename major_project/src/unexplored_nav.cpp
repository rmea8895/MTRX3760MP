#include "../include/major_project/unexplored_nav.h"
#include <limits>
#include <utility>
#include <queue>
#include <iostream>
#include <cmath>

CUnexploredNav::CUnexploredNav(ros::NodeHandlePtr nh_)
    : mapInterface(nh_)
    , mbInterface(nh_)
    , odomInterface(nh_)
{
    ROS_INFO("Unexplored nav INIT");
}

CUnexploredNav::~CUnexploredNav()
{}

// Need a function to check if a cell has been visited already
bool CUnexploredNav::isValid(int xGrid, int yGrid) {
    bool check = false;

    // If cell lies out of bounds
    if (xGrid < 0 || yGrid < 0 || xGrid >= mROW || yGrid >= mCOL) {
        check = false;
    }
    else {
        check = true;
    }
 
    // Otherwise
    return check;
}

bool CUnexploredNav::searchBoundaries(_2DVector* gridPtr, _2DVector* costmapPtr)
{
    _2DVector grid = *gridPtr;
    _2DVector costmap = *costmapPtr;

    // For now, assume grid and costmap have same size
    int ROW = grid.size();
    int COL = grid[0].size();

    mROW = ROW;
    mCOL = COL;

    // boundary pixels vector
    std::vector<std::pair<int, int>> local_boundaryPixels;

    // loop over entire map and find boundary points
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if(
                grid[i][j] == _unexplored_cell
                && costmap[i][j] < _max_wall_threshold
            )
            {
                for(int k = 0; k < 4; k++)
                {
                    int adjx = i + dRow[k];
                    int adjy = j + dCol[k];
                    if(isValid(adjx, adjy))
                    {
                        if(grid[adjx][adjy] == -1)
                        {
                            // Boundary point is found
                            local_boundaryPixels.push_back(std::make_pair(i,j));
                        }
                    }
                }
            }
        }
    }
    boundaryPixels = local_boundaryPixels;
    return !local_boundaryPixels.empty();
}

// Function to compute euclidian distance
double CUnexploredNav::calculateDistance(int x, int y, int xGrid, int yGrid) {
    // Compute dx and dy
    int dx = xGrid - x;
    int dy = yGrid - y;
    // Use double arithmetic for the calculation
    return std::sqrt(static_cast<double>(dx * dx) + static_cast<double>(dy * dy));
}


std::pair<int, int> CUnexploredNav::closestPoint(int xGrid, int yGrid) {
    // Get a really high value to begin with
    double minDistance = std::numeric_limits<double>::max();
    std::pair<int, int> minCoords;
    for (int i = 0; i < boundaryPixels.size(); i++) {
        int x = boundaryPixels.at(i).first;
        int y = boundaryPixels.at(i).second;
        double distance = calculateDistance(x, y, xGrid, yGrid);

        if (distance < minDistance) {
            minDistance = distance;
            minCoords = boundaryPixels.at(i);
        }
    }
    return minCoords;
}

std::pair<double, double> CUnexploredNav::grid2Cartesian(std::pair<int, int> gridCoords) {
    int xGrid = gridCoords.first;
    int yGrid = gridCoords.second;

    double xCart = (xGrid - mROW/2) * resolution;
    double yCart = -(mCOL/2 - yGrid) * resolution;

    return std::make_pair(xCart, yCart);
}

std::pair<int, int> CUnexploredNav::cartesian2Grid(std::pair<double, double> cartCoords) {
    double xCart = cartCoords.first;
    double yCart = cartCoords.second;

    int xGrid = (xCart/resolution) + mROW/2;
    int yGrid = mCOL/2 - (yCart/resolution);

    return std::pair<int, int>(xGrid, yGrid);
}


bool CUnexploredNav::handler() {
    bool ret = false;
  
    // row and col are the x and y position of the robot in the grid
    std::pair<double, double> currentPosCart = odomInterface.getPos();

    // Run array search to obtain unexplored boundary points
    ret = searchBoundaries(mapInterface.getMapPtr(), mapInterface.getCostMapPtr());

    // Convert current position from odom data to grid coordinates
    std::pair<int , int> currentPosGrid = cartesian2Grid(currentPosCart);
    int xGrid = currentPosGrid.first;
    int yGrid = currentPosGrid.second;

    // Run calculateDistance to find the closest of those boundary points
    std::pair<double, double> minCoords = grid2Cartesian(closestPoint(xGrid, yGrid));
        
    // If sucessfull send the goal to the move base interface
    if(ret)
        mbInterface.sendGoal(minCoords);
    return ret;
}