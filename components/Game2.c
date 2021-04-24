#include "Button.h"
#include "ButtonsArray.h"

void game2_zoo(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    //player->playFromMP3Folder(100); // TODO: play "Зоопарк"
    buttonsArray->getButton(1)->setLED(true);
    delay(300);
    buttonsArray->getButton(1)->setLED(false);
    int8_t pressedIndex;
    Button* pressedButton = NULL;

    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == -1)
        {
            continue;
        }
        pressedButton = buttonsArray->getButton(pressedIndex);
        pressedButton->setLED(true);
        delay(500);
        pressedButton->setLED(false);

        if (pressedIndex == 4 && buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            return;
        }

        if (pressedIndex == 0)
        {
            // play random from 0 to N 
            // player->playFromMP3Folder();
        }
    }
}