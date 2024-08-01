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

// Key pin defenition
const uint8_t KEY_PIN = 42;
unsigned int longPressTime = 650;   // key press time to detect a long push

// SimpleKey object
SimpleKey key = SimpleKey(KEY_PIN);

void setup(void) 
{
    DEBUG_BEGIN(115200);
}

void loop() 
{
    switch(key.getPushType(longPressTime))
    {
        case 1:
            // current key was short pressed and is now releasd
            DEBUG_PRINTLN_VALUE("Pressed short", key.getKeyPin());
            break;
        case 2:
            // current key was pressed for time thats defined in longPressTime
            DEBUG_PRINTLN_VALUE("Pressed long", key.getKeyPin());
            break;
    }
}


