/*
  SimpleKey library for Arduino framework
  use with Arduino, ESP32 

  - Key debouncing
  - Short push
  - Long push

  Oberoner21, t.schindel@gmx.de
  Version 1.0, vom 31.07.24
*/

#include <Arduino.h>
#include "SmartDebug.h"
#include "SimpleKey.h"

// Keys pin defenition
const uint8_t KEY_LEFT = 42;
const uint8_t KEY_UP = 40;
const uint8_t KEY_DOWN = 41;
const uint8_t KEY_RIGHT = 39;
const uint8_t KEY_A = 38;
const uint8_t KEY_B = 45;

const uint8_t KEYS_COUNT = 6;   // counter of keys
const uint8_t KEYS_PINS[6] = { KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_A, KEY_B }; // array of key pins
SimpleKey *Keys[KEYS_COUNT] = {0};  // array of pointer to the SimpleKey objects for any key


void setup(void) 
{
    DEBUG_BEGIN(115200);

    // Creates Simple Key Object for any key and store the pointer
    // to the objects into Keys array
    for(byte i=0; i<KEYS_COUNT; i++)
    {
      Keys[i] = new SimpleKey(KEYS_PINS[i]);
    }
}


void loop() 
{
  // loop over the keys array
  for( auto &key : Keys )
  {
    // if current key pressed?
    if(key->push() == 1)
    {
        DEBUG_PRINTLN_VALUE("Pressed short", key->getKeyPin());
    }
  }
}

