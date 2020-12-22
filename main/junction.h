#ifndef _junction_h_
#define _junction_h_

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "servoconfig.h"

class Junction {
  public:

  Junction(Adafruit_PWMServoDriver *pwm, int board_num, int initial_angle, int min_deg, int max_deg, int shift_deg);
  int setAngle(int angle);
  int getAngle();

  int update();
  
  private:
  uint16_t angle2pw(int16_t angle);

  int _angle;
  int _board_num;
  Adafruit_PWMServoDriver *_pwm;
  
  int _min_deg;
  int _max_deg;
  int _shift_deg;
  
};

#endif
