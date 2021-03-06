################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(my_car)


## Compile as C++17
set(CMAKE_CXX_STANDARD 17)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        sensor_msgs
        geometry_msgs
        nav_msgs
        tf
        gazebo_ros
        message_generation
        )

find_package(gazebo REQUIRED)

################################################################################
# Setup for python modules and scripts
################################################################################

################################################################################
# Declare ROS messages, services and actions
################################################################################
add_message_files(
        FILES
        MotorState.msg
)

generate_messages(
        DEPENDENCIES
        std_msgs
)
################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################

catkin_package(
        INCLUDE_DIRS include
        CATKIN_DEPENDS roscpp std_msgs sensor_msgs geometry_msgs nav_msgs tf gazebo_ros message_runtime
        DEPENDS GAZEBO
)

################################################################################
# Build
################################################################################
link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${GAZEBO_INCLUDE_DIRS}
)

#add_executable(turtlebot3_drive src/turtlebot3_drive.cpp)
#add_dependencies(turtlebot3_drive ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(turtlebot3_drive ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_executable(my_car_drive src/my_car_drive.cpp)
add_dependencies(my_car_drive ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(my_car_drive ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})

add_executable(arduino_drive src/arduino_drive.cpp)
add_dependencies(arduino_drive ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(arduino_drive ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
