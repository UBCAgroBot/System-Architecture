// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agrobot_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_HPP_
#define AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agrobot_msgs__msg__Detection __attribute__((deprecated))
#else
# define DEPRECATED__agrobot_msgs__msg__Detection __declspec(deprecated)
#endif

namespace agrobot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Detection_
{
  using Type = Detection_<ContainerAllocator>;

  explicit Detection_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->top = 0.0f;
      this->left = 0.0f;
      this->width = 0.0f;
      this->height = 0.0f;
    }
  }

  explicit Detection_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->top = 0.0f;
      this->left = 0.0f;
      this->width = 0.0f;
      this->height = 0.0f;
    }
  }

  // field types and members
  using _top_type =
    float;
  _top_type top;
  using _left_type =
    float;
  _left_type left;
  using _width_type =
    float;
  _width_type width;
  using _height_type =
    float;
  _height_type height;

  // setters for named parameter idiom
  Type & set__top(
    const float & _arg)
  {
    this->top = _arg;
    return *this;
  }
  Type & set__left(
    const float & _arg)
  {
    this->left = _arg;
    return *this;
  }
  Type & set__width(
    const float & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const float & _arg)
  {
    this->height = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agrobot_msgs::msg::Detection_<ContainerAllocator> *;
  using ConstRawPtr =
    const agrobot_msgs::msg::Detection_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::msg::Detection_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agrobot_msgs::msg::Detection_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agrobot_msgs__msg__Detection
    std::shared_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agrobot_msgs__msg__Detection
    std::shared_ptr<agrobot_msgs::msg::Detection_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Detection_ & other) const
  {
    if (this->top != other.top) {
      return false;
    }
    if (this->left != other.left) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    return true;
  }
  bool operator!=(const Detection_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Detection_

// alias to use template instance with default allocator
using Detection =
  agrobot_msgs::msg::Detection_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agrobot_msgs

#endif  // AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_HPP_
