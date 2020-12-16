#include "gepardleg.h"

#include <Arduino.h>
#include <string.h>

GepardLeg::GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num) {
  _ankle_num = ankle_num;
  _knee_num = knee_num;
  _shoulder_num = shoulder_num;
  _pwm = pwm;
}

int GepardLeg::getShoulder() { return _shoulder; };
int GepardLeg::getKnee() { return _knee; };
int GepardLeg::getAnkle() { return _ankle; };

int GepardLeg::setShoulder(int angle) {

  angle = (angle < SHOULDER_MIN_DEG ) ? SHOULDER_MIN_DEG : angle;
  angle = (angle > SHOULDER_MAX_DEG ) ? SHOULDER_MAX_DEG : angle;
  
  _shoulder = angle;
  _pwm->setPWM(_shoulder_num, 0, angle2pw(angle + SHOULDER_SHIFT_DEG));

  setKnee(_knee);
  return _shoulder;
};

int GepardLeg::setKnee(int angle) {
  
  _knee = angle;
  
  long int k = 180 - _knee + _shoulder; 
  long int delta = 0;
  
  if (k < KNEE_MIN_DEG) {
    delta = KNEE_MIN_DEG - k;  
  }

  if (k > KNEE_MAX_DEG) {
    delta = KNEE_MAX_DEG - k;  
  }
  
  k = k + delta;
  _knee = _knee - delta;
  
  Serial.print("  Knee to: ");
  Serial.print(angle);
  Serial.print(",abs: ");
  Serial.print(k);
  Serial.print(" delta: ");
  Serial.println(delta);
  
  _pwm->setPWM(_knee_num, 0, angle2pw(k + KNEE_SHIFT_DEG));
  setAnkle(_ankle);

  return _knee;
};

int GepardLeg::setAnkle(int angle) {

  _ankle = angle;
  long int a = 90 + _knee - _ankle + ANKLE_SHIFT_DEG;
  
  a = (a < ANKLE_MIN_DEG ) ? ANKLE_MIN_DEG : a;
  a = (a > ANKLE_MAX_DEG ) ? ANKLE_MAX_DEG : a;

  Serial.print("    Ankle to: ");
  Serial.print(angle);
  Serial.print(",abs: ");
  Serial.println(a);

  _pwm->setPWM(_ankle_num, 0, angle2pw(a + ANKLE_SHIFT_DEG));

  return _ankle;
};


uint16_t GepardLeg::angle2pw(int16_t angle){
  uint32_t pw = 0;

  if (angle < 0) angle = 0;

  pw = (SERVOMAX - SERVOMIN) * angle / 180;  
  pw = pw + SERVOMIN;
  
  return pw;
}

void GepardLeg::shrug(){
  setAnkle(90);
  setKnee(145);
  setShoulder(0);
}

void GepardLeg::stretch(){
  setAnkle(90);
  setKnee(90);
  setShoulder(90);
}

void GepardLeg::kick(){
  setAnkle(120);
  setShoulder(100);
  setKnee(165);
  delay(200);
  setShoulder(10);
  setKnee(0);
  setAnkle(90);
}
