#include "Button.h"
#include "ButtonsArray.h"

void game2_zoo(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    player->playFolder(01, 002); // "bus stop"
    delay(3500);

    player->playFolder(20, 001); // "Зоопарк"
    delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
    
    int8_t pressedIndex;
    int8_t fileIndex = 1;
    Button* pressedButton = NULL;

    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == -1)
        {
            continue;
        }
        if (pressedIndex == 4 && buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            return;
        }
        pressedButton = buttonsArray->getButton(pressedIndex);
        
        pressedButton->setLED(true);
        
        player->playFolder(21, fileIndex);
        delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
        fileIndex++;
        if (fileIndex > 22) fileIndex = 1;

        pressedButton->setLED(false);
    }
}