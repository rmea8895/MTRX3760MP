#ifndef TAGDETECT_H
#define TAGDETECT_H

#define QUEUE_SIZE 1
#define FIRETAGCODE 232
#define PERSONTAGCODE 123

// Are all these includes nessisary?
#include "ros/ros.h"
#include <iostream>
#include <string>     
#include <array>  
#include "apriltag_ros/AprilTagDetection.h" 
#include <std_msgs/Bool.h>     
//#include "tag_detector/detect.h"              // for mScanAngles

//#include "tag_detector/detect.h"

class CTagDetect
{
    private:
    ros::NodeHandle nh_;
    ros::Publisher pub_fireDetect_;
    ros::Publisher pub_personDetect_;
    ros::Subscriber sub_aprilTag_;

    void TagCheck(const apriltag_ros::AprilTagDetectionPtr& TagsDetected);
    void TagVerify(int id, float size_tag );

    // tag_detector::detect det_fire;
    // tag_detector::detect det_person;
    std_msgs::Bool det_fire;
    std_msgs::Bool det_person;

    //variables
    int id;
    int pos[2];

    //Camera Statics
    int cam_width = 640;
    int cam_height = 480;

    public:
    //initalise members
    CTagDetect();

    //exit strategy 
    ~CTagDetect();

    //initalise subscribers and publishers
    bool init();
};

#endif // TAGDETECT_H 