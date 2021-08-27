//
// Created by crepusculumx on 2021/8/27.
//

#ifndef MY_CAR_MY_CAR_DRIVE_H
#define MY_CAR_MY_CAR_DRIVE_H

#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <nav_msgs/Odometry.h>


class MyCarDrive {
private:

    ros::NodeHandle nh;

    // ROS Topic Publishers
    ros::Publisher cmd_vel_pub;

    // ROS Topic Subscribers
    ros::Subscriber joy_sub;

    bool init();

    void gamepad_callback(const sensor_msgs::JoyConstPtr &joy);

public:
    MyCarDrive();

    ~MyCarDrive();

    bool control_loop();
};

#endif //MY_CAR_MY_CAR_DRIVE_H
