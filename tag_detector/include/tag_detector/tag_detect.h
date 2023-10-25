#ifndef TAGDETECT_H
#define TAGDETECT_H

#define QUEUE_SIZE 1
#define FIRETAGCODE 232
#define PERSONTAGCODE 123

// Are all these includes nessisary?
#include "ros/ros.h"
#include <iostream>
#include <string>     
#include <array>                         // for mScanAngles


class CTagDetect
{
    private:
    ros::NodeHandle nh_;
    ros::Publisher pub_fireDetect_;
    ros::Publisher pub_personDetect_;
    ros::Sybscriber sub_aprilTag_;

    void TagCheck(const apriltag_ros::AprilTagDetection& TagsDetected);
    void TagVerify(int id, int pos[2]);

    //msgs to detect if red or not
    message_generation::detect det_fire;
    message_generation::detect det_person;

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
    void init();

};

#endif // TAGDETECT_H 