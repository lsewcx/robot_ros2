#include <gtest/gtest.h>
#include<iostream>
#include <../include/image_publisher.hpp>

TEST(ImagePublisherTest, PublishImageWithFrame)
{
    std::cout<<"测试";
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}