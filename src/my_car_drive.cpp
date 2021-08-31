//
// Created by crepusculumx on 2021/8/27.
//
#include "my_car/my_car_drive.h"


MyCarDrive::MyCarDrive() {
    bool ret = init();
    ROS_ASSERT(ret);
}

MyCarDrive::~MyCarDrive() {
    ros::shutdown();
}

bool MyCarDrive::init() {
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
    joy_sub = nh.subscribe("/joy", 50, &MyCarDrive::gamepad_callback, this);
    return true;
}

bool MyCarDrive::control_loop() {
    return true;
}

void MyCarDrive::gamepad_callback(const sensor_msgs::JoyConstPtr &joy) {
    geometry_msgs::Twist vel;
    vel.linear.x = joy->axes[1];
    vel.angular.z = joy->axes[0];
    cmd_vel_pub.publish(vel);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "my_car_drive");
    MyCarDrive my_car_drive;
    ros::spin();
    return 0;
}