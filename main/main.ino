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

int shoulderAng = 90;
int kneeAng = 90;
int ankleAng = 90;

void setup() {
  Serial.begin(57600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  Serial.println("---------");
  
  frontLeft.setShoulder(shoulderAng);
  frontLeft.setKnee(kneeAng);  
  frontLeft.setAnkle(ankleAng);

  frontLeft.update();
}

void help() {
  Serial.println("----------Help---------");
  Serial.println("h    .. this help");
  Serial.println("q, w .. shoulder decrease, increase angle");
  Serial.println("a, s .. knee decrease, increase angle");
  Serial.println("z, x .. ankle decrease, increase angle");
  Serial.println("c .. shrug the leg");
  Serial.println("d .. stretch the leg");
  Serial.println("v .. kick by the leg");
  Serial.println("1 .. front down position");
  Serial.println("2 .. move from frontdown to backdown position");
  Serial.println("3 .. move from backdown to frontdown position");
  Serial.println("4 .. back down position");
}

void loop() {
//#ifdef _undef_
  Serial.print("Status: A:");
  Serial.print(frontLeft.getAnkle());
  Serial.print(" K:");
  Serial.print(frontLeft.getKnee());
  Serial.print(" S:");
  Serial.print(frontLeft.getShoulder());

  int incomingByte = waitForEnter();
  Serial.print(" B: ");
  Serial.println(incomingByte);
  
  switch(incomingByte) {
    case 104: //'h'
      help();
      break;
      
    case 122: //'z'
      frontLeft.setAnkle(frontLeft.getAnkle()+DELTA);
      break;
      
    case 120: //'x'
      frontLeft.setAnkle(frontLeft.getAnkle()-DELTA);
      break;

    case 115: //'s'
      frontLeft.setKnee(frontLeft.getKnee()+DELTA);
      break;

    case 97: //'a'
      frontLeft.setKnee(frontLeft.getKnee()-DELTA);
      break;

    case 119: //'w'
      frontLeft.setShoulder(frontLeft.getShoulder()+DELTA);
      break;     

    case 113: //'q'
      frontLeft.setShoulder(frontLeft.getShoulder()-DELTA);
      break;     


    case 99: //'c'
      frontLeft.shrug();
      break;

    case 100: //'d'
      frontLeft.stretch();
      break;

    case 118: //'v'
      frontLeft.kick();
      delay(600);
      frontLeft.shrug();
      delay(300);
      frontLeft.stretch();
      break;

    case 49: //'1'
      frontLeft.step1();
      break;

    case 50: //'2'
      frontLeft.step2();
      break;

    case 51: //'3'
      frontLeft.step3();
      break;

    case 52: //'4'
      frontLeft.step4();
      break;
  }
  
  frontLeft.update();
  
//  #endif

}
