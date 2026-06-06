// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__TRAITS_HPP_
#define AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agrobot_msgs/srv/detail/nav_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agrobot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const NavPosition_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavPosition_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agrobot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use agrobot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agrobot_msgs::srv::NavPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agrobot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agrobot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const agrobot_msgs::srv::NavPosition_Request & msg)
{
  return agrobot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agrobot_msgs::srv::NavPosition_Request>()
{
  return "agrobot_msgs::srv::NavPosition_Request";
}

template<>
inline const char * name<agrobot_msgs::srv::NavPosition_Request>()
{
  return "agrobot_msgs/srv/NavPosition_Request";
}

template<>
struct has_fixed_size<agrobot_msgs::srv::NavPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<agrobot_msgs::srv::NavPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<agrobot_msgs::srv::NavPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agrobot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const NavPosition_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: row
  {
    out << "row: ";
    rosidl_generator_traits::value_to_yaml(msg.row, out);
    out << ", ";
  }

  // member: distance
  {
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: row
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "row: ";
    rosidl_generator_traits::value_to_yaml(msg.row, out);
    out << "\n";
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << "\n";
  }

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavPosition_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agrobot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use agrobot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agrobot_msgs::srv::NavPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agrobot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agrobot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const agrobot_msgs::srv::NavPosition_Response & msg)
{
  return agrobot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agrobot_msgs::srv::NavPosition_Response>()
{
  return "agrobot_msgs::srv::NavPosition_Response";
}

template<>
inline const char * name<agrobot_msgs::srv::NavPosition_Response>()
{
  return "agrobot_msgs/srv/NavPosition_Response";
}

template<>
struct has_fixed_size<agrobot_msgs::srv::NavPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agrobot_msgs::srv::NavPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agrobot_msgs::srv::NavPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agrobot_msgs::srv::NavPosition>()
{
  return "agrobot_msgs::srv::NavPosition";
}

template<>
inline const char * name<agrobot_msgs::srv::NavPosition>()
{
  return "agrobot_msgs/srv/NavPosition";
}

template<>
struct has_fixed_size<agrobot_msgs::srv::NavPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<agrobot_msgs::srv::NavPosition_Request>::value &&
    has_fixed_size<agrobot_msgs::srv::NavPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<agrobot_msgs::srv::NavPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<agrobot_msgs::srv::NavPosition_Request>::value &&
    has_bounded_size<agrobot_msgs::srv::NavPosition_Response>::value
  >
{
};

template<>
struct is_service<agrobot_msgs::srv::NavPosition>
  : std::true_type
{
};

template<>
struct is_service_request<agrobot_msgs::srv::NavPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agrobot_msgs::srv::NavPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__TRAITS_HPP_
