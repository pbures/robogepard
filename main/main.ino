#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  105 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  510 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;

void setServos(uint16_t pulselen){
  for(uint8_t s=0; s<5; s++){
    pwm.setPWM(s, 0, pulselen);
  }
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

  servonum=0;

  setServos(SERVOMIN);
  Serial.println("MIN");
  while(Serial.available() <= 0) {};
  Serial.read();

  setServos((SERVOMIN + SERVOMAX) / 2);
  Serial.println("MID");
  while(Serial.available() <= 0) {};
  Serial.read();  

  setServos(SERVOMAX);
  Serial.println("MAX");
  while(Serial.available() <= 0) {};
  Serial.read();

  setServos((SERVOMIN + SERVOMAX) / 2);
  Serial.println("MID");
  while(Serial.available() <= 0) {};
  Serial.read();  
  

//  for (uint16_t pulselen=SERVOMIN; pulselen < SERVOMAX; pulselen+=1) {
//    setServos(pulselen);
//    //pwm.setPWM(servonum, 0, pulselen);
//    Serial.println(pulselen);
//    delay(10);
////    while(Serial.available() <= 0) {};
////    Serial.read();
//  }
  
//  
//  pwm.setPWM(servonum, 0, SERVOMIN);
//  delay(1000);
//
//  pwm.setPWM(servonum, 0, SERVOMAX);
//  delay(1000);
//
  
//  // Drive each servo one at a time using setPWM()
//  Serial.println(servonum);
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen+=20) {
//    pwm.setPWM(servonum, 0, pulselen);
//  }
//
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum, 0, pulselen);
//  }
//
//  delay(500);

//  // Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
//  // The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior. 
//  for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
//    pwm.writeMicroseconds(servonum, microsec);
//  }
//
//  delay(500);
//  for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
//    pwm.writeMicroseconds(servonum, microsec);
//  }
//
//  delay(500);

  servonum++;
  if (servonum > 7) servonum = 0; // Testing the first 8 servo channels
}
