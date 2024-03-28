#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>

namespace roborts_camera
{
    class CameraNode : public rclcpp::Node
    {
    public:
        CameraNode() : Node("camera_node"), it_(this), is_running_(false)
        {
            pub_ = image_transport::create_publisher(this, "camera/image");
            cap_ = std::make_shared<cv::VideoCapture>(0); // 使用默认摄像头

            if (!cap_->isOpened())
            {
                throw std::runtime_error("无法打开摄像头");
            }

            cap_->set(cv::CAP_PROP_FRAME_WIDTH, 640);  // 设置摄像头宽度
            cap_->set(cv::CAP_PROP_FRAME_HEIGHT, 480); // 设置摄像头高度

            // 检查OpenCL是否可用，如果可用则启用它
            if (cv::ocl::haveOpenCL())
            {
                cv::ocl::setUseOpenCL(true);
            }

            startThread();
        }

        void startThread()
        {
            is_running_ = true;
            thread_ = std::thread(&CameraNode::update, this);
        }

        void stopThread()
        {
            is_running_ = false;
            if (thread_.joinable())
            {
                thread_.join();
            }
        }

        ~CameraNode()
        {
            stopThread();
        }

    private:
        void update()
        {
            cv::Mat frame;
            while (is_running_)
            {
                cap_ >> frame;
                if (!frame.empty())
                {
                    // 将帧转换为ROS图像消息并发布
                    sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
                    pub_.publish(*img_msg);
                }
            }
        }

        bool is_running_;
        cv::VideoCapture cap_;
        std::thread thread_;
        image_transport::Publisher pub_;
        image_transport::ImageTransport it_;
    };

} // namespace roborts_camera

#endif