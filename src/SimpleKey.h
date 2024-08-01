
#pragma once
#include <Arduino.h>

class SimpleKey
{
    public:
        SimpleKey(const uint8_t keyPin, unsigned int debounceDelay = 50, byte trigger = HIGH);
        byte push();
        byte getPushType(int i);
        uint8_t getKeyPin() { return _keyPin; }
    private:
        uint8_t _keyPin;
        byte _trigger;
        unsigned long _currentTime;
        unsigned long _debounceTime;
        unsigned long _pushTime;
        unsigned int _debounceDelay;
        bool _status = false;
        bool _status_prev = false;
        bool _btnPressed = false;
        void _updateTime();
};
