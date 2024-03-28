#include "rclcpp/rclcpp.hpp"
#include "../include/robot_camera/camera.hpp"

/*
    colcon build --symlink-install
    source install/setup.bash
    ros2 run robot_camera camera_node
*/
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<roborts_camera::CameraNode>();
    RCLCPP_INFO(node->get_logger(), "摄像头启动");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}