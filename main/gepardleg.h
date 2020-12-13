#ifndef _gepardleg_h_
#define _gepardleg_h_

#include "servoconfig.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define ANKLE_MIN_DEG 0
#define ANKLE_MAX_DEG 160

#define KNEE_MIN_DEG 30
#define KNEE_MAX_DEG 180

#define SHOULDER_MIN_DEG 0
#define SHOULDER_MAX_DEG 160

  class GepardLeg {
  public:
    GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num);
    int ankle(int angle);
    int knee(int angle);
    int shoulder(int angle);

    void shrug();
    void stretch();
    
    uint16_t angle2pw(uint16_t angle);
    
  private:

    Adafruit_PWMServoDriver *_pwm;
    
    int _ankle;
    int _knee;
    int _shoulder;

    int _ankle_num;
    int _knee_num;
    int _shoulder_num;
    
  };

#endif
