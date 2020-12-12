#ifndef _gepardleg_h_
#define _gepardleg_h_

#include "servoconfig.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

  class GepardLeg {
  public:
    GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num);
    void ankle(int angle);
    void knee(int angle);
    void shoulder(int angle);
    
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
