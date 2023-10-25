#ifndef UNEXPLORED_NAV
#define UNEXPLORED_NAV

#include <utility>
#include <queue>
#include <unordered_map>

#include "../include/major_project/maps.h"

// Forward declare CMaps
class CMaps;

/*
 * Unexplored navigation class
 * 1) finds boundary points ...
 */

class CUnexploredNav
{
  public:
    // Handler runs the BFS and calculateDistance to find closest point
    std::pair<int, int> handler(int row, int col);

  private:
    // -- Function declarations ------------------------------------------------
    bool isValid(int row, int col);
    bool BFS(auto gridPtr, auto costmapPtr, int row, int col);  // Will need to change function input data types
    double calculateDistance(int x, int y, int row, int col);
    std::pair<int, int> closestPoint();
    std::pair<double, double> grid2Cartesian(std::pair<int, int> gridCoords);

    // -- Data declarations ----------------------------------------------------
    bool visited[ROW][COL];   // Array for recording visited pixels -- WILL need to change how ROW and COL are accessed
    const double resolution = 0.025; // Resolution for distance per grid element
    const int dRow[4] = { -1, 0, 1, 0 };
    const int dCol[4] = { 0, 1, 0, -1 };

    // Vector of pairs for storing the boundary pixels
    std::vector<std::pair<int, int>> boundaryPixels;

    // CUnexploredNav has a CMaps
    CMaps maps;
};

#endif // UNEXPLORED_NAV