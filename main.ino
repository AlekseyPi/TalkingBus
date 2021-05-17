#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFPlayerMini_Fast.h"
#include "components/Button.h"
#include "components/ButtonsArray.h"
#include "components/Start.c"
#include "components/Game1.c"
#include "components/Game2.c"

// sound:
SoftwareSerial _softwareSerial(13, 12); // RX, TX
DFPlayerMini_Fast * _DFPlayer;

// buttons:
const uint8_t INPUT1 = 2; // blue push button 1
const uint8_t OUTPUT1 = 3; // blue led 4
const uint8_t INPUT2 = 4; // white push button 2
const uint8_t OUTPUT2 = 5; // white led 4
const uint8_t INPUT3 = 6; // green push button 3
const uint8_t OUTPUT3 = 7; // green led 4
const uint8_t INPUT4 = 8; // yellow push button 4
const uint8_t OUTPUT4 = 9; // yellow led 4
const uint8_t INPUT5 = 10; // red push button 5
const uint8_t OUTPUT5 = 11; // red led 5

const uint8_t _buttonsCount = 5;
Button * _buttons;
ButtonsArray * _buttonsArray;

void setup()
{
  _softwareSerial.begin(9600);
  _DFPlayer = new DFPlayerMini_Fast();
  _DFPlayer->begin(_softwareSerial);
  _DFPlayer->volume(24);

  _buttons = (Button*) malloc(sizeof(Button) * _buttonsCount);
  _buttons[0] = Button(1, INPUT1, OUTPUT1);
  _buttons[1] = Button(2, INPUT2, OUTPUT2);
  _buttons[2] = Button(3, INPUT3, OUTPUT3);
  _buttons[3] = Button(4, INPUT4, OUTPUT4);
  _buttons[4] = Button(5, INPUT5, OUTPUT5);
  _buttonsArray = new ButtonsArray(_buttons, _buttonsCount);

  _buttonsArray->initAll();

  start(_buttonsArray, _DFPlayer);
}

const uint8_t GAMES_COUNT = 2;
uint8_t gameCode = 0;

void loop()
{
  // DEBUG:
  gameCode = 2;
  // END DEBUG;

  // read gameCode from EEPROM 

  switch (gameCode)
  {
  case 0:
    gameCode = _buttonsArray->waitForInput(1, 2, 0);
    break;
  case 1:
    game1_songs(_buttonsArray, _DFPlayer);
    break;
  case 2:
    game2_zoo(_buttonsArray, _DFPlayer); 
    break;
  default:
    break;
  }
  //gameCode++; 
  //if (gameCode > GAMES_COUNT) gameCode = 1;
  //store gameCode into EEPROM 
}