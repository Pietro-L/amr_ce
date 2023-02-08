// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from knapp_amr:msg/Order.idl
// generated code does not contain a copyright notice
#include "knapp_amr/msg/detail/order__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `description`
#include "rosidl_runtime_c/string_functions.h"

bool
knapp_amr__msg__Order__init(knapp_amr__msg__Order * msg)
{
  if (!msg) {
    return false;
  }
  // order_id
  // description
  if (!rosidl_runtime_c__String__init(&msg->description)) {
    knapp_amr__msg__Order__fini(msg);
    return false;
  }
  return true;
}

void
knapp_amr__msg__Order__fini(knapp_amr__msg__Order * msg)
{
  if (!msg) {
    return;
  }
  // order_id
  // description
  rosidl_runtime_c__String__fini(&msg->description);
}

bool
knapp_amr__msg__Order__are_equal(const knapp_amr__msg__Order * lhs, const knapp_amr__msg__Order * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // order_id
  if (lhs->order_id != rhs->order_id) {
    return false;
  }
  // description
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->description), &(rhs->description)))
  {
    return false;
  }
  return true;
}

bool
knapp_amr__msg__Order__copy(
  const knapp_amr__msg__Order * input,
  knapp_amr__msg__Order * output)
{
  if (!input || !output) {
    return false;
  }
  // order_id
  output->order_id = input->order_id;
  // description
  if (!rosidl_runtime_c__String__copy(
      &(input->description), &(output->description)))
  {
    return false;
  }
  return true;
}

knapp_amr__msg__Order *
knapp_amr__msg__Order__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  knapp_amr__msg__Order * msg = (knapp_amr__msg__Order *)allocator.allocate(sizeof(knapp_amr__msg__Order), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(knapp_amr__msg__Order));
  bool success = knapp_amr__msg__Order__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
knapp_amr__msg__Order__destroy(knapp_amr__msg__Order * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    knapp_amr__msg__Order__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
knapp_amr__msg__Order__Sequence__init(knapp_amr__msg__Order__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  knapp_amr__msg__Order * data = NULL;

  if (size) {
    data = (knapp_amr__msg__Order *)allocator.zero_allocate(size, sizeof(knapp_amr__msg__Order), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = knapp_amr__msg__Order__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        knapp_amr__msg__Order__fini(&data[i - 1]);
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
knapp_amr__msg__Order__Sequence__fini(knapp_amr__msg__Order__Sequence * array)
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
      knapp_amr__msg__Order__fini(&array->data[i]);
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

knapp_amr__msg__Order__Sequence *
knapp_amr__msg__Order__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  knapp_amr__msg__Order__Sequence * array = (knapp_amr__msg__Order__Sequence *)allocator.allocate(sizeof(knapp_amr__msg__Order__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = knapp_amr__msg__Order__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
knapp_amr__msg__Order__Sequence__destroy(knapp_amr__msg__Order__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    knapp_amr__msg__Order__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
knapp_amr__msg__Order__Sequence__are_equal(const knapp_amr__msg__Order__Sequence * lhs, const knapp_amr__msg__Order__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!knapp_amr__msg__Order__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
knapp_amr__msg__Order__Sequence__copy(
  const knapp_amr__msg__Order__Sequence * input,
  knapp_amr__msg__Order__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(knapp_amr__msg__Order);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    knapp_amr__msg__Order * data =
      (knapp_amr__msg__Order *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!knapp_amr__msg__Order__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          knapp_amr__msg__Order__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!knapp_amr__msg__Order__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
