#include "Button.h"
#include "ButtonsArray.h"

void start(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
  // cd /Volumes/BUTTONSSD  
  // rm -R -f .*
  player->playFolder(01, 001); // start sound
  
  for (int i = 0; i < 5; i++)
  {
    buttonsArray->getButton(i)->setLED(true);
    delay(100);
  }
  for (int i = 0; i < 5; i++)
  {
    buttonsArray->getButton(i)->setLED(false);
    delay(100);
  }
}