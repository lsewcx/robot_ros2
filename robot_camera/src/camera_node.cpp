#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
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
            cv::Mat rgb_frame;
            cv::cvtColor(frame, rgb_frame, cv::COLOR_BGR2RGB); // 将BGR图像转换为RGB图像
            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "rgb8", rgb_frame).toImageMsg();
            publisher_.publish(*msg);
            RCLCPP_INFO(this->get_logger(), "图像已发布");
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "没有摄像头");
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