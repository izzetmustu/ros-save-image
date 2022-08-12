#include <ros/ros.h>
#include <ros_save_image/ros_save_image.hpp>

TakeSS::TakeSS(ros::NodeHandle* nh): nh_(nh), it_(*nh_)
{
    nh_->param<std::string>("image_topic", image_topic, "/usb_cam/image_raw");
    counter = 0;
    server_ = nh->advertiseService("/take_ss_service", &TakeSS::ssCallback, this);
    ROS_INFO_STREAM("Image topic: " << image_topic);
}

bool
TakeSS::ssCallback(ros_save_image::TakeScreenshot::Request& req, ros_save_image::TakeScreenshot::Response& res)
{
    boost::shared_ptr<sensor_msgs::Image const> image_;
    ROS_WARN_STREAM("Service called waiting for image topic " << image_topic);
    image_ = ros::topic::waitForMessage<sensor_msgs::Image>(image_topic, *nh_);
    ROS_WARN_STREAM("Image is OK!");
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(image_, sensor_msgs::image_encodings::BGR8);
        if(cv_ptr->image.empty())
        {
            ROS_ERROR_STREAM("Image is empty");
            res.image_number = counter;
            res.success = false;
            return false;
        }
        else
        {
            cv::imwrite(std::to_string(counter)+".jpg", cv_ptr->image);
            res.image_number = counter;
            res.success = true;
            counter++;
            return true;
        }
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        res.image_number = counter;
        res.success = false;
        return false;
    }
}

int
main(int argc, char** argv)
{
    ros::init(argc, argv, "take_ss_node");
    ros::NodeHandle nh("~");
    TakeSS tss(&nh);
    ros::spin();
    return 0;
}