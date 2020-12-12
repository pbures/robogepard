#include "gepardleg.h"

#include <Arduino.h>
#include <string.h>

GepardLeg::GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num) {
  _ankle_num = ankle_num;
  _knee_num = knee_num;
  _shoulder_num = shoulder_num;
  _pwm = pwm;
}

void GepardLeg::ankle(int angle) {
  _ankle = angle;
  _pwm->setPWM(_ankle_num, 0, angle2pw(angle));
};

void GepardLeg::knee(int angle) {
  _ankle = angle;
  _pwm->setPWM(_knee_num, 0, angle2pw(angle));
};

void GepardLeg::shoulder(int angle) {
  _ankle = angle;
  _pwm->setPWM(_shoulder_num, 0, angle2pw(angle));
};

uint16_t GepardLeg::angle2pw(uint16_t angle){
  uint32_t pw = 0;

  Serial.print("Angle: ");
  Serial.println(angle);
  
  pw = (SERVOMAX - SERVOMIN);
  Serial.println(pw);

  pw = pw * angle;
  Serial.println(pw);

  pw = pw / 180;
  Serial.println(pw);
  
  pw = pw + SERVOMIN;
  Serial.println(pw);
  

  Serial.print(" pw: ");
  Serial.println(pw);
  
  return pw;
}
