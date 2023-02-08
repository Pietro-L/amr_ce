// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from knapp_amr:msg/Order.idl
// generated code does not contain a copyright notice

#ifndef KNAPP_AMR__MSG__DETAIL__ORDER__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define KNAPP_AMR__MSG__DETAIL__ORDER__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "knapp_amr/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "knapp_amr/msg/detail/order__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace knapp_amr
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_knapp_amr
cdr_serialize(
  const knapp_amr::msg::Order & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_knapp_amr
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  knapp_amr::msg::Order & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_knapp_amr
get_serialized_size(
  const knapp_amr::msg::Order & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_knapp_amr
max_serialized_size_Order(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace knapp_amr

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_knapp_amr
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, knapp_amr, msg, Order)();

#ifdef __cplusplus
}
#endif

#endif  // KNAPP_AMR__MSG__DETAIL__ORDER__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
