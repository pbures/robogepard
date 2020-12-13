#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "gepardleg.h"
#include "servoconfig.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GepardLeg frontLeft(&pwm, 0,1,2);
GepardLeg frontRight(&pwm, 3,4,5);

#define DELTA 5

void setServos(uint16_t pulselen){
  for(uint8_t s=0; s<5; s++){
    pwm.setPWM(s, 0, pulselen);
  }
}

int waitForEnter() {
  while(Serial.available() <= 0) {};
  int incByte = Serial.read();
  return incByte;
}

int ankleAng = ANKLE_MAX_DEG;
int kneeAng = KNEE_MIN_DEG;
int shoulderAng = 25;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  frontLeft.ankle(ankleAng);
  frontLeft.knee(kneeAng);
  frontLeft.shoulder(shoulderAng);
}

void loop() {

  Serial.print("Status: A:");
  Serial.print(ankleAng);
  Serial.print(" K:");
  Serial.print(kneeAng);
  Serial.print(" S:");
  Serial.print(shoulderAng);

  int incomingByte = waitForEnter();
  Serial.print(" B: ");
  Serial.println(incomingByte);
  
  switch(incomingByte) {
    case 122: //'z'
      ankleAng += DELTA;
      ankleAng = frontLeft.ankle(ankleAng);
      break;
      
    case 120: //'x'
      ankleAng -= DELTA;
      ankleAng = frontLeft.ankle(ankleAng);
      break;

    case 115: //'s'
      kneeAng += DELTA;
      kneeAng = frontLeft.knee(kneeAng);
      break;

    case 97: //'a'
      kneeAng -= DELTA;
      kneeAng = frontLeft.knee(kneeAng);
      break;

    case 119: //'w'
      shoulderAng += DELTA;
      shoulderAng = frontLeft.shoulder(shoulderAng);
      break;     

    case 113: //'q'
      shoulderAng -= DELTA;
      shoulderAng = frontLeft.shoulder(shoulderAng);
      break;     


    case 99: //'c'
      frontLeft.shrug();
      break;

    case 100: //'d'
      frontLeft.stretch();
      break;
  }

}
