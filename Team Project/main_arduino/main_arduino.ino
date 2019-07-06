/*
 * Main Arduino
 * Version 20190703
 * Read sound data every 0.1 sec
 * If sound is larger than LOUD_SOUND,
 * buzzer_melody, led_blink
 */

#include "pitches.h"

// BLUETOOTH defines
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // 블루투스의 Tx, Rx핀을 2,3번핀으로 설정

// SOUND defines
const int LOUD_SOUND = 640;
const int mySoundSensor = A0;
const int myBuzzer = 9;
const int subArduino = 7;

// LED defines
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int LED_PIN  6 // On Trinket or Gemma, suggest changing this to 1
const int LED_COUNT 4 // LED 갯수
const int BRIGHTNESS 255
const int delayVAL 500 
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

///////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(mySoundSensor, INPUT);
//  Serial.begin(9600);
  mySerial.begin(9600);

  // LED setup
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  int readSound = analogRead(A0);
//  Serial.println(readSound);
  
  if(readSound > LOUD_SOUND)
  {
    mySerial.write(readSound);
    
    led_blink();
    buzzer_melody();
  }

  delay(50);
}

void led_blink()
{
  pixels.clear();

  pixels.setPixelColor(1, pixels.Color(150, 0, 0));
  pixels.setPixelColor(2, pixels.Color(150, 0, 0));
  pixels.setPixelColor(3, pixels.Color(150, 150, 0));
  pixels.setPixelColor(4, pixels.Color(150, 150, 150));

  pixels.show();  // Send the updated pixel colors to the hardware.

  delay(delayVAL); // Pause before next pass through loop
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
