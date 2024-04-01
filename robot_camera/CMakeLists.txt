cmake_minimum_required(VERSION 3.5)
project(robot_camera)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(GTest REQUIRED)  # Add this line

# add executable
add_executable(camera_node src/image_publisher.cpp)

ament_target_dependencies(camera_node
  rclcpp
  OpenCV
  image_transport
  cv_bridge
  sensor_msgs
)

# add test executable
add_executable(test_camera_node test/test_camera_node.cpp)

# link test libraries
target_link_libraries(test_camera_node ${GTEST_LIBRARIES} pthread)

# add include directories for test executable
target_include_directories(test_camera_node PRIVATE
  ${rclcpp_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${image_transport_INCLUDE_DIRS}
  ${cv_bridge_INCLUDE_DIRS}
  ${sensor_msgs_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# enable testing and add test
enable_testing()
add_test(NAME test_camera_node COMMAND test_camera_node)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  camera_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()