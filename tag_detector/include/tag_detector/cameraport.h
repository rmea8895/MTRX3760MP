#ifndef CAMERA_H
#define CAMERA_H

#define QUEUE_SIZE 1
#define IMAGE_TOPIC "/tag_detections_image"
#define THRESH_RED_IMAGE 0.7
#define THRESH_RED_PIXEL 0.7

// Are all these includes nessisary?
#include "ros/ros.h"
#include <iostream>
#include <string>     
#include <array>                         // for mScanAngles
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. Refer to: http://www.ros.org/doc/api/sensor_msgs/html/namespacesensor__msgs_1_1image__encodings.html for more info.
#include <sensor_msgs/image_encodings.h>
//Include headers for OpenCV Image processing
#include <opencv2/imgproc/imgproc.hpp>
//Include headers for OpenCV GUI handling
#include <opencv2/highgui/highgui.hpp>

#include <sensor_msgs/Image.h>


class CCamera
{
    private:
    ros::NodeHandle nh_;

    image_transport::ImageTransport it_;
    image_transport::Subscriber sub_img_;

    void imageCallback(const sensor_msgs::ImageConstPtr& original_image);


    public:
    //initalise members
    CCamera(std::string image_topic);

    //exit strategy 
    ~CCamera();

    //initalise subscribers and publishers
    void init();

};

#endif // WALLFOLLWER_H 