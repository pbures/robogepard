#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "gepardleg.h"
#include "servoconfig.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GepardLeg frontLeft(&pwm, 0,1,2);
GepardLeg frontRight(&pwm, 3,4,5);

void setServos(uint16_t pulselen){
  for(uint8_t s=0; s<5; s++){
    pwm.setPWM(s, 0, pulselen);
  }
}

void waitForEnter() {
  while(Serial.available() <= 0) {};
  Serial.read();
}

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {

  frontLeft.ankle(0);
  Serial.println("MIN:--");
  waitForEnter();

  frontLeft.ankle(90);
  Serial.println("MID:--");
  waitForEnter();

  frontLeft.ankle(180);
  Serial.println("MAX:--");
  waitForEnter();

  frontLeft.ankle(90);
  Serial.println("MID2:--");
  waitForEnter();  
}
