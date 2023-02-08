// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from knapp_amr:msg/Order.idl
// generated code does not contain a copyright notice

#ifndef KNAPP_AMR__MSG__DETAIL__ORDER__BUILDER_HPP_
#define KNAPP_AMR__MSG__DETAIL__ORDER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "knapp_amr/msg/detail/order__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace knapp_amr
{

namespace msg
{

namespace builder
{

class Init_Order_description
{
public:
  explicit Init_Order_description(::knapp_amr::msg::Order & msg)
  : msg_(msg)
  {}
  ::knapp_amr::msg::Order description(::knapp_amr::msg::Order::_description_type arg)
  {
    msg_.description = std::move(arg);
    return std::move(msg_);
  }

private:
  ::knapp_amr::msg::Order msg_;
};

class Init_Order_order_id
{
public:
  Init_Order_order_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Order_description order_id(::knapp_amr::msg::Order::_order_id_type arg)
  {
    msg_.order_id = std::move(arg);
    return Init_Order_description(msg_);
  }

private:
  ::knapp_amr::msg::Order msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::knapp_amr::msg::Order>()
{
  return knapp_amr::msg::builder::Init_Order_order_id();
}

}  // namespace knapp_amr

#endif  // KNAPP_AMR__MSG__DETAIL__ORDER__BUILDER_HPP_
