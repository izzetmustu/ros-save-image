cmake_minimum_required(VERSION 3.0.2)
project(ros_save_image)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  message_generation
)

find_package(OpenCV REQUIRED)

add_service_files(
  FILES
  TakeScreenshot.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES take-ss
 CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs message_runtime 
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
add_executable(${PROJECT_NAME}_node src/ros_save_image.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
