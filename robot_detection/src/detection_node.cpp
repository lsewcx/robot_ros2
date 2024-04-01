#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber() : Node("image_subscriber")
    {
        auto callback = [this](const sensor_msgs::msg::Image::SharedPtr msg) -> void {
            cv::Mat rgb_frame = cv_bridge::toCvShare(msg, "rgb8")->image;
            RCLCPP_INFO(this->get_logger(), "图像已接收");
        };

        subscription_ = this->create_subscription<sensor_msgs::msg::Image>("camera/image", 10, callback);
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}
