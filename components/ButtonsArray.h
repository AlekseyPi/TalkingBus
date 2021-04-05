#ifndef ButtonsArray_h
#define ButtonsArray_h

#include "Button.h"

const uint32_t KEYPRESS_ADDITIONAL_TIMEOUT = 2000;

class ButtonsArray
{
    public:
        ButtonsArray(Button* buttons, uint8_t count);
        void initAll();
        void updateAllButtonsState();
        uint16_t waitForInput(uint8_t minKeypressCount, uint8_t maxKeypressCount, uint32_t noInputTimeout);
        Button* getButton(uint8_t index);
        int8_t waitForSingleButton(uint32_t timeoutMillis);
        int8_t waitForSingleButton();
    private:
        uint8_t _count;
        Button* _buttons;
        int8_t getPressedIndex();
        
};

uint32_t powerOf10(int8_t exponent) 
{
  if (exponent > 9) exponent = 9;
  if (exponent == -1) return 0;
  uint32_t result = 1;
  for (int8_t i = 1; i <= exponent; i++)
  {
    result *= 10;
  }
  return result;
}


ButtonsArray::ButtonsArray(Button* buttons, uint8_t count)
{
    _count = count;
    _buttons = buttons;
}

void ButtonsArray::initAll()
{
    for (uint8_t i = 0; i < _count; i++)
    {
        getButton(i)->init();
    }
}

void ButtonsArray::updateAllButtonsState() 
{
  for (int i = 0; i < _count; i++)
  {
    getButton(i)->updateState(); 
  }
}

uint16_t ButtonsArray::waitForInput(uint8_t minKeypressCount, uint8_t maxKeypressCount, uint32_t noInputTimeout)
{
  uint32_t input = 0;
  uint32_t minAcceptableInput = powerOf10(minKeypressCount - 1);
  uint32_t maxAcceptableInput = powerOf10(maxKeypressCount - 1);
  uint32_t timeoutMillis = minKeypressCount > 0 ? UINT32_MAX : millis() + noInputTimeout;

  while (true)
  {
    int8_t pressedIndex = waitForSingleButton(timeoutMillis); 
    if (pressedIndex != -1)
    {
      uint8_t pressedValue = getButton(pressedIndex)->getValue();
      input = input * 10 + pressedValue;
      timeoutMillis = millis() + KEYPRESS_ADDITIONAL_TIMEOUT;
    }
    if (input >= maxAcceptableInput)
        break;
    if (input >= minAcceptableInput && millis() > timeoutMillis)
        break;    
  }
  return input;
}

Button* ButtonsArray::getButton(uint8_t index)
{
    if (index >= 0 && index < _count)
    {
        return (_buttons + index);
    }
}

int8_t ButtonsArray::getPressedIndex()
{
  for (int i = 0; i < _count; i++)
  {
    if (getButton(i)->getPressed() && getButton(i)->getStateChangedMillis() > 25) //  const uint16_t DebounceMillis = 25;
    {
      return i;
    }
  }
  return -1;
}

// returns button index or -1 if timeout
int8_t ButtonsArray::waitForSingleButton(uint32_t timeoutTimeMillis)
{
  while (millis() < timeoutTimeMillis) {
    updateAllButtonsState();
    int8_t pressedIndex = getPressedIndex();
    if (pressedIndex != -1) {
      getButton(pressedIndex)->waitUnpressed();
      return pressedIndex;
    }
    delay(10);
  }
  return -1;
}

int8_t ButtonsArray::waitForSingleButton()
{
    return waitForSingleButton(UINT32_MAX);
}


#endif