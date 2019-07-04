#include "LedControl.h"

LedControl lc = LedControl(12,11,10,1);
byte one[] =
{B00000000, B00011000, B00100100, B00100100, B00100100, B00100100, B00011000, B00000000};
byte zero[] =
{B00000000, B00010000, B00110000, B00010000, B00010000, B00010000, B00111000, B00000000 };

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,5);
  lc.clearDisplay(0);
}


void loop() {
  display_heart(1);
  delay(500);
  display_heart(0);
  delay(500);
}

void display_heart(int a) {
  if ( a==0 )
  {
    for (int i = 0 ; i < 8 ;  i++) {
      lc.setRow(0,i,one[i]);
    }
  }
  else
  {
    for (int i = 0 ; i < 8 ; i++)
    {
      lc.setRow(0,i,zero[i]);
    }
  }
}
