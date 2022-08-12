#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros_save_image/TakeScreenshot.h>
#include <std_msgs/Empty.h>

class 
TakeSS
{
private:
    ros::NodeHandle* nh_;
    ros::ServiceServer server_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    std::string image_topic;
    int counter;
public:
    TakeSS(ros::NodeHandle* nh);
    bool ssCallback(ros_save_image::TakeScreenshot::Request& req, ros_save_image::TakeScreenshot::Response& res);
};
