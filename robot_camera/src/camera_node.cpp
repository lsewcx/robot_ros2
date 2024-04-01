#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImagePublisher : public rclcpp::Node
{
public:
    ImagePublisher() : Node("image_publisher"), cap_(0)
    {
        publisher_ = image_transport::create_publisher(this, "camera/image");
        timer_ = this->create_wall_timer(std::chrono::milliseconds(30), std::bind(&ImagePublisher::publish_image, this));
    }

private:
    void publish_image()
    {
        cv::Mat frame;
        cap_ >> frame;
        if (!frame.empty())
        {
            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
            publisher_.publish(*msg);
        }
    }

    cv::VideoCapture cap_;
    image_transport::Publisher publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisher>());
    rclcpp::shutdown();
    return 0;
}