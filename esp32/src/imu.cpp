#include "imu.h"
//#include "common.h"

void IMU::init()
{
    unsigned long timeout = 5000;
    unsigned long preMillis = millis();
    mpuint();
    action_info.active = UNKNOWN;
}

void IMU::mpuint()
{
    Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {//Adafruit_I2CDevice.cpp 30行 sda scl
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}
Imu_Action *IMU::update(int interval)
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // imu.getMotion6(&(action_info.ax), &(action_info.ay), &(action_info.az),
    //                &(action_info.gx), &(action_info.gy), &(action_info.gz));
       mpu.getEvent(&a, &g, &temp);
       action_info.ax=a.acceleration.x;   
       action_info.ay=a.acceleration.y;  
       action_info.az=a.acceleration.z;   
       action_info.gx=g.gyro.x;
       action_info.gy=g.gyro.y;
       action_info.gz=g.gyro.z;
    if (millis() - last_update_time > interval)
    {
        if (action_info.ay > 4 && !action_info.isValid)
        {
          //  encoder_diff--;
            action_info.isValid = 1;
            action_info.active = TURN_LEFT;
        }
        else if (action_info.ay < -4)
        {
           // encoder_diff++;
            action_info.isValid = 1;
            action_info.active = TURN_RIGHT;
        }
        else
        {
            action_info.isValid = 0;
        }

        if (action_info.ax > 5 && !action_info.isValid)
        {
            delay(300);
            // imu.getMotion6(&(action_info.ax), &(action_info.ay), &(action_info.az),
            //                &(action_info.gx), &(action_info.gy), &(action_info.gz));
            mpu.getEvent(&a, &g, &temp);
            action_info.ax=a.acceleration.x;   
            action_info.ay=a.acceleration.y;  
            action_info.az=a.acceleration.z;   
            action_info.gx=g.gyro.x;
            action_info.gy=g.gyro.y;
            action_info.gz=g.gyro.z;
            if (action_info.ax > 5)
            {
                action_info.isValid = 1;
                action_info.active = GO_FORWORD;
                //encoder_state = LV_INDEV_STATE_PR;
            }
        }
        else if (action_info.ax < -5 && !action_info.isValid)
        {
            mpu.getEvent(&a, &g, &temp);
            action_info.ax=a.acceleration.x;   
            action_info.ay=a.acceleration.y;  
            action_info.az=a.acceleration.z;   
            action_info.gx=g.gyro.x;
            action_info.gy=g.gyro.y;
            action_info.gz=g.gyro.z;
            delay(300);
            // imu.getMotion6(&(action_info.ax), &(action_info.ay), &(action_info.az),
            //                &(action_info.gx), &(action_info.gy), &(action_info.gz));
            if (action_info.ax < -5)
            {
                action_info.isValid = 1;
                action_info.active = RETURN;
                //encoder_state = LV_INDEV_STATE_REL;
            }
        }
        else if(action_info.az>5 &&!action_info.isValid)
        {
            mpu.getEvent(&a, &g, &temp);
            action_info.ax=a.acceleration.x;   
            action_info.ay=a.acceleration.y;  
            action_info.az=a.acceleration.z;   
            action_info.gx=g.gyro.x;
            action_info.gy=g.gyro.y;
            action_info.gz=g.gyro.z;
          action_info.active=UNKNOWN;
          action_info.isValid = 1;
        }
        else
        {
            action_info.isValid = 0;
        }
        last_update_time = millis();
         
    Serial.printf("%d %d %d %d \n",action_info.ax,action_info.ay,action_info.az,action_info.active);
    return &action_info;
    
    }
}
