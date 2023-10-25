#include "../include/major_project/mb_interface.h"


Cmb_interface::Cmb_interface(ros::NodeHandlePtr nh_)
{
  ROS_INFO("move_base/goal interface init");
  bool ret = init(nh_);
  ROS_ASSERT(ret);
}



Cmb_interface::~Cmb_interface()
{
}

bool Cmb_interface::init(ros::NodeHandlePtr nh_)
{
  move_base_pub = nh_->advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
  actionlib_cancel_pub = nh_->advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1);
  return true;
}

void Cmb_interface::cancelGoal()
{
  actionlib_msgs::GoalID test;

  test.id = "";
  actionlib_cancel_pub.publish(test);
}

void Cmb_interface::sendGoal()
{
  geometry_msgs::PoseStamped test;

  test.header.frame_id = "map";
  test.pose.position.x = 0.0;
  test.pose.position.y = 0.0;
  test.pose.orientation.w = 0.7514451452616765;
  test.pose.orientation.z = 0.659795569599143;
  move_base_pub.publish(test);
}

