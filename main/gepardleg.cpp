#include "gepardleg.h"

#include <Arduino.h>
#include <string.h>

GepardLeg::GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num) {
  _ankle_num = ankle_num;
  _knee_num = knee_num;
  _shoulder_num = shoulder_num;
  _pwm = pwm;
}

int GepardLeg::ankle(int angle) {

  angle = (angle < ANKLE_MIN_DEG ) ? ANKLE_MIN_DEG : angle;
  angle = (angle > ANKLE_MAX_DEG ) ? ANKLE_MAX_DEG : angle;
  
  _ankle = angle;
  _pwm->setPWM(_ankle_num, 0, angle2pw(angle));

  return angle;
};

int GepardLeg::knee(int angle) {
  
  angle = (angle < KNEE_MIN_DEG ) ? KNEE_MIN_DEG : angle;
  angle = (angle > KNEE_MAX_DEG ) ? KNEE_MAX_DEG : angle;
  
  _knee = angle;
  _pwm->setPWM(_knee_num, 0, angle2pw(angle));

  return angle;
};

int GepardLeg::shoulder(int angle) {
  
  angle = (angle < SHOULDER_MIN_DEG ) ? SHOULDER_MIN_DEG : angle;
  angle = (angle > SHOULDER_MAX_DEG ) ? SHOULDER_MAX_DEG : angle;
  
  _shoulder = angle;
  _pwm->setPWM(_shoulder_num, 0, angle2pw(angle));

  return angle;
};

uint16_t GepardLeg::angle2pw(uint16_t angle){
  uint32_t pw = 0;

  pw = (SERVOMAX - SERVOMIN) * angle / 180;  
  pw = pw + SERVOMIN;
  
  return pw;
}

void GepardLeg::shrug(){
  bool cont = true;
  
  int a = _ankle;
  int k = _knee;

  while(cont) {
    
    a = ankle(++a);
    k = knee(--k);
    
    if (a >= ANKLE_MAX_DEG && k <= KNEE_MIN_DEG) {
      cont = false;
    }
  }
}

void GepardLeg::stretch(){
  bool cont = true;
  int a = _ankle;
  int k = _knee;

  while(cont) {
    ankle(--a);
    knee(++k);

    if (a <= ANKLE_MIN_DEG && k >= KNEE_MAX_DEG) {
      cont = false;
    }
  }
}
