#include "Button.h"
#include "ButtonsArray.h"

void start(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
  // cd /Volumes/BUTTONSSD  
  // rm -R -f .*
  // player->playFolder(01, 001); // start sound
  
  for (int i = 0; i < 5; i++)
  {
    buttonsArray->getButton(i)->setLED(true);
    delay(50);
  }
  for (int i = 0; i < 5; i++)
  {
    buttonsArray->getButton(i)->setLED(false);
    delay(50);
  }

  player->playFolder(01, 001); // bus start 10 sec
  delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
}