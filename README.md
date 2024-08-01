# SimpleKey
Simple key is a basic library to debounce a key and handle short and long pushes. It can be used for all microcontrollers that use the Arduino framework. (Arduino, ESP2866, ESP32...)
The SimpleKey class was adapted and modificatet using the template of the library SimpleRotary from [mprogram](https://github.com/mprograms/SimpleRotary).

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
### Handle Key Fields
To handle multiple keys, create a separate SmartKey object for each key. It is best to first define the pin numbers of the individual keys in an array. A second array stores the pointers to the corresponding SmartKey objects.
```
// Keys pin defenition
const uint8_t KEY_LEFT = 42;
const uint8_t KEY_UP = 40;
const uint8_t KEY_DOWN = 41;
const uint8_t KEY_RIGHT = 39;
const uint8_t KEY_A = 38;
const uint8_t KEY_B = 45;

const uint8_t KEYS_COUNT = 6;   // counter of keys
const uint8_t KEYS_PINS[6] = { KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_A, KEY_B }; // array of key pins
SimpleKey *Keys[KEYS_COUNT] = {0};  // initialize a array of pointer to the SimpleKey objects for any key
```
In the setup() methode you create and save the SmartKey objects for all the keys.
```
void setup(void) 
{
    Serial.begin(115200);

    // Creates Simple Key Object for any key and store the pointer to the objects into Keys array
    for(byte i=0; i<KEYS_COUNT; i++)
    {
      Keys[i] = new SimpleKey(KEYS_PINS[i]);
    }
}
```
Then you loop over the keys pointer array and detect key pushes.
```
void loop() 
{
  // loop over the keys array
  for( auto &key : Keys )
  {
    // if current key pressed?
    if(key->push() == 1)
    {
        Serial.print("Key short pressed: "); Serial.println(key->getKeyPin());
    }
  }
}
```
For more and detailed informations, visit the example section.
