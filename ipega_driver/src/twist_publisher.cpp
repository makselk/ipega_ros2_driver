#include "ipega_driver/twist_publisher.hpp"

#include <filesystem>

/******************************************************************************/
TwistPublisher::TwistPublisher() : rclcpp::Node("twist_publisher"), count(0) {
  std::vector<std::string> jsX = findJsX();
  if (jsX.size() == 0) {
    std::cerr << "No input jsX fount" << std::endl;
    exit(1);
  }

  for (size_t i = 0; i != jsX.size(); ++i) {
    try {
      ipegas.emplace_back(new Ipega(jsX[i]));
    } catch (std::exception& ex) {
      std::cerr << ex.what() << std::endl;
      exit(1);
    }

    std::string topic_name = "twist_" + std::to_string(i);
    pubs.emplace_back(
        this->create_publisher<geometry_msgs::msg::Twist>(topic_name, 5));
  }

  timer = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&TwistPublisher::publisherCallback, this));
}
/******************************************************************************/
void TwistPublisher::publisherCallback() {
  for (size_t i = 0; i != ipegas.size(); ++i) {
    auto l_stick = ipegas[i]->getLeftStick();
    auto r_stick = ipegas[i]->getRightStick();

    geometry_msgs::msg::Twist twist;
    twist.linear.x = (double)std::get<0>(r_stick) / 127.0;
    twist.linear.y = (double)std::get<1>(r_stick) / 127.0;
    twist.angular.z = (double)std::get<1>(l_stick) / 127.0;

    pubs[i]->publish(twist);
  }
}
/******************************************************************************/
std::vector<std::string> TwistPublisher::findJsX() {
  std::vector<std::string> paths;
  for (const auto& entry : std::filesystem::directory_iterator("/dev/input/")) {
    if (entry.is_regular_file() &&
        entry.path().filename().string().find("js") == 0) {
      paths.push_back(entry.path().string());
    }
  }
  return paths;
}
/******************************************************************************/
