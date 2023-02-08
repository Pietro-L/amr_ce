cmake_minimum_required(VERSION 3.8)
project(knapp_amr)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

rosidl_generate_interfaces(${PROJECT_NAME}
"msg/Order.msg"
)
add_executable(optimizer src/OrderOptimizer.cpp)
add_executable(posePub src/posePub.cpp)
add_executable(orderPub src/orderPub.cpp)



ament_target_dependencies(optimizer rclcpp geometry_msgs visualization_msgs)
ament_target_dependencies(posePub rclcpp geometry_msgs)
ament_target_dependencies(orderPub rclcpp geometry_msgs)

target_include_directories(optimizer PUBLIC "${YAML_CPP_INCLUDEDIR}" include)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(optimizer "${cpp_typesupport_target}" ${YAML_CPP_LIBRARIES}) 
target_link_libraries(orderPub "${cpp_typesupport_target}") 

install(TARGETS 
optimizer
posePub
orderPub
DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
