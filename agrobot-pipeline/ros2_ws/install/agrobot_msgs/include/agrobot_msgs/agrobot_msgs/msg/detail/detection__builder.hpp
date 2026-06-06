// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agrobot_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
#define AGROBOT_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agrobot_msgs/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agrobot_msgs
{

namespace msg
{

namespace builder
{

class Init_Detection_height
{
public:
  explicit Init_Detection_height(::agrobot_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  ::agrobot_msgs::msg::Detection height(::agrobot_msgs::msg::Detection::_height_type arg)
  {
    msg_.height = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agrobot_msgs::msg::Detection msg_;
};

class Init_Detection_width
{
public:
  explicit Init_Detection_width(::agrobot_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_height width(::agrobot_msgs::msg::Detection::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_Detection_height(msg_);
  }

private:
  ::agrobot_msgs::msg::Detection msg_;
};

class Init_Detection_left
{
public:
  explicit Init_Detection_left(::agrobot_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_width left(::agrobot_msgs::msg::Detection::_left_type arg)
  {
    msg_.left = std::move(arg);
    return Init_Detection_width(msg_);
  }

private:
  ::agrobot_msgs::msg::Detection msg_;
};

class Init_Detection_top
{
public:
  Init_Detection_top()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Detection_left top(::agrobot_msgs::msg::Detection::_top_type arg)
  {
    msg_.top = std::move(arg);
    return Init_Detection_left(msg_);
  }

private:
  ::agrobot_msgs::msg::Detection msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agrobot_msgs::msg::Detection>()
{
  return agrobot_msgs::msg::builder::Init_Detection_top();
}

}  // namespace agrobot_msgs

#endif  // AGROBOT_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
