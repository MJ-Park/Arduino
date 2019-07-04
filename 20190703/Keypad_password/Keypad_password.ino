#include <Keypad.h>
#include <string.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

int led = 13;
int arr_index = 0;
int MAX_ARR_INDEX = 3;

char PASSWORD[5] = {'2', '4', '8', '7', '\0'};
char input_password[5] = {'0', '0', '0', '0', '\0'};

//const String INIT_PASSWORD[4] = {NULL, NULL, NULL, NULL};
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();

  if (customKey){
      Serial.print(customKey);
       input_password[arr_index] = customKey;
        arr_index++;
//    Serial.println(customKey);
    if(arr_index > MAX_ARR_INDEX) {
      if(!strcmp(PASSWORD, input_password)) {
        Serial.println("");
        Serial.println("LED ON");
        digitalWrite(led,HIGH);
      }
      else {
        digitalWrite(led,LOW);
        Serial.println("");
       Serial.println("WRONG PASSWORD");
       Serial.print("INPUT PASSWORD : ");
       Serial.println(input_password);
       Serial.print("SETTING PASSWORD : ");
       Serial.println(PASSWORD);
      }
      arr_index = 0;

      }
  }
}
