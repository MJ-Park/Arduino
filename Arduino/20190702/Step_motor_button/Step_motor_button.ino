#include <Stepper.h>

const int MAX_STEP = 2048;
const int MAX_STATE = 4;
const int MIN_STATE = 1;
const int STEP_
int button = 7;
boolean currentState = LOW;
int motorState = 1;
Stepper myStepper(MAX_STEP, 11, 9, 10, 8);

void setup() {
  pinMode(button,INPUT);
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  int tmp = digitalRead(button);

  if(digitalRead(button) == HIGH)
  {
    currentState = HIGH;
    if(motorState >= MAX_STATE) {
      motorState = MIN_STATE;
    }
    else {
      motorState++;
    }

    switch(motorState)
    {
      case 1:
        myStepper.step(MAX_STEP);
    }

    if(motorState == 1)
    {
      myStepper.step(MAX_STEP);
    }
    else if(motorState == 2)
    {
      myStepper.step(-MAX_STEP);
    }
    else if(motorState == 3)
    {
      myStepper.step(MAX_STEP/4);
    }
    else if(motorState == 4)
    {
      myStepper.step(-(MAX_STEP/8));
    }
    delay(100);
  }
  else if (currentState == HIGH)
  {
    currentState == LOW;
    delay(100);
  }
  else
  {
    delay(100);
  }
  
    Serial.println(digitalRead(button));

}
