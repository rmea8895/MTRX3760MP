#include "../include/cameraTester/camera.h"

static const char WINDOW[] = "Image Processed";

CTagDetect::CTagDetect()
{
    // Init turtlebot3 node
    ROS_INFO("TAG DETECT INIT");
    bool ret = init(nh_);
    // check initialization
    ROS_ASSERT(ret);
}

CTagDetect::~CCamera()
{
    //closing proceedure
    ros::shutdown();
}

void CTagDetect::init()
{
    //Begin WIndow to show image
    ROS_INFO("INIT FIN");
}

void TagCheck(const apriltag_ros::AprilTagDetection& TagsDetected)
{

}

void TagVerify(int id, int pos[2]);
{
    
}


// ------------------------ Main -----------------------------------------------
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "TagDetector");

    //Begin Camera Object
    CTagDetect CTagDetect();

    ROS_INFO("Main Started");

    ros::Time::init();

    //Main Access Point for communications
    ros::Rate loop_rate(30); // 30 Hz
    while (ros::ok())
  {
    // callbacks
    ros::spinOnce();
    //ROS_INFO("SCANNING:");
    loop_rate.sleep();
  }

    return 0;
}

//--------------------