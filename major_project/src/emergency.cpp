#include "../include/major_project/emergency.h"

void Cemergency::cancelGoal()
{
  mbInterface.cancelGoal();
}

std::pair<double, double> Cemergency::findEmergency()
{
  _2DArray mapPtr =  *mapInterface.getMapPtr();
  _2DArray costMapPtr =  *mapInterface.getCostMapPtr();

  // use odom yaw to 
  // For now, assume grid and costmap have same size
  int ROW = mapPtr.size();
  int COL = mapPtr[0].size();

  mROW = ROW;
  mCOL = COL;

  std::pair<double, double> currentPosCart = odomInterface.getPos();

  std::pair<int, int> currentPosGrid = cartesian2Grid(currentPosCart);
  // get angle to rise run of yaw-90 for RHS point of front yaw
  int rise;
  int run;
  if (odomInterface.getYaw() >= (3/4)*2*M_PI){
      AngleToRiseRun(M_PI*2 - (odomInterface.getYaw()), &rise, &run);
  }
  else{
      AngleToRiseRun((odomInterface.getYaw() - M_PI/2), &rise, &run);
  }

  bool wallFound = false;
  // 
  int riseCount = 0;
  int runCount = 0;
  int i = 0, j = 0;

  //std::pair<int, int> wall;

  while(isValid(i,j) && !wallFound)
  {
    for(int k = 0; k < abs(run); k++)
    {
      j += (run < 0) ? -1 : 1;
      // From cost map 0 is free, -1 is unfound and 100 is wall
      wallFound = mapPtr[i][j] == 1 || (costMapPtr[i][j] > 80);
    }
    for(int k = 0; k < abs(rise); k++)
    {
      i += (rise < 0) ? -1 : 1;
      // From cost map 0 is free, -1 is unfound and 100 is wall
      wallFound = mapPtr[i][j] == 1 || (costMapPtr[i][j] > 80);
    }
    
  }

  if(!wallFound)
    return currentPosCart;
  else
    return grid2Cartesian(std::make_pair(i, j));
}

bool Cemergency::isValid(int xGrid, int yGrid) {
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

void Cemergency::AngleToRiseRun(double angle, int* rise, int* run) {
    double x = -std::sin(angle);
    double y = std::cos(angle);

    // Determine the smaller of x and y
    double smaller = std::min(std::abs(x), std::abs(y));

    if (smaller == 0.0) {
        *rise = 1;
        *run = 1;
    } else {
        double length = 1.0 / smaller;

        *rise = static_cast<int>(y * length);
        *run = static_cast<int>(x * length);
    }
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

    return std::make_pair(xGrid, yGrid);
}

Cemergency::Cemergency(ros::NodeHandlePtr nh_)
  : mbInterface(nh_)
  , mapInterface(nh_)
  , odomInterface(nh_)
{

}