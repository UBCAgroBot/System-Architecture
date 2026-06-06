// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agrobot_msgs:srv/NavPosition.idl
// generated code does not contain a copyright notice
#include "agrobot_msgs/srv/detail/nav_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
agrobot_msgs__srv__NavPosition_Request__init(agrobot_msgs__srv__NavPosition_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
agrobot_msgs__srv__NavPosition_Request__fini(agrobot_msgs__srv__NavPosition_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
agrobot_msgs__srv__NavPosition_Request__are_equal(const agrobot_msgs__srv__NavPosition_Request * lhs, const agrobot_msgs__srv__NavPosition_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
agrobot_msgs__srv__NavPosition_Request__copy(
  const agrobot_msgs__srv__NavPosition_Request * input,
  agrobot_msgs__srv__NavPosition_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

agrobot_msgs__srv__NavPosition_Request *
agrobot_msgs__srv__NavPosition_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Request * msg = (agrobot_msgs__srv__NavPosition_Request *)allocator.allocate(sizeof(agrobot_msgs__srv__NavPosition_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agrobot_msgs__srv__NavPosition_Request));
  bool success = agrobot_msgs__srv__NavPosition_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agrobot_msgs__srv__NavPosition_Request__destroy(agrobot_msgs__srv__NavPosition_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agrobot_msgs__srv__NavPosition_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agrobot_msgs__srv__NavPosition_Request__Sequence__init(agrobot_msgs__srv__NavPosition_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Request * data = NULL;

  if (size) {
    data = (agrobot_msgs__srv__NavPosition_Request *)allocator.zero_allocate(size, sizeof(agrobot_msgs__srv__NavPosition_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agrobot_msgs__srv__NavPosition_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agrobot_msgs__srv__NavPosition_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
agrobot_msgs__srv__NavPosition_Request__Sequence__fini(agrobot_msgs__srv__NavPosition_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      agrobot_msgs__srv__NavPosition_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

agrobot_msgs__srv__NavPosition_Request__Sequence *
agrobot_msgs__srv__NavPosition_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Request__Sequence * array = (agrobot_msgs__srv__NavPosition_Request__Sequence *)allocator.allocate(sizeof(agrobot_msgs__srv__NavPosition_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agrobot_msgs__srv__NavPosition_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agrobot_msgs__srv__NavPosition_Request__Sequence__destroy(agrobot_msgs__srv__NavPosition_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agrobot_msgs__srv__NavPosition_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agrobot_msgs__srv__NavPosition_Request__Sequence__are_equal(const agrobot_msgs__srv__NavPosition_Request__Sequence * lhs, const agrobot_msgs__srv__NavPosition_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agrobot_msgs__srv__NavPosition_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agrobot_msgs__srv__NavPosition_Request__Sequence__copy(
  const agrobot_msgs__srv__NavPosition_Request__Sequence * input,
  agrobot_msgs__srv__NavPosition_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agrobot_msgs__srv__NavPosition_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agrobot_msgs__srv__NavPosition_Request * data =
      (agrobot_msgs__srv__NavPosition_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agrobot_msgs__srv__NavPosition_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agrobot_msgs__srv__NavPosition_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agrobot_msgs__srv__NavPosition_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
agrobot_msgs__srv__NavPosition_Response__init(agrobot_msgs__srv__NavPosition_Response * msg)
{
  if (!msg) {
    return false;
  }
  // row
  // distance
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agrobot_msgs__srv__NavPosition_Response__fini(msg);
    return false;
  }
  return true;
}

void
agrobot_msgs__srv__NavPosition_Response__fini(agrobot_msgs__srv__NavPosition_Response * msg)
{
  if (!msg) {
    return;
  }
  // row
  // distance
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agrobot_msgs__srv__NavPosition_Response__are_equal(const agrobot_msgs__srv__NavPosition_Response * lhs, const agrobot_msgs__srv__NavPosition_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // row
  if (lhs->row != rhs->row) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
agrobot_msgs__srv__NavPosition_Response__copy(
  const agrobot_msgs__srv__NavPosition_Response * input,
  agrobot_msgs__srv__NavPosition_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // row
  output->row = input->row;
  // distance
  output->distance = input->distance;
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agrobot_msgs__srv__NavPosition_Response *
agrobot_msgs__srv__NavPosition_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Response * msg = (agrobot_msgs__srv__NavPosition_Response *)allocator.allocate(sizeof(agrobot_msgs__srv__NavPosition_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agrobot_msgs__srv__NavPosition_Response));
  bool success = agrobot_msgs__srv__NavPosition_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agrobot_msgs__srv__NavPosition_Response__destroy(agrobot_msgs__srv__NavPosition_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agrobot_msgs__srv__NavPosition_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agrobot_msgs__srv__NavPosition_Response__Sequence__init(agrobot_msgs__srv__NavPosition_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Response * data = NULL;

  if (size) {
    data = (agrobot_msgs__srv__NavPosition_Response *)allocator.zero_allocate(size, sizeof(agrobot_msgs__srv__NavPosition_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agrobot_msgs__srv__NavPosition_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agrobot_msgs__srv__NavPosition_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
agrobot_msgs__srv__NavPosition_Response__Sequence__fini(agrobot_msgs__srv__NavPosition_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      agrobot_msgs__srv__NavPosition_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

agrobot_msgs__srv__NavPosition_Response__Sequence *
agrobot_msgs__srv__NavPosition_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__srv__NavPosition_Response__Sequence * array = (agrobot_msgs__srv__NavPosition_Response__Sequence *)allocator.allocate(sizeof(agrobot_msgs__srv__NavPosition_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agrobot_msgs__srv__NavPosition_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agrobot_msgs__srv__NavPosition_Response__Sequence__destroy(agrobot_msgs__srv__NavPosition_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agrobot_msgs__srv__NavPosition_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agrobot_msgs__srv__NavPosition_Response__Sequence__are_equal(const agrobot_msgs__srv__NavPosition_Response__Sequence * lhs, const agrobot_msgs__srv__NavPosition_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agrobot_msgs__srv__NavPosition_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agrobot_msgs__srv__NavPosition_Response__Sequence__copy(
  const agrobot_msgs__srv__NavPosition_Response__Sequence * input,
  agrobot_msgs__srv__NavPosition_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agrobot_msgs__srv__NavPosition_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agrobot_msgs__srv__NavPosition_Response * data =
      (agrobot_msgs__srv__NavPosition_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agrobot_msgs__srv__NavPosition_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agrobot_msgs__srv__NavPosition_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agrobot_msgs__srv__NavPosition_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
