// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_HPP_
#define AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agrobot_msgs__srv__NavPosition_Request __attribute__((deprecated))
#else
# define DEPRECATED__agrobot_msgs__srv__NavPosition_Request __declspec(deprecated)
#endif

namespace agrobot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct NavPosition_Request_
{
  using Type = NavPosition_Request_<ContainerAllocator>;

  explicit NavPosition_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit NavPosition_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agrobot_msgs__srv__NavPosition_Request
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agrobot_msgs__srv__NavPosition_Request
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NavPosition_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const NavPosition_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NavPosition_Request_

// alias to use template instance with default allocator
using NavPosition_Request =
  agrobot_msgs::srv::NavPosition_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agrobot_msgs


#ifndef _WIN32
# define DEPRECATED__agrobot_msgs__srv__NavPosition_Response __attribute__((deprecated))
#else
# define DEPRECATED__agrobot_msgs__srv__NavPosition_Response __declspec(deprecated)
#endif

namespace agrobot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct NavPosition_Response_
{
  using Type = NavPosition_Response_<ContainerAllocator>;

  explicit NavPosition_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->row = 0l;
      this->distance = 0.0f;
      this->success = false;
      this->message = "";
    }
  }

  explicit NavPosition_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->row = 0l;
      this->distance = 0.0f;
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _row_type =
    int32_t;
  _row_type row;
  using _distance_type =
    float;
  _distance_type distance;
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__row(
    const int32_t & _arg)
  {
    this->row = _arg;
    return *this;
  }
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agrobot_msgs__srv__NavPosition_Response
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agrobot_msgs__srv__NavPosition_Response
    std::shared_ptr<agrobot_msgs::srv::NavPosition_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NavPosition_Response_ & other) const
  {
    if (this->row != other.row) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const NavPosition_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NavPosition_Response_

// alias to use template instance with default allocator
using NavPosition_Response =
  agrobot_msgs::srv::NavPosition_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agrobot_msgs

namespace agrobot_msgs
{

namespace srv
{

struct NavPosition
{
  using Request = agrobot_msgs::srv::NavPosition_Request;
  using Response = agrobot_msgs::srv::NavPosition_Response;
};

}  // namespace srv

}  // namespace agrobot_msgs

#endif  // AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_HPP_
