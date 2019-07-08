/*
 * Main Arduino
 * Version 20190708
 * Read sound data every 0.1 sec
 * If sound is larger than LOUD_SOUND,
 * buzzer_melody, led_blink
 */

#include "pitches.h"

// BLUETOOTH defines
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,4);

// SOUND defines
const int LOUD_SOUND = 635;
const int mySoundSensor = A0;
const int myBuzzer = 9;
const int subArduino = 7;

// LED defines
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int LED_PIN1 = 11;
const int LED_PIN2 = 5;
const int LED_PIN3 = 6;

const int LED_COUNT1 = 2;
const int LED_COUNT2 = 1;



const int LED_COUNT3 = 1;// LED 갯수
const int BRIGHTNESS = 170;
const int delayVAL = 2000;
Adafruit_NeoPixel pixels1(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(LED_COUNT3, LED_PIN3, NEO_GRB + NEO_KHZ800);

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
  pixels1.setBrightness(BRIGHTNESS);
  pixels2.setBrightness(BRIGHTNESS);
  pixels3.setBrightness(BRIGHTNESS);
  pixels1.begin(); 
  pixels2.begin(); 
  pixels3.begin(); 

}

void loop() {
  int readSound = analogRead(A0);
//  Serial.println(readSound);
  
  if(readSound > LOUD_SOUND)
  {
    mySerial.write(readSound);
    delay(100);
    mySerial.write(readSound);
    delay(100);
    
    led_blink();
    buzzer_melody();
    pixels1.clear();
    pixels2.clear();
    pixels3.clear();
    pixels1.show();
    pixels2.show();
    pixels3.show();
  }

  delay(100);
}

void led_blink()
{
  pixels1.setPixelColor(0, pixels1.Color(255, 255, 255));
  pixels1.setPixelColor(1, pixels1.Color(255, 0, 0));
  pixels2.setPixelColor(0, pixels2.Color(255, 200, 0));
  pixels3.setPixelColor(0, pixels3.Color(255, 178, 217));
  
  pixels2.show();
  pixels3.show();
  pixels1.show();//설정 값 출력
  delay(delayVAL);
  
  

}

void buzzer_melody()
{
int melody[] = {
   NOTE_FS3, NOTE_A3, NOTE_A3, NOTE_A3,NOTE_A3, NOTE_FS3, NOTE_A3,       NOTE_FS3, NOTE_A3, NOTE_A3, NOTE_A3,NOTE_A3, NOTE_B3, NOTE_A3,
   NOTE_D4, NOTE_D4, NOTE_D4, 0, NOTE_D4, NOTE_D4, NOTE_D4,0,    NOTE_D4, NOTE_B3, NOTE_B3, NOTE_B3,NOTE_B3, NOTE_A3, NOTE_B3,
   NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3,NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_D4,      NOTE_D4, NOTE_AS3, NOTE_AS3, NOTE_AS3,0,
   NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_D4, NOTE_FS4,       NOTE_E4, 0,0,
   NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_FS3, NOTE_A3,      NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3,
   NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,   NOTE_D4, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_B3,    
   NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_G4, NOTE_A4,   NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
   NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_D4,      NOTE_D4,0, NOTE_A3, NOTE_FS4, NOTE_A3, NOTE_FS4,
   NOTE_A3, NOTE_FS4, NOTE_FS4, NOTE_E4,               NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4,NOTE_D4, NOTE_D4, NOTE_CS4, 
   NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_E4,NOTE_E4, NOTE_CS4, 0,      NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_E4,NOTE_D4, 
   NOTE_D4, NOTE_CS4, NOTE_B3, 0,   NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_D4,0, NOTE_FS4, NOTE_A3,  
   NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_E4,0,    NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_D4,NOTE_FS4, NOTE_FS4, NOTE_A3,
   NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4,NOTE_E4,    NOTE_E4, NOTE_D4,0,
   NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, 0,
   NOTE_A3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_FS4,   NOTE_FS4, NOTE_FS4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,    
   NOTE_FS4, NOTE_D4, NOTE_D4, NOTE_E4, 0,    NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4,NOTE_D4,0,
   NOTE_A3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, 0,     NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_CS4,
   NOTE_D4, /*0,NOTE_D4, NOTE_E4,
   NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, 0,     NOTE_A3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, 0,0
   NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, 0,     NOTE_A3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_FS4,
   NOTE_FS4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_E4, NOTE_D4, NOTE_CS4, NOTE_D4, 
   NOTE_B3, NOTE_CS4, NOTE_D4, 0, NOTE_CS4, NOTE_D4,   NOTE_A3, NOTE_CS4, NOTE_D4, 0, NOTE_CS4, NOTE_D4, 
   NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_D4,0,NOTE_E4,          ccccccccccccccccccccccccccccccccccccccNOTE_E4*/
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    8,8,8,8,8,8,4,    8,8,8,8,8,8,4, //14
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,4,//15
    8,8,8,8,8,8,8,8,  8,4,8,4,4,  //13
    8,8,8,8,8,8,4,   4,4,2,  //10
    8,8,8,8,8,8,4,  8,8,8,8,8,8,4, //14
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,4, //15
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,4, //15
    8,8,8,8,8,8,4,  4,4,8,8,8,8, // 13
    4,4,4,4,    8,8,8,8,4,8,8, // 11
    8,8,8,8,8,8,4,  8,8,8,8,8,8,8,8, //15
    4,4,4,4,    8,8,8,8,4,8,8,  //11
    8,8,8,8,2,  8,8,8,8,4,8,8, //12
    4,4,4,8,8,  8,2,2, //8
    8,8,8,8,8,8,8,8, //8
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,8,8, //16  
    8,8,4,4,4,   8,8,8,8,8,8,8,8,  //13
    8,8,8,8,8,8,8,8,    8,8,8,8,8,8,4, //15
    2 /*4,4,2, //4
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,8,8,1, //16  
    8,8,8,8,8,8,8,8,  8,8,8,8,8,8,8,8, //16
    8,8,8,8,8,8,4,2, //8
    4,8,8,8,8,4,   4,8,8,8,8,4, //12
    8,8,8,8,8,8,8,8,1 //9*/
  };

    for (int thisNote = 0; thisNote < 219; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(myBuzzer, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);
    noTone(myBuzzer);
  }
}
