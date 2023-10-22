#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

/**
 * Publishes to the command velocity topic 
*/
class CCmdVel
{
  public:
    /// Constructor takes pointer to the node handler
    CCmdVel(ros::NodeHandle *nh_);
    ~CCmdVel();
    /// Updates the command velocity of the turtlebot
    void updateCmdVel(double linear, double angular);
  private:
    /// cmd velcocity node handler
    ros::Publisher cmd_vel_pub_;
    /// Initialisation function
    bool init();
};