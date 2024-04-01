#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImagePublisher : public rclcpp::Node
{
public:
    ImagePublisher();

private:
    void publish_image();

    cv::VideoCapture cap_;
    image_transport::Publisher publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};