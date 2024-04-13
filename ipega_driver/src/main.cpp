#include "ipega_driver/twist_publisher.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto twist_publisher = std::make_shared<TwistPublisher>();
  rclcpp::spin(twist_publisher);
  rclcpp::shutdown();
  return EXIT_SUCCESS;
}