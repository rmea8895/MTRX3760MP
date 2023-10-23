#ifndef UNEXPLORED_NAV
#define UNEXPLORED_NAV

#include <utility>
#include <queue>

/**
 * Unexplored navigation class
 * 1) finds boundary points ...
*/
class CUnexploredNav 
{
  public:
    CUnexploredNav();

  private:
    // Will probably need to change this
    static const int ROW = 5;
    static const int COL = 5;

    // Will probably need to change the inputs to match with smart pointer
    // (object_name->data.at(10,20))
    bool isValid(bool vis[][COL], int row, int col);
    void BFS(int grid[][COL], int costmap[][COL], bool vis[][COL], int row, int col);

    // Array for recording visited pixels
    bool visited[ROW][COL];

    // Vector of pairs for storing the boundary pixels
    std::vector<std::pair<int, int>> boundaryPixels;

    
};

#endif // UNEXPLORED_NAV