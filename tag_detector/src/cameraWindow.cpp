#include "../include/cameraTester/camera.h"

static const char WINDOW[] = "Image Processed";

CCamera::CCamera(std::string image_topic)
 : it_(nh_)
{
  // Init turtlebot3 node
  ROS_INFO("CAMERA INIT");

  //Subscribe to cammer image
  sub_img_ = it_.subscribe( image_topic, QUEUE_SIZE, &CCamera::imageCallback, this);
  
  //Publish the red detection booleen if true or false
  pub_img_ = nh_.advertise<std_msgs::Bool>("Red_bool", 1000);
  
}

CCamera::~CCamera()
{
    //closing proceedure
  cv::destroyWindow(WINDOW);
  ros::shutdown();
}

void CCamera::init()
{
    //Begin WIndow to show image
    cv::namedWindow(WINDOW, cv::WINDOW_AUTOSIZE);

    ROS_INFO("INIT FIN");
}

void CCamera::imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{
    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
    
    cv_ptr = cv_bridge::toCvCopy(original_image, sensor_msgs::image_encodings::BGR8);

    //Display the image using OpenCV
    cv::imshow("Image", cv_ptr->image);
    //Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
    cv::waitKey(3);


}
