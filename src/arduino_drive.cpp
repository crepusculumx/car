//
// Created by crepusculumx on 2021/8/31.
//
#include "my_car/arduino_drive.h"


ArduinoDrive::ArduinoDrive() {
    bool ret = init();
    ROS_ASSERT(ret);
}

ArduinoDrive::~ArduinoDrive() {
    ros::shutdown();
}

bool ArduinoDrive::init() {
    cmd_vel_sub = nh.subscribe("/cmd_vel", 50, &ArduinoDrive::cmd_vel_callback, this);
    motor_state_pub = nh.advertise<my_car::MotorState>("/motor_state", 50);
    return true;
}

void ArduinoDrive::cmd_vel_callback(const geometry_msgs::TwistConstPtr &msg) {
    my_car::MotorState motorState = cmd_vel_to_motor_state(msg);
    motor_state_pub.publish(motorState);
}

my_car::MotorState ArduinoDrive::cmd_vel_to_motor_state(const geometry_msgs::TwistConstPtr &msg) {
    my_car::MotorState motorState;
    constexpr double MY_PI = 3.14159;

    constexpr double l = 0.4; // 两轮间距
    constexpr double d = 0.1; // 轮子直径
    constexpr double c = d * MY_PI; // 轮子周长

    constexpr int PPR = 400;//400脉冲每转

    double vl = msg->linear.x - msg->angular.z * l / 2;
    double vr = msg->linear.x + msg->angular.z * l / 2;

    int vl_direction = (vl >= 0);
    int vr_direction = (vr >= 0);
    vl = std::fabs(vl);
    vr = std::fabs(vr);
    motorState.direction.emplace_back(vl_direction);
    motorState.direction.emplace_back(vr_direction);
    motorState.rate.emplace_back(static_cast<int>(vl * PPR / c));
    motorState.rate.emplace_back(static_cast<int>(vr * PPR / c));
    return motorState;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "arduino_drive");
    ArduinoDrive arduinoDrive;
    ros::spin();
    return 0;
}