#ifndef TWIST_PUBLISHER_HPP
#define TWIST_PUBLISHER_HPP

#include <geometry_msgs/msg/twist.hpp>

#include "ipega_driver/ipega.hpp"
#include "rclcpp/rclcpp.hpp"

/******************************************************************************/
class TwistPublisher : public rclcpp::Node {
 public:
  TwistPublisher();

 private:
  void publisherCallback();
  std::vector<std::string> findJsX();

 private:
  rclcpp::TimerBase::SharedPtr timer;
  std::vector<rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr> pubs;
  std::vector<Ipega*> ipegas;
  size_t count;
};
/******************************************************************************/
#endif  // TWIST_PUBLISHER_HPP