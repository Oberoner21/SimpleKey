
#include "SimpleKey.h"

/**
	CONSTRUCTOR
	Constructs the simple key object
	
	@param keyPin			the pin number of key
	@param debounceDelay	debounce delay in mS, defaul value is 50 mS
	@param trigger			HIGH, if the pressed key set the key pin to LOW,
							LOW, if the pressed key set the key pin to HIGH
							default is HIGH
	
**/
SimpleKey::SimpleKey(const uint8_t keyPin, unsigned int debounceDelay, byte trigger)
{
    _keyPin = keyPin;
	_debounceDelay = debounceDelay;
	_trigger = trigger;
    _currentTime = millis();
    _debounceTime = _currentTime;
	
	if ( _trigger == HIGH ) 
	{
		pinMode(_keyPin, INPUT_PULLUP);
	} else {
		pinMode(_keyPin, INPUT);
	}
}

/**
	GET KEY PUSH
	Gets the status of the key
	
	Returned values
	0x00 = Key not pushed.
	0x01 = Key pushed;

	@return byte, value of key.
**/
byte SimpleKey::push()
{
	_updateTime();
	byte val = 0x00;

	_status = ( digitalRead(_keyPin) == _trigger ? true : false);

	if ( _currentTime >= _debounceTime + _debounceDelay){
		if ( !_status &&  _status_prev ) {
			val = 0x01;
			_pushTime = _currentTime;
		}
		_status_prev = _status;
		_debounceTime = _currentTime;
	}

	return val; 
}

/**
	GET KEY PUSH TYPE
	Checks to see if the key push is a short or long push
	
	Note: Unlike push(), pushType() generates a return value for a short press only on key release. 
	This allows us to track a long press without a false positive of a short press. It is for this reason 
	that you should use this function if you are tying to check for a long or short press in the same function.

	Returned values
	0x00 = Key not pressed.
	0x01 = Key was pressed.
	0x02 = Key was pressed for n milliseconds.
	
	@param i 	the number of milliseconds the key needs to be pressed in order
				to be considered a long press.
	
	@return byte
**/
byte SimpleKey::getPushType(int i)
{
	_updateTime();
	_status = ( digitalRead(_keyPin) == _trigger ) ? true : false;
	byte val = 0x00;

	if ( _currentTime >= _debounceTime + _debounceDelay )
	{
		// Button has been pressed
		if ( !_status && _status_prev ) 
		{
			_btnPressed = true;
			_pushTime = _currentTime;
		}
		
		// Button has been released
		else if ( _status && !_status_prev  && _btnPressed ) 
		{
			_btnPressed = false;
			val = 0x01;
		}

		// Button is being held
		else if ( !_status && !_status_prev && _btnPressed) 
		{
			if ( _currentTime > _pushTime + i ) 
			{
				_btnPressed = false;
				val = 0x02;
			}
		}
		
		_status_prev = _status;
		_debounceTime = _currentTime;
	}

	return val; 
}

/**
	UPDATE THE TIME
	Updates the _currentTime value to the current time in milliseconds.
**/
void SimpleKey::_updateTime()
{
	_currentTime = millis();
}

