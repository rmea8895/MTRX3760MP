#include "../include/major_project/emergency.h"

void Cemergency::cancelGoal()
{
  mbInterface.cancelGoal();
}

Cemergency::~Cemergency()
{}

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
  std::cout << "h1" << std::endl;
  std::pair<double, double> currentPosCart = odomInterface.getPos();

  std::pair<int, int> currentPosGrid = cartesian2Grid(currentPosCart);
  // get angle to rise run of yaw-90 for RHS point of front yaw
  int rise;
  int run;
  //AngleToRiseRun((odomInterface.getYaw()), &rise, &run);
  std::cout << "Yaw:" << odomInterface.getYaw() << std::endl;
  

  if (odomInterface.getYaw() >= (3/4)*2*M_PI){
      AngleToRiseRun(M_PI*2 - (odomInterface.getYaw()), &rise, &run);
  }
  else{
      AngleToRiseRun((odomInterface.getYaw() - M_PI/2), &rise, &run);
  }
  std::cout << "RiseRun:" << rise << ", " <<  run << std::endl;

  bool wallFound = false;
  // 
  int riseCount = 0;
  int runCount = 0;
  int i = currentPosGrid.first, j = 800 - currentPosGrid.second;

  while(isValid(i,j) && !wallFound)
  {
    for(int k = 0; k < abs(rise); k++)
    {
      j += (rise < 0) ? -1 : 1;
      if (isValid(i,j))
      {
        // From cost map 0 is free, -1 is unfound and 100 is wall
        //std::cout << static_cast<int>(costMapPtr[i][j]) << std::endl;
        wallFound = (mapPtr[i][j] == 1) || (costMapPtr[i][j] > 15);
      }
      
    }
    for(int k = 0; k < abs(run); k++)
    {
      i += (run < 0) ? -1 : 1;
      if (isValid(i,j))
      {
        //std::cout << static_cast<int>(costMapPtr[i][j]) << std::endl;
        // From cost map 0 is free, -1 is unfound and 100 is wall
        wallFound = (mapPtr[i][j] == 1) || (costMapPtr[i][j] > 15);
      }
    }
    std::cout << "ij" << i << ", " << j << std::endl;
    
  }
  std::cout << "grid goto:" << i << ", "<< j << std::endl;
  std::cout << "grid current:" << currentPosGrid.first << ", " << currentPosGrid.second << std::endl;
  std::cout << "odom current" << currentPosCart.first << ", " << currentPosCart.second << std::endl;
  if (wallFound)
    std::cout << "True" << std::endl; 
  else 
    std::cout << "False" << std::endl; 

  if(!wallFound)
    return currentPosCart;
  else
    return grid2Cartesian(std::make_pair(i, j));
  //return currentPosCart;
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
 
    // Otherwise
    return check;
}

void Cemergency::AngleToRiseRun(double angle, int* rise, int* run) {
    double x = std::sin(angle);
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
    std::cout << "xy" << xCart << ", " << yCart << std::endl;
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