#include "Button.h"
#include "Const.h"
#include "ButtonsArray.h"

void start(ButtonsArray *buttonsArray, DFPlayerMini_Fast *player)
{
  for (int i = 0; i < BUTTONS_COUNT; i++)
  {
    buttonsArray->getButton(i)->setLED(true);
    delay(30);
  }
  for (int i = 0; i < BUTTONS_COUNT; i++)
  {
    buttonsArray->getButton(i)->setLED(false);
    delay(30);
  }

  //player->playFolder(01, 001); // bus start 10 sec
  //delay(300); while (player->isPlaying()) delay(100); // wait until the song is played
}