#ifndef Button_h
#define Button_h

#include "Arduino.h"
const uint32_t LONG_PRESS_MILLISECONDS = 1000;

class Button 
{
  public:
    Button(uint8_t value, uint8_t inputPin, uint8_t outputPin);
    void init();
    uint8_t getValue();
    void updateState();
    void waitPressed();
    void waitUnpressed();
    bool getPressed();
    uint32_t getStateChangedMillis();
    uint32_t getPreviousStateMillis();
    bool wasLongPressed();
    void setLED(bool value);
    bool getLED();
  private:
    uint8_t _value;
    uint8_t _inputPin;
    uint8_t _outputPin;
    bool _pressed;
    bool _isLEDOn;
    uint32_t _stateChangedMillis;
    uint32_t _previousStateMillis;
    bool _wasLongPressed;
};

Button::Button(uint8_t value, uint8_t inputPin, uint8_t outputPin)
{
  _value = value;
  _inputPin = inputPin;
  _outputPin = outputPin;
}

void Button::init()
{
  pinMode(_inputPin, INPUT_PULLUP);
  pinMode(_outputPin, OUTPUT);
}

uint8_t Button::getValue()
{
  return _value;
}

void Button::updateState()
{
    bool actualPressed = !digitalRead(_inputPin);
    if (actualPressed != _pressed)
    {
        _previousStateMillis = millis() - _stateChangedMillis;
        _wasLongPressed = !actualPressed && _previousStateMillis > LONG_PRESS_MILLISECONDS;
        _stateChangedMillis = millis();
        _pressed = actualPressed;
    }
}

void Button::waitPressed()
{
  while (!_pressed) 
  {
    delay(10);
    updateState();
  }
}

void Button::waitUnpressed()
{
  while (_pressed) 
  {
    delay(10);
    updateState();
  }
}

bool Button::getPressed()
{
  return _pressed;
}

uint32_t Button::getStateChangedMillis()
{
  return millis() - _stateChangedMillis;
}

uint32_t Button::getPreviousStateMillis()
{
  return _previousStateMillis;
}

bool Button::wasLongPressed()
{
  return _wasLongPressed;
}

void Button::setLED(bool value)
{
    _isLEDOn = value;
    digitalWrite(_outputPin, _isLEDOn);
}

bool Button::getLED()
{
    return _isLEDOn;
}

#endif