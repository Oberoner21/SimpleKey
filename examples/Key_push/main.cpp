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

// SimpleKey object
SimpleKey key = SimpleKey(KEY_PIN);

void setup(void) 
{
    DEBUG_BEGIN(115200);
}

void loop() 
{
    if(key.push() == 1)
    {
        DEBUG_PRINTLN_VALUE("Pressed short", key.getKeyPin());
    }
}


