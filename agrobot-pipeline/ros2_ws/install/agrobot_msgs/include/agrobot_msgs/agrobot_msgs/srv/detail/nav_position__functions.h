// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice

#ifndef AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__FUNCTIONS_H_
#define AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agrobot_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "agrobot_msgs/srv/detail/nav_position__struct.h"

/// Initialize srv/NavPosition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agrobot_msgs__srv__NavPosition_Request
 * )) before or use
 * agrobot_msgs__srv__NavPosition_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__init(agrobot_msgs__srv__NavPosition_Request * msg);

/// Finalize srv/NavPosition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Request__fini(agrobot_msgs__srv__NavPosition_Request * msg);

/// Create srv/NavPosition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agrobot_msgs__srv__NavPosition_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
agrobot_msgs__srv__NavPosition_Request *
agrobot_msgs__srv__NavPosition_Request__create();

/// Destroy srv/NavPosition message.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Request__destroy(agrobot_msgs__srv__NavPosition_Request * msg);

/// Check for srv/NavPosition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__are_equal(const agrobot_msgs__srv__NavPosition_Request * lhs, const agrobot_msgs__srv__NavPosition_Request * rhs);

/// Copy a srv/NavPosition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__copy(
  const agrobot_msgs__srv__NavPosition_Request * input,
  agrobot_msgs__srv__NavPosition_Request * output);

/// Initialize array of srv/NavPosition messages.
/**
 * It allocates the memory for the number of elements and calls
 * agrobot_msgs__srv__NavPosition_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__Sequence__init(agrobot_msgs__srv__NavPosition_Request__Sequence * array, size_t size);

/// Finalize array of srv/NavPosition messages.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Request__Sequence__fini(agrobot_msgs__srv__NavPosition_Request__Sequence * array);

/// Create array of srv/NavPosition messages.
/**
 * It allocates the memory for the array and calls
 * agrobot_msgs__srv__NavPosition_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
agrobot_msgs__srv__NavPosition_Request__Sequence *
agrobot_msgs__srv__NavPosition_Request__Sequence__create(size_t size);

/// Destroy array of srv/NavPosition messages.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Request__Sequence__destroy(agrobot_msgs__srv__NavPosition_Request__Sequence * array);

/// Check for srv/NavPosition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__Sequence__are_equal(const agrobot_msgs__srv__NavPosition_Request__Sequence * lhs, const agrobot_msgs__srv__NavPosition_Request__Sequence * rhs);

/// Copy an array of srv/NavPosition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Request__Sequence__copy(
  const agrobot_msgs__srv__NavPosition_Request__Sequence * input,
  agrobot_msgs__srv__NavPosition_Request__Sequence * output);

/// Initialize srv/NavPosition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agrobot_msgs__srv__NavPosition_Response
 * )) before or use
 * agrobot_msgs__srv__NavPosition_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__init(agrobot_msgs__srv__NavPosition_Response * msg);

/// Finalize srv/NavPosition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Response__fini(agrobot_msgs__srv__NavPosition_Response * msg);

/// Create srv/NavPosition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agrobot_msgs__srv__NavPosition_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
agrobot_msgs__srv__NavPosition_Response *
agrobot_msgs__srv__NavPosition_Response__create();

/// Destroy srv/NavPosition message.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Response__destroy(agrobot_msgs__srv__NavPosition_Response * msg);

/// Check for srv/NavPosition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__are_equal(const agrobot_msgs__srv__NavPosition_Response * lhs, const agrobot_msgs__srv__NavPosition_Response * rhs);

/// Copy a srv/NavPosition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__copy(
  const agrobot_msgs__srv__NavPosition_Response * input,
  agrobot_msgs__srv__NavPosition_Response * output);

/// Initialize array of srv/NavPosition messages.
/**
 * It allocates the memory for the number of elements and calls
 * agrobot_msgs__srv__NavPosition_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__Sequence__init(agrobot_msgs__srv__NavPosition_Response__Sequence * array, size_t size);

/// Finalize array of srv/NavPosition messages.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Response__Sequence__fini(agrobot_msgs__srv__NavPosition_Response__Sequence * array);

/// Create array of srv/NavPosition messages.
/**
 * It allocates the memory for the array and calls
 * agrobot_msgs__srv__NavPosition_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
agrobot_msgs__srv__NavPosition_Response__Sequence *
agrobot_msgs__srv__NavPosition_Response__Sequence__create(size_t size);

/// Destroy array of srv/NavPosition messages.
/**
 * It calls
 * agrobot_msgs__srv__NavPosition_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
void
agrobot_msgs__srv__NavPosition_Response__Sequence__destroy(agrobot_msgs__srv__NavPosition_Response__Sequence * array);

/// Check for srv/NavPosition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__Sequence__are_equal(const agrobot_msgs__srv__NavPosition_Response__Sequence * lhs, const agrobot_msgs__srv__NavPosition_Response__Sequence * rhs);

/// Copy an array of srv/NavPosition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agrobot_msgs
bool
agrobot_msgs__srv__NavPosition_Response__Sequence__copy(
  const agrobot_msgs__srv__NavPosition_Response__Sequence * input,
  agrobot_msgs__srv__NavPosition_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGROBOT_MSGS__SRV__DETAIL__NAV_POSITION__FUNCTIONS_H_
