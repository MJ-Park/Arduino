/*
 * Sub Arduino
 * Version 20190703
 * If mainArduino pin is HIGH,
 * start motor control
 */


// BLUETOOTH defines
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // 블루투스의 Tx, Rx핀을 2,3번핀으로 설정

// MOTOR defines
#include <Stepper.h>
const int STEPS = 2048;
Stepper myStepper(STEPS, 11, 9, 10, 8);

void setup() {
  myStepper.setSpeed(4);
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(mySerial.available()) {
    Serial.write(mySerial.read());
    myStepper.step((STEPS/2));
    delay(50);
    myStepper.step(-(STEPS/2));
    delay(50);
    myStepper.step((STEPS/2)-100);
    delay(50);
    myStepper.step(-(STEPS/2)+100);
    delay(50);
//    myStepper.step((STEPS/4));
//    delay(50);
//    myStepper.step(-(STEPS/4));
//    delay(50);
  }
} 

