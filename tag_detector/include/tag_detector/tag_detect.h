#ifndef CAMERA_H
#define CAMERA_H

#define QUEUE_SIZE 1
#define IMAGE_TOPIC "/camera/rgb/image_raw"
#define THRESH_RED_IMAGE 0.7
#define THRESH_RED_PIXEL 0.7

// Are all these includes nessisary?
#include "ros/ros.h"
#include <iostream>
#include <string>     
#include <array>                         // for mScanAngles


class CTagDetect
{
    private:
    ros::NodeHandle nh_;
    ros::Publisher pub_tagDetect_;

    void TagCheck(const apriltag_ros::AprilTagDetection& TagsDetected);
    void TagVerify(int id, int pos[2]);

    public:
    //initalise members
    CTagDetect();

    //exit strategy 
    ~CTagDetect();

    //initalise subscribers and publishers
    void init();

};

#endif // WALLFOLLWER_H 