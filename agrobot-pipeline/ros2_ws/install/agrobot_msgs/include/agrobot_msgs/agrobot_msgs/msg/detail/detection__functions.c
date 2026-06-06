// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agrobot_msgs:msg/Detection.idl
// generated code does not contain a copyright notice
#include "agrobot_msgs/msg/detail/detection__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
agrobot_msgs__msg__Detection__init(agrobot_msgs__msg__Detection * msg)
{
  if (!msg) {
    return false;
  }
  // top
  // left
  // width
  // height
  return true;
}

void
agrobot_msgs__msg__Detection__fini(agrobot_msgs__msg__Detection * msg)
{
  if (!msg) {
    return;
  }
  // top
  // left
  // width
  // height
}

bool
agrobot_msgs__msg__Detection__are_equal(const agrobot_msgs__msg__Detection * lhs, const agrobot_msgs__msg__Detection * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // top
  if (lhs->top != rhs->top) {
    return false;
  }
  // left
  if (lhs->left != rhs->left) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  return true;
}

bool
agrobot_msgs__msg__Detection__copy(
  const agrobot_msgs__msg__Detection * input,
  agrobot_msgs__msg__Detection * output)
{
  if (!input || !output) {
    return false;
  }
  // top
  output->top = input->top;
  // left
  output->left = input->left;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  return true;
}

agrobot_msgs__msg__Detection *
agrobot_msgs__msg__Detection__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__msg__Detection * msg = (agrobot_msgs__msg__Detection *)allocator.allocate(sizeof(agrobot_msgs__msg__Detection), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agrobot_msgs__msg__Detection));
  bool success = agrobot_msgs__msg__Detection__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agrobot_msgs__msg__Detection__destroy(agrobot_msgs__msg__Detection * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agrobot_msgs__msg__Detection__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agrobot_msgs__msg__Detection__Sequence__init(agrobot_msgs__msg__Detection__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__msg__Detection * data = NULL;

  if (size) {
    data = (agrobot_msgs__msg__Detection *)allocator.zero_allocate(size, sizeof(agrobot_msgs__msg__Detection), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agrobot_msgs__msg__Detection__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agrobot_msgs__msg__Detection__fini(&data[i - 1]);
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
agrobot_msgs__msg__Detection__Sequence__fini(agrobot_msgs__msg__Detection__Sequence * array)
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
      agrobot_msgs__msg__Detection__fini(&array->data[i]);
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

agrobot_msgs__msg__Detection__Sequence *
agrobot_msgs__msg__Detection__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agrobot_msgs__msg__Detection__Sequence * array = (agrobot_msgs__msg__Detection__Sequence *)allocator.allocate(sizeof(agrobot_msgs__msg__Detection__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agrobot_msgs__msg__Detection__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agrobot_msgs__msg__Detection__Sequence__destroy(agrobot_msgs__msg__Detection__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agrobot_msgs__msg__Detection__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agrobot_msgs__msg__Detection__Sequence__are_equal(const agrobot_msgs__msg__Detection__Sequence * lhs, const agrobot_msgs__msg__Detection__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agrobot_msgs__msg__Detection__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agrobot_msgs__msg__Detection__Sequence__copy(
  const agrobot_msgs__msg__Detection__Sequence * input,
  agrobot_msgs__msg__Detection__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agrobot_msgs__msg__Detection);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agrobot_msgs__msg__Detection * data =
      (agrobot_msgs__msg__Detection *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agrobot_msgs__msg__Detection__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agrobot_msgs__msg__Detection__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agrobot_msgs__msg__Detection__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
