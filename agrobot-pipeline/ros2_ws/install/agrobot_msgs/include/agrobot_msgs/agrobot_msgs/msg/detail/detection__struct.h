// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agrobot_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
#define AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Detection in the package agrobot_msgs.
typedef struct agrobot_msgs__msg__Detection
{
  float top;
  float left;
  float width;
  float height;
} agrobot_msgs__msg__Detection;

// Struct for a sequence of agrobot_msgs__msg__Detection.
typedef struct agrobot_msgs__msg__Detection__Sequence
{
  agrobot_msgs__msg__Detection * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agrobot_msgs__msg__Detection__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGROBOT_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
