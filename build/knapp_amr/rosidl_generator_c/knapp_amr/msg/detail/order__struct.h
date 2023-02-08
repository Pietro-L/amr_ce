// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from knapp_amr:msg/Order.idl
// generated code does not contain a copyright notice

#ifndef KNAPP_AMR__MSG__DETAIL__ORDER__STRUCT_H_
#define KNAPP_AMR__MSG__DETAIL__ORDER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'description'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Order in the package knapp_amr.
typedef struct knapp_amr__msg__Order
{
  uint32_t order_id;
  rosidl_runtime_c__String description;
} knapp_amr__msg__Order;

// Struct for a sequence of knapp_amr__msg__Order.
typedef struct knapp_amr__msg__Order__Sequence
{
  knapp_amr__msg__Order * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} knapp_amr__msg__Order__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // KNAPP_AMR__MSG__DETAIL__ORDER__STRUCT_H_
