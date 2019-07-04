/*
 * Main Arduino
 * Version 20190703
 * Read sound data every 0.1 sec
 * If sound is larger than LOUD_SOUND,
 * buzzer_melody, led_blink
 */

#include "pitches.h"
 
const int LOUD_SOUND = 650;
const int mySoundSensor = A0;
const int myBuzzer = 9;
const int subArduino = 7;

void setup() {
  pinMode(mySoundSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  int readSound = analogRead(A0);
  Serial.println(readSound);
  
  if(readSound > LOUD_SOUND)
  {
    digitalWrite(subArduino,HIGH);
    led_blink();
    buzzer_melody();
  }
}

void led_blink()
{
  
}

void buzzer_melody()
{
    int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };

    int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

    for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(myBuzzer, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(myBuzzer);
  }
}
