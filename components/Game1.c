#include "Button.h"
#include "ButtonsArray.h"

void game1(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    buttonsArray->getButton(0)->setLED(true);
    delay(300);
    buttonsArray->getButton(0)->setLED(false);

    int8_t pressedIndex;
    int8_t buttonSongIndex = -1;
    int16_t currentFileNumber = -1; 
    Button* pressedButton = NULL;
    Button* previouslyPressedButton = NULL;
    
    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == -1)
        {
            if (currentFileNumber != -1 && !player->isPlaying())
            {
                player->playFromMP3Folder(currentFileNumber);
                delay(500);
            }
            continue;
        }
        if (buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            player->stop();
            currentFileNumber = -1;
            continue;
        }

        if (++buttonSongIndex > 4) buttonSongIndex = 0;

        previouslyPressedButton = pressedButton;
        pressedButton = buttonsArray->getButton(pressedIndex);
        if (previouslyPressedButton != NULL)
        {
            previouslyPressedButton->setLED(false);
            if (previouslyPressedButton != pressedButton) 
            {
                buttonSongIndex = 0;
            }
        }
        pressedButton->setLED(true);
        currentFileNumber = pressedIndex * 5 + buttonSongIndex + 1;
        player->playFromMP3Folder(currentFileNumber);
    }
}