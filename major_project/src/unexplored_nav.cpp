#include "../include/major_project/unexplored_nav.h"

#include <limits>
#include <utility>
#include <queue>
#include <iostream>
#include <cmath>


/*
1. Use the regular occupancy grid (/map) to find pixels that are on the boundary
	of unexplored. These

2. Use /move_base global cost map to remove any points that are red (close to a
	nearby wall)
*/

// Define constants


// THIS NEEDS REFACTORING TO MANAGE ROW, COL, visited

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
        std::cout << "Out of bounds" << std::endl;
        check = false;
    }
    else {
        check = true;
    }
    // // If cell is already visited
    // else if (visited[xGrid][yGrid]) {
    //     std::cout << "Visited" << std::endl;
    //     check = false;
    // }
    // Otherwise true
    
 
    // Otherwise
    return check;
}
bool CUnexploredNav::searchBoundaries(_2DArray* gridPtr, _2DArray* costmapPtr)
{
    _2DArray grid = *gridPtr;
    _2DArray costmap = *costmapPtr;

    // For now, assume grid and costmap have same size
    int ROW = grid.size();
    int COL = grid[0].size();

    mROW = ROW;
    mCOL = COL;

    // std::pair<int , int> currentPosGrid = cartesian2Grid(currentPosCart);
    // int xGrid = currentPosGrid.first;
    // int yGrid = currentPosGrid.second;
    std::vector<std::pair<int, int>> local_boundaryPixels;

    std::cout << ROW << std::endl;
    std::cout << COL << std::endl;
    // loop over map
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if(
                grid[i][j] == 0
                && costmap[i][j] < 90
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
                            //std::cout << "Boundary found " << i << "," << j << std::endl;

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
// // Need a function to perform the BFS algorithm
// bool CUnexploredNav::BFS(_2DArray* gridPtr, _2DArray* costmapPtr, std::pair<double, double> currentPosCart)
// {
//     /*
//      * Inputs:
//      *  - grid: global gray map
//      *  - costmap: costmap indicating near collisions
//      *  - vis
//      * Outputs:
//      *  - UnexploredBoundaries: bool (false if )
//      */

//     _2DArray grid = *gridPtr;
//     _2DArray costmap = *costmapPtr;

//     // For now, assume grid and costmap have same size
//     int ROW = grid.size();
//     int COL = grid[0].size();

//     mROW = ROW;
//     mCOL = COL;

//     std::pair<int , int> currentPosGrid = cartesian2Grid(currentPosCart);
//     int xGrid = currentPosGrid.first;
//     int yGrid = currentPosGrid.second;

//     // Visited array shiz
//     visited.resize(ROW);
//     for(int i = 0; i < ROW; i++)
//     {
//         visited[i].resize(COL);
//     }

//     // initialise visted with false
//     for(int i = 0; i < ROW; i ++)
//     { 
//         for(int j = 0; j < COL; j++)
//         {
//             visited[i][j] = false;
//         }
//     }

//     // Determine whether there are no more regions to explore
//     //bool UnexploredBoundaries = true;
    
//     std::vector<std::pair<int, int>> boundaryPixels;
//     // Stores indices of the matrix cells
//     std::queue<std::pair<int, int>> q;
 
//     // Mark the starting cell as visited and push it into the queue
//     q.push({ xGrid, yGrid });
//     visited[xGrid][yGrid] = true;
 
//     // Iterate while the queue is not empty
//     while (!q.empty()) {
 
//         std::pair<int, int> cell = q.front();
//         int x = cell.first;
//         int y = cell.second;
 
//         //std::cout << static_cast<int>(grid[x][y]) << " ";
 
//         q.pop();
 
//         // Search the adjacent cells (up, down, left, right)
//         bool isBoundary = false;
//         for (int i = 0; i < 4; i++) {
 
//             int adjx = x + dRow[i];
//             int adjy = y + dCol[i];
//             //
//             // If the adjacent pixel is not visited before
//             if (isValid(adjx, adjy)) {
//                 visited[adjx][adjy] = true;

//                 // Logic for if pixels are on the boundary of unexplored regions
//                 // If adjacent pixel is unexplored and is far away enough from
//                 // any nearby walls, then add pixel to vector of pairs
//                 if (
//                     grid[adjx][adjy] == -1
//                         && costmap[adjx][adjy] < 50 
//                         && isBoundary == false
//                         ) {
                    
//                     std::cout << "BHS working!" << std::endl;
//                     // Add pixel by pushing back onto the vector
//                     boundaryPixels.push_back(std::make_pair(x, y));
//                     // boundaryPixels[std::make_pair(x, y)] = calculateMagnitude(x, y, row, col);

//                     // Check if at least one adjacent pixel is unxeplored
//                     isBoundary = true;

//                     break;
//                 }
//                 else {
//                     q.push({ adjx, adjy });
//                 }
//             }
//         }
//     }
//     return !boundaryPixels.empty();
// }

// Function to compute euclidian distance
double CUnexploredNav::calculateDistance(int x, int y, int xGrid, int yGrid) {
    // Compute dx and dy
    int dx = xGrid - x;
    int dy = yGrid - y;
    // Use double arithmetic for the calculation
    return std::sqrt(static_cast<double>(dx * dx) + static_cast<double>(dy * dy));
}

// Need a function to find closest unexplored point
// (minimum of euclidian distance)
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
    std::cout << "Min coords:" << minCoords.first << ", " << minCoords.second << std::endl;

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


// Handler to run the functions (like a main)
bool CUnexploredNav::handler() {

    bool ret = false;
  
    // row and col are the x and y position of the robot in the grid
    std::pair<double, double> currentPosCart = odomInterface.getPos();
    std::cout << "Current position" << currentPosCart.first << ", "<< currentPosCart.second << std::endl;

    // Run BFS to obtain unexplored boundary points
    ret = searchBoundaries(mapInterface.getMapPtr(), mapInterface.getCostMapPtr());
    //
    std::pair<int , int> currentPosGrid = cartesian2Grid(currentPosCart);
    int xGrid = currentPosGrid.first;
    int yGrid = currentPosGrid.second;
    // Run calculateDistance to find the closest of those boundary points
    std::pair<double, double> minCoords = grid2Cartesian(closestPoint(xGrid, yGrid));
    
    std::cout << "Closest coordinates:" << minCoords.first << ", "  << minCoords.second<< std::endl;
    
    // If sucessfull send the goal to 
    if(ret)
        mbInterface.sendGoal(minCoords);
    return ret;
}