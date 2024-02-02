#include <iostream>
#include "tag_move_demo/TFSubscriber.h"

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);

    std::cout << "x:" << std::endl;

    // TFSubscriberノードのインスタンスを作成
    auto node = std::make_shared<TFSubscriber>();

    std::cout << "y:" << std::endl;

    // テスト用のTFMessageを作成
    auto message = std::make_shared<tf2_msgs::msg::TFMessage>();
    geometry_msgs::msg::TransformStamped transform_stamped;

    std::cout << "z:" << std::endl;
    
    transform_stamped.header.frame_id = "camera_frame";
    transform_stamped.child_frame_id = "tag_frame";
    transform_stamped.transform.translation.x = 1.0; // 仮の値
    transform_stamped.transform.translation.y = 2.0; // 仮の値
    transform_stamped.transform.rotation.w = 1.0; // 単位四元数（回転なし）
    transform_stamped.transform.rotation.x = 0.0;
    transform_stamped.transform.rotation.y = 0.0;
    transform_stamped.transform.rotation.z = 0.0;

    std::cout << "a:" << std::endl;

    message->transforms.push_back(transform_stamped);

    // tf_callbackを直接呼び出してメッセージを処理
    node->tf_callback(message);

    std::cout << "b:" << std::endl;

    // 現在の変換情報を取得
    auto current_transform = node->getCurrentTransform();

    // 結果を標準出力に表示
    std::cout << "Current Transform:" << std::endl;
    std::cout << "X: " << current_transform.x << std::endl;
    std::cout << "Y: " << current_transform.y << std::endl;
    std::cout << "Theta: " << current_transform.theta << std::endl;

    // ここで期待される値と比較（手動でチェック）
    // 例: 期待されるXが1.0、Yが2.0であることを確認

    rclcpp::shutdown();
    return 0;
}
