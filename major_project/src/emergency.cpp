#include "../include/major_project/emergency.h"

void Cemergency::cancelGoal()
{
  mbInterface.cancelGoal();
}

std::pair<double, double> Cemergency::findEmergency()
{
  _2DArray* mapPtr =  mbInterface.getMapPtr();
  _2DArray* costMapPtr =  mbInterface.getCostMapPtr();

  // use odom yaw to 
  // For now, assume grid and costmap have same size
  int ROW = mapPtr.size();
  int COL = mapPtr[0].size();

  mROW = ROW;
  mCOL = COL;



}


std::pair<double, double> Cemergency::grid2Cartesian(std::pair<int, int> gridCoords) {
    int xGrid = gridCoords.first;
    int yGrid = gridCoords.second;

    double xCart = (xGrid - mROW/2) * resolution;
    double yCart = -(mCOL/2 - yGrid) * resolution;

    return std::make_pair(xCart, yCart);
}

std::pair<int, int> Cemergency::cartesian2Grid(std::pair<double, double> cartCoords) {
    double xCart = cartCoords.first;
    double yCart = cartCoords.second;

    int xGrid = (xCart/resolution) + mROW/2;
    int yGrid = mCOL/2 - (yCart/resolution);

    return std::pair<int, int>(xGrid, yGrid);
}
