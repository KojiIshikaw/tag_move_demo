#include "rclcpp/rclcpp.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <mutex>
#include <cmath> // std::asinを使用するために必要

#include "tag_move_demo/TFSubscriber.h"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFSubscriber>());
    rclcpp::shutdown();
    return 0;
}
