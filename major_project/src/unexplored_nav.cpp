#include "../include/major_project/unexplored_nav.h"
#include "../include/major_project/maps.h"

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


// Need a function to check if a cell has been visited already
bool CUnexploredNav::isValid(int row, int col) {
    bool check;

    // If cell lies out of bounds
    if (row < 0 || col < 0 || row >= ROW || col >= COL) {
        check = false;
    }
    // If cell is already visited
    else if (visited[row][col]) {
        check = false;
    }
    // Otherwise true
    else {
        check = true;
    }
 
    // Otherwise
    return check;
}

// Need a function to perform the BFS algorithm
bool CUnexploredNav::BFS(auto gridPtr, auto costmapPtr, int row, int col)
{
    /*
     * Inputs:
     *  - grid: global gray map
     *  - costmap: costmap indicating near collisions
     *  - vis
     * Outputs:
     *  - noUnexploredBoundaries: bool (false if )
     */

    auto grid = gridPtr->map;
    auto costmap = costmapPtr->costMap;

    // For now, assume grid and costmap have same size
    int ROW = grid.size();
    int COL = grid[0].size();

    // Determine whether there are no more regions to explore
    bool noUnexploredBoundaries = false;

    // Stores indices of the matrix cells
    std::queue<std::pair<int, int>> q;
 
    // Mark the starting cell as visited and push it into the queue
    q.push({ row, col });
    visited[row][col] = true;
 
    // Iterate while the queue is not empty
    while (!q.empty()) {
 
        std::pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;
 
        //std::cout << grid[x][y] << " ";
 
        q.pop();
 
        // Search the adjacent cells (up, down, left, right)
        bool isBoundary = false;
        for (int i = 0; i < 4; i++) {
 
            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            // If the adjacent pixel is not visited before
            if (isValid(adjx, adjy)) {
                q.push({ adjx, adjy });
                visited[adjx][adjy] = true;

                // Logic for if pixels are on the boundary of unexplored regions
                // If adjacent pixel is unexplored and is far away enough from
                // any nearby walls, then add pixel to vector of pairs
                if (grid[adjx][adjy] == PLACEHOLDER && costmap[adjx][adjy] < PLACEHOLDER && isBoundary == false) {
                    // Add pixel by pushing back onto the vector
                    boundaryPixels.push_back(std::make_pair(x, y));
                    // boundaryPixels[std::make_pair(x, y)] = calculateMagnitude(x, y, row, col);

                    // Check if at least one adjacent pixel is unxeplored
                    isBoundary = true;

                    break;
                }
                else {
                    // There are no more unexplored borders
                    noUnexploredBoundaries = true;
                }
            }
        }
    }
}

// Function to compute euclidian distance
double CUnexploredNav::calculateDistance(int x, int y, int row, int col) {
    // Compute dx and dy
    int dx = row - x;
    int dy = col - y;
    // Use double arithmetic for the calculation
    return std::sqrt(static_cast<double>(dx * dx) + static_cast<double>(dy * dy));
}


// Need a function to find closest unexplored point
// (minimum of euclidian distance)
std::pair<int, int> CUnexploredNav::closestPoint() {
    // Get a really high value to begin with
    double minDistance = std::numeric_limits<double>::max();
    std::pair<int, int> minCoords;

    for (int i = 0; i < boundaryPixels.size(); i++) {
        int x = boundaryPixels.at(i).first;
        int y = boundaryPixels.at(i).second;
        double distance = calculateDistance(x, y, row, col);

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

    double xCart = (xGrid - ROW/2) * resolution;
    double yCart = (COL/2 - yGrid) * resolution;

    return std::pair<double, double>(xCart, yCart);
}

std::pair<int, int> CUnexploredNav::cartesian2Grid(std::pair<double, double> cartCoords) {
    double xCart = cartCoords.first;
    double yCart = cartCoords.second;

    int xGrid = (xCart/resolution) + ROW/2;
    int yGrid = COL/2 - (yCart/resolution);

    return std::pair<int, int>(xGrid, yGrid);
}


// Handler to run the functions (like a main)
std::pair<int, int> CUnexploredNav::handler(int row, int col) {
    // row and col are the x and y position of the robot in the grid

    // Run BFS to obtain unexplored boundary points
    BFS(maps.getMapPtr(), maps.getCostMapPtr(), row, col);

    // Run calculateDistance to find the closest of those boundary points
    std::pair<int, int> minCoords;
    minCoords = grid2Cartesian(closestPoint());
    
    return minCoords;
}