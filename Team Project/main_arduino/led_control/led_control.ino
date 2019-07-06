/*

* Main Arduino

* Version 20190703

* Read sound data every 0.1 sec

* If sound is larger than LOUD_SOUND,

* buzzer_melody, led_blink

*/

#include "pitches.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN  6 // On Trinket or Gemma, suggest changing this to 1
#define LED_COUNT 4 // LED 갯수
#define BRIGHTNESS 255

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#define delayVAL 500 

// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//  NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//  NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//  NEO_GRB    Pixels are wired for GRB bitstream (most NeoPixel products)
//  NEO_RGB    Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//  NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


const int LOUD_SOUND = 650;

const int mySoundSensor = A0;

const int myBuzzer = 9;

const int subArduino = 7;



void setup() {

  pinMode(mySoundSensor, INPUT);

  Serial.begin(9600);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  pixels.setBrightness(BRIGHTNESS);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)


}



void loop() {

  int readSound = analogRead(A0);



  if(readSound > LOUD_SOUND)

  {

    digitalWrite(subArduino,HIGH);

    led_();

    buzzer_melody();

  }

}



void led_()

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
