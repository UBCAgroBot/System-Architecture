// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__BUILDER_HPP_
#define AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agrobot_msgs/srv/detail/nav_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agrobot_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agrobot_msgs::srv::NavPosition_Request>()
{
  return ::agrobot_msgs::srv::NavPosition_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace agrobot_msgs


namespace agrobot_msgs
{

namespace srv
{

namespace builder
{

class Init_NavPosition_Response_message
{
public:
  explicit Init_NavPosition_Response_message(::agrobot_msgs::srv::NavPosition_Response & msg)
  : msg_(msg)
  {}
  ::agrobot_msgs::srv::NavPosition_Response message(::agrobot_msgs::srv::NavPosition_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agrobot_msgs::srv::NavPosition_Response msg_;
};

class Init_NavPosition_Response_success
{
public:
  explicit Init_NavPosition_Response_success(::agrobot_msgs::srv::NavPosition_Response & msg)
  : msg_(msg)
  {}
  Init_NavPosition_Response_message success(::agrobot_msgs::srv::NavPosition_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_NavPosition_Response_message(msg_);
  }

private:
  ::agrobot_msgs::srv::NavPosition_Response msg_;
};

class Init_NavPosition_Response_distance
{
public:
  explicit Init_NavPosition_Response_distance(::agrobot_msgs::srv::NavPosition_Response & msg)
  : msg_(msg)
  {}
  Init_NavPosition_Response_success distance(::agrobot_msgs::srv::NavPosition_Response::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_NavPosition_Response_success(msg_);
  }

private:
  ::agrobot_msgs::srv::NavPosition_Response msg_;
};

class Init_NavPosition_Response_row
{
public:
  Init_NavPosition_Response_row()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavPosition_Response_distance row(::agrobot_msgs::srv::NavPosition_Response::_row_type arg)
  {
    msg_.row = std::move(arg);
    return Init_NavPosition_Response_distance(msg_);
  }

private:
  ::agrobot_msgs::srv::NavPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agrobot_msgs::srv::NavPosition_Response>()
{
  return agrobot_msgs::srv::builder::Init_NavPosition_Response_row();
}

}  // namespace agrobot_msgs

#endif  // AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__BUILDER_HPP_
