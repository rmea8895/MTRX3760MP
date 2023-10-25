#include "../include/cameraTester/cameraport.h"
#include "../include/cameraTester/tag_detect.h"

static const char WINDOW[] = "Image Processed";

CTagDetect::CTagDetect()
{
    // Init turtlebot3 node
    ROS_INFO("TAG DETECT INIT");
    bool ret = init(nh_);
    // check initialization
    ROS_ASSERT(ret);

    //Subscribe to apriltag
    sub_aprilTag_ = nh_.subscribe( "/tag_detections", QUEUE_SIZE, &CTagDetect::TagCheck, this);

    //Publishers to main
    pub_fireDetect_ = nh_.advertise<message_generation::detect>("Fire_det", 1000);
    pub_personDetect_ = nh_.advertise<message_generation::detect>("Person_det", 1000);
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
    if(TagsDetected.id == [])
    {
        print("NO TAG DETECTED");
    }
    else
    {
        //Number of tags detected
        int no_tags = sizeof(TagsDetected.id)/sizeof(TagsDetected.id[0])
        
        for(int i = 0; i < no_tags; i++)
        {
            TagVerify(TagsDetected.id[i], TagsDetected.size[i] );
        }
    }
    
}

void TagVerify(int id, float size_tag);
{
    //FIRE TAG CHECKER
    if(id == FIRETAGCODE){
        det_fire.detected = true;
        det_fire.size = size_tag;
    }else{
        det_fire.detected = false;
        det_fire.size = 0;
    }
    //PERSON TAG CHECKER
    if(id == PERSONTAGCODE){
        det_person.detected = true;
        det_person.size = size_tag;
    }else{
        det_person.detected = false;
        det_person.size = 0;
    }

    pub_fireDetect_.publish(det_fire);
    pub_personDetect_.publish(det_person);
}


// ------------------------ Main -----------------------------------------------
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "TagDetector");

    //Begin Camera Object
    CTagDetect CTagDetect();

    //Cameria Port
    static const char image_topic[] = IMAGE_TOPIC;
    //Begin Camera Object
    CCamera camera(image_topic);

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