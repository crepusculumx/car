//
// Created by crepusculumx on 2021/8/31.
//

#ifndef MY_CAR_ARDUINO_DRIVE_H
#define MY_CAR_ARDUINO_DRIVE_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <my_car/MotorState.h>

class ArduinoDrive {
private:
    ros::NodeHandle nh;

    // ROS Topic Publishers
    ros::Publisher motor_state_pub;

    // ROS Topic Subscribers
    ros::Subscriber cmd_vel_sub;

    bool init();

    my_car::MotorState cmd_vel_to_motor_state(const geometry_msgs::TwistConstPtr &msg);

    void cmd_vel_callback(const geometry_msgs::TwistConstPtr &msg);

public:
    ArduinoDrive();

    ~ArduinoDrive();
};

#endif //MY_CAR_ARDUINO_DRIVE_H
