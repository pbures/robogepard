#ifndef _gepardleg_h_
#define _gepardleg_h_

#include "servoconfig.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "junction.h"

#define ANKLE_SHIFT_DEG 0
#define ANKLE_MIN_DEG 0
#define ANKLE_MAX_DEG 160

#define KNEE_SHIFT_DEG -15
#define KNEE_MIN_DEG 25
#define KNEE_MAX_DEG 230

#define SHOULDER_SHIFT_DEG -10
#define SHOULDER_MIN_DEG 0
#define SHOULDER_MAX_DEG 130

  class GepardLeg {
  public:
    GepardLeg(Adafruit_PWMServoDriver *pwm, int ankle_num, int knee_num, int shoulder_num);

    Junction *ankle;
    Junction *knee;
    Junction *shoulder;

    int getAnkle();
    int getKnee();
    int getShoulder();
    
    int setAnkle(int angle);
    int setKnee(int angle);
    int setShoulder(int angle);

    void update();

    void shrug();
    void stretch();
    void kick();
    void step1();
    void step2();
    void step3();
    void step4();

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
