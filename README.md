# SimpleKey
Simple key is a basic library to debounce a key and handle short and long pushes. It can be used for all microcontrollers that use the Arduino framework. (Arduino, ESP2866, ESP32...)

-----
## Arduino code
### Getting started
Include the SimpleKey library and create a SimpleKey object specifying the pin number to which the key is connected.
```
#include <SimpleKey.h>
const uint8_t KEY_PIN = 41;
SimpleKey key = SimpleKey(KEY_PIN);
```
By default, the key is LOW activ and its connection pin on the microcontroller is set to INPUT_PULLUP mode. You can change this by specifying the third constructor parameter as followed.
The second parameter is then the debounce delay time in mS (by default 50mS).
```
SimpleKey key = SimpleKey(KEY_PIN, 50, LOW);
```
### Getting Key Push
To tell whether or not the button has been pressed simply call push();.
```
void loop()
{
    if(key.push() == 1)
    {
        Serial.print("Key pressed: "); Serial.println(key.getKeyPin());
    }
}
```
### Getting Key Long Push
In most cases you will detect a short push and a long push in the same function. To do this, call getPushType(longPressTime). The parameter longPressTime defines the time period
after which pressing the button is considered a long push. If the button is released earlier, a short press is returned. Unlike the push() function, however, it is the time at which the button is released.
```
unsigned int longPressTime = 500;  // in mS

void loop()
{
    switch(key.getPushType(longPressTime)
    {
        case 1:
            Serial.print("Key short pressed: "); Serial.println(key.getKeyPin());
            break;
        case 2:
            Serial.print("Key long pressed: "); Serial.println(key.getKeyPin());
            break;
    }
}
```

