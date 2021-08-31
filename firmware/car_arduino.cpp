#include <ros.h>
#include <my_car/MotorState.h>

//头文件必须以#include <ros.h>开头

#define MOTOR_SIZE 2

#define RATE_PIN_0 2
#define DIRECTION_PIN_0 3

#define RATE_PIN_1 8
#define DIRECTION_PIN_1 9

typedef struct Motor {
    int rate = 0;
    int direction = 0;

    int rate_pin;
    int direction_pin;

    //Motor(int rate_pin, int direction_pin) : rate_pin(rate_pin), direction_pin(direction_pin) {}
} Motor;

Motor motors[MOTOR_SIZE];

// time
unsigned long last_time;
unsigned long cur_time;

// 累计脉冲
double d_pulse[MOTOR_SIZE];

// ros
ros::NodeHandle nh;

void call_back(const my_car::MotorState &msg) {
    for (size_t i = 0; i < MOTOR_SIZE; i++) {
        motors[i].rate = msg.rate[i];
        motors[i].direction = msg.direction[i];
    }
}

ros::Subscriber <my_car::MotorState> sub("/motor_state", call_back);

void setup() {
    nh.initNode();
    nh.subscribe(sub);

    // motor init
    motors[0].rate_pin = RATE_PIN_0;
    motors[0].direction_pin = DIRECTION_PIN_0;

    motors[1].rate_pin = RATE_PIN_1;
    motors[1].direction_pin = DIRECTION_PIN_1;

    for (size_t i = 0; i < MOTOR_SIZE; i++) {
        pinMode(motors[i].rate_pin, OUTPUT);
        pinMode(motors[i].direction_pin, OUTPUT);
    }
    last_time = millis();
}

void loop() {

    for (size_t i = 0; i < MOTOR_SIZE; i++) {
        if (motors[i].direction == 0) {
            digitalWrite(motors[i].direction_pin, LOW);
        } else {
            digitalWrite(motors[i].direction_pin, HIGH);
        }
        if (motors[i].rate == 0) continue;
        tone(motors[i].rate_pin, motors[i].rate);
        delay(1);
        noTone(motors[i].rate_pin);
    }
    nh.spinOnce();
}