#include "../include/major_project/unexplored_nav.h"
#include <utility>
#include <queue>
#include <iostream>


/*
1. Use the regular occupancy grid (/map) to find pixels that are on the boundary
	of unexplored. These

2. Use /move_base global cost map to remove any points that are red (close to a
	nearby wall)
*/

// Define constants
// Direction arrays are used to traverse the adjacent cells
const int dRow[] = {-1, 0, 1, 0};
const int dCol[] = {0, 1, 0, -1};

/*
Smart pointer data

*/

// Constructor
CUnexploredNav::CUnexploredNav() {
    //
}


// Need a function to check if a cell has been visited already
bool CUnexploredNav::isValid(bool vis[][COL], int row, int col) {
    bool check;

    // If cell lies out of bounds
    if (row < 0 || col < 0 || row >= ROW || col >= COL) {
        check = false;
    }
    // If cell is already visited
    else if (vis[row][col]) {
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
void CUnexploredNav::BFS(int grid[][COL], int costmap[][COL], bool vis[][COL], int row, int col)
{
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
 
        std::cout << grid[x][y] << " ";
 
        q.pop();
 
        // Search the adjacent cells (up, down, left, right)
        bool isBoundary = false;
        for (int i = 0; i < 4; i++) {
 
            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            // If the adjacent pixel is not visited before
            if (isValid(visited, adjx, adjy)) {
                q.push({ adjx, adjy });
                vis[adjx][adjy] = true;

                // Logic for if pixels are on the boundary of unexplored regions
                // If adjacent pixel is unexplored and is far away enough from
                // any nearby walls, then add pixel to vector of pairs
                if (grid[adjx][adjy] == PLACEHOLDER && costmap[adjx][adjy] < PLACEHOLDER && isBoundary == false) {
                    // Add pixel by pushing back onto the vector
                    boundaryPixels.push_back(std::make_pair(x, y));

                    // Check if at least one adjacent pixel is unxeplored
                    isBoundary = true;
                }
            }
        }
    }
}