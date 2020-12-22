#include "junction.h"

Junction::Junction(Adafruit_PWMServoDriver *pwm, int board_num, int initial_angle, int min_deg, int max_deg, int shift_deg){
  _board_num = board_num;
  _min_deg = min_deg;
  _max_deg = max_deg;
  _shift_deg = shift_deg;
  _pwm = pwm;
  _angle = initial_angle;
}

int Junction::getAngle() {
  return _angle;
}

int Junction::setAngle(int angle) {
  angle = (angle < _min_deg) ? _min_deg : angle;
  angle = (angle > _max_deg) ? _max_deg : angle;
  
  _angle = angle;
  return angle;
}

int Junction::update() {
  _pwm->setPWM(_board_num, 0, angle2pw(_angle + _shift_deg));
  return _angle;
}

uint16_t Junction::angle2pw(int16_t angle){
  uint32_t pw = 0;

  if (angle < 0) angle = 0;

  pw = (SERVOMAX - SERVOMIN) * angle / 180;  
  pw = pw + SERVOMIN;
  
  return pw;
}
