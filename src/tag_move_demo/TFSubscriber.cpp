#include "tag_move_demo/TFSubscriber.h"
#include <cmath> // std::asinを使用するために必要

TFSubscriber::TFSubscriber() : Node("tf_subscriber") {
    subscription_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
        "/tf", 10, std::bind(&TFSubscriber::tf_callback, this, std::placeholders::_1));
    
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        std::bind(&TFSubscriber::publish_cmd_vel, this));
}

void TFSubscriber::tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& transform : msg->transforms) {
        if (transform.header.frame_id == "camera_frame" && transform.child_frame_id == "tag_frame") {
            double w = transform.transform.rotation.w;
            double x = transform.transform.rotation.x;
            double y = transform.transform.rotation.y;
            double z = transform.transform.rotation.z;
            double pitch = calculatePitchFromQuaternion(w, x, y, z);
            rclcpp::Time timestamp = rclcpp::Time(transform.header.stamp.sec, transform.header.stamp.nanosec);
            
            current_transform_ = {timestamp, x, y, pitch};
            break;
        }
    }
}

void TFSubscriber::publish_cmd_vel() {
    std::lock_guard<std::mutex> lock(mutex_);
    geometry_msgs::msg::Twist cmd_vel;
    cmd_vel.linear.x = 0.1;
    publisher_->publish(cmd_vel);
}

TFTransform2D TFSubscriber::getCurrentTransform() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return current_transform_;
}
