#ifndef TF_TRANSFORM_2D_H
#define TF_TRANSFORM_2D_H

#include "rclcpp/rclcpp.hpp"
#include <cmath> // for std::asin

// 四元数からy軸を中心とする回転角度（ピッチ角）を計算する関数
inline double calculatePitchFromQuaternion(double w, double x, double y, double z) {
    double value = 2.0 * (w * x - y * z);
    // valueが[-1, 1]の範囲内に収まるようにクランプする
    value = std::max(-1.0, std::min(1.0, value));
    double pitch = std::asin(value);
    return pitch; // ラジアン単位で返す
}

// TF変換情報を格納する構造体
typedef struct TFTransform2D {
    rclcpp::Time timestamp; // 時刻
    double x;               // x位置
    double y;               // y位置
    double theta;           // z軸回りの回転角度

    // 構造体のコンストラクタ
    TFTransform2D(const rclcpp::Time& ts = rclcpp::Time(0), double x_val = 0.0, double y_val = 0.0, double theta_val = 0.0)
    : timestamp(ts), x(x_val), y(y_val), theta(theta_val) {}
} TFTransform2D;

#endif // TF_TRANSFORM_2D_H
