#ifndef IMU_H
#define IMU_H

#include <Adafruit_MPU6050.h>
#include <Wire.h>
//#include "lv_port_indev.h"

#define IMU_I2C_SDA 32
#define IMU_I2C_SCL 33

//extern int32_t encoder_diff;
//extern lv_indev_state_t encoder_state;

enum ACTIVE_TYPE
{
    TURN_RIGHT = 0,
    TURN_LEFT,
    RETURN,
    GO_FORWORD,
    UNKNOWN
};

struct Imu_Action
{
    boolean isValid;
    ACTIVE_TYPE active;
    boolean long_time;
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
};

class IMU
{
private:
    Adafruit_MPU6050 mpu;
    int flag;
    long last_update_time;

public:
    Imu_Action action_info;
public:
    void init();
    Imu_Action *update(int interval);
    void mpuint();
};

#endif
