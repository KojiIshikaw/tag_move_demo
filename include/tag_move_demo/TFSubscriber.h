#ifndef TF_SUBSCRIBER_H
#define TF_SUBSCRIBER_H

#include "rclcpp/rclcpp.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <mutex>

#include "tag_move_demo/TFTransform2D.h"

class TFSubscriber : public rclcpp::Node {
public:
    TFSubscriber();

    // 現在の変換情報を外部から取得するためのメソッド
    TFTransform2D getCurrentTransform() const;

    void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg);
    
private:
    void publish_cmd_vel();

    rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    TFTransform2D current_transform_;
    mutable std::mutex mutex_;
};

#endif // TF_SUBSCRIBER_H
