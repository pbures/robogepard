#include "gepardleg.h"

#include <Arduino.h>
#include <string.h>

#include "legdegs.h"

/*
 * --------######o######---------------
 *    |shoulder |||
 *     \        |||
 *       \__    |||
 * s. servoangle||| _
 *              |||   \
 * ------------- o     |  k.servo angle
 *      | knee  ||| __/
 *       \      |||
 *        \__   ||| _
 *              |||  \
 * ------------ |||   \ a.servo angle
 *    |   ankle  o    | 
 *     \_ [//////////////]
 *        [//////////////]
 * 
 */

GepardLeg::GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num) {

  shoulder = new Junction(pwm, shoulder_num, 90, SHOULDER_MIN_DEG, SHOULDER_MAX_DEG, SHOULDER_SHIFT_DEG);
  knee = new Junction(pwm, knee_num, 0, KNEE_MIN_DEG, KNEE_MAX_DEG, KNEE_SHIFT_DEG);
  ankle = new Junction(pwm, ankle_num, 90, ANKLE_MIN_DEG, ANKLE_MAX_DEG, ANKLE_SHIFT_DEG);
  
  _ankle_num = ankle_num;
  _knee_num = knee_num;
  _shoulder_num = shoulder_num;
  _pwm = pwm;
}

int GepardLeg::getShoulder() { return this->shoulder->getAngle(); };
int GepardLeg::getKnee() { return 180 - knee->getAngle() + this->getShoulder(); };
int GepardLeg::getAnkle() { return _ankle; };

void GepardLeg::update() {
  knee->update();
  ankle->update();
  shoulder->update();
}

int GepardLeg::setShoulder(int angle) {

  int knee_deg = getKnee();
  
  int a = shoulder->setAngle(angle);
//  shoulder->update();
  setKnee(knee_deg);

  #ifdef DEBUG
  Serial.print("  Shoulder to: ");
  Serial.print(angle);
  
  Serial.print(",abs: ");
  Serial.println(a);
  #endif
  
  return getShoulder();
};

int GepardLeg::setKnee(int angle) {

  int ankle = getAnkle();
  long int k = 180 - angle + getShoulder(); 
  long int k2 = knee->setAngle(k);

  #ifdef DEBUG
  Serial.print("  Knee to: ");
  Serial.print(angle);
  Serial.print(",abs: ");
  Serial.print(k);
  Serial.print(" abs_limited: ");
  Serial.println(k2);
  #endif
 
  setAnkle(ankle);
  return getKnee();
};

int GepardLeg::setAnkle(int angle) {

  _ankle = angle;
  long int a = 90 + getKnee() - angle;
  long int a2 = ankle->setAngle(a);

  #ifdef DEBUG  
  Serial.print("    Ankle to: ");
  Serial.print(angle);
  Serial.print(",abs: ");
  Serial.print(a);
  Serial.print(" abs_limited: ");
  Serial.println(a2);
  #endif
  
  return getAnkle();
};

void GepardLeg::shrug(){
  setAnkle(90);
  setKnee(145);
  setShoulder(0);
  update();
}

void GepardLeg::stretch(){
  setAnkle(90);
  setKnee(90);
  setShoulder(90);
  update();
}

void GepardLeg::kick(){
  setAnkle(245);
  setShoulder(105);
  setKnee(220);
  update();
  delay(200);
  setShoulder(10);
  setKnee(0);
  setAnkle(90);
  update();
}

void GepardLeg::step1(){
  setAnkle(90);
  setKnee(legDegs[0][0]);
  setShoulder(legDegs[0][1]);
  update();
};

void GepardLeg::step2(){
  setAnkle(90);
  for(int j=3; j>=0; j--){
    for(int i=0; i< legDegsLen; i++){
      setKnee(legDegs[i][0]);
      setShoulder(legDegs[i][1]);
      delay(2);
      update();
    }

    delay(500);
    setKnee(180); update();
    delay(500);
    setShoulder(legDegs[0][1]-20); update();
    delay(200);
    setKnee(legDegs[0][0]); update();
    delay(200);
    setShoulder(legDegs[0][1]);
    update();
    delay(500);
  }

};

void GepardLeg::step3(){
  setAnkle(90);
  for(int i=legDegsLen-1; i>=0; i--){
    setKnee(legDegs[i][0]);
    setShoulder(legDegs[i][1]);
    update();
  }
};

void GepardLeg::step4(){
  setAnkle(90);
  setKnee(legDegs[legDegsLen-1][0]);
  setShoulder(legDegs[legDegsLen-1][1]);
  update();
};
