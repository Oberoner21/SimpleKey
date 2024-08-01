# SimpleKey
Simple key is a basic library to debounce a key and handle short and long pushes. It can be used for all microcontrollers that use the Arduino framework. (Arduino, ESP266, ESP32...)

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
