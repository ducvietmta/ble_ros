cmake_minimum_required(VERSION 2.8.3)
project(ble_test)
find_package(catkin REQUIRED COMPONENTS
  Eigen3
  actionlib
  roscpp
  message_generation
)
 add_message_files(
   FILES
   BLEBeacon.msg
   BLEData.msg
 )
 generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
   INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS message_runtime
  CATKIN_DEPENDS roscpp
)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  EIGEN3_INCLUDE_DIR
)
add_library(${PROJECT_NAME}
  src/SimpleKalmanFilter.cpp
)
add_executable(${PROJECT_NAME}_node src/main.cpp)
target_link_libraries(
  ${PROJECT_NAME}_node
  ${PROJECT_NAME}
  ${catkin_LIBRARIES})
