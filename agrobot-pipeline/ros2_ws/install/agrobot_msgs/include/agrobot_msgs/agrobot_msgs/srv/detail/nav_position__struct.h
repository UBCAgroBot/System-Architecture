// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_H_
#define AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/NavPosition in the package agrobot_msgs.
typedef struct agrobot_msgs__srv__NavPosition_Request
{
  uint8_t structure_needs_at_least_one_member;
} agrobot_msgs__srv__NavPosition_Request;

// Struct for a sequence of agrobot_msgs__srv__NavPosition_Request.
typedef struct agrobot_msgs__srv__NavPosition_Request__Sequence
{
  agrobot_msgs__srv__NavPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agrobot_msgs__srv__NavPosition_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/NavPosition in the package agrobot_msgs.
typedef struct agrobot_msgs__srv__NavPosition_Response
{
  int32_t row;
  float distance;
  bool success;
  rosidl_runtime_c__String message;
} agrobot_msgs__srv__NavPosition_Response;

// Struct for a sequence of agrobot_msgs__srv__NavPosition_Response.
typedef struct agrobot_msgs__srv__NavPosition_Response__Sequence
{
  agrobot_msgs__srv__NavPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agrobot_msgs__srv__NavPosition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__STRUCT_H_
