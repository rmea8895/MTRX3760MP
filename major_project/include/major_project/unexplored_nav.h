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
    std::pair<int, int> handler(int row, int col);

  private:
    // Will probably need to change this
    static const int ROW = 5;
    static const int COL = 5;
    // int row;
    // int col;

    // Will probably need to change the inputs to match with smart pointer
    // (object_name->data.at(10,20))
    bool isValid(int row, int col);
    void BFS(auto gridPtr, auto costmapPtr, int row, int col);
    double calculateDistance(int x, int y, int row, int col);
    std::pair<int, int> closestPoint();

    // Array for recording visited pixels
    bool visited[ROW][COL];

    // Vector of pairs for storing the boundary pixels
    std::vector<std::pair<int, int>> boundaryPixels;

    // CUnexploredNav has a CMaps
    CMaps maps;


    
};

#endif // UNEXPLORED_NAV