#include "Button.h"
#include "ButtonsArray.h"

void game1_songs(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    player->playFolder(10, 001); // "площадь Исполнителей"
    buttonsArray->getButton(0)->setLED(true);
    delay(300);
    buttonsArray->getButton(0)->setLED(false);
    // play random song

    int8_t pressedIndex;
    Button* pressedButton = NULL;
    Button* previouslyPressedButton = NULL;
    int8_t buttonSongIndex = -1;
    int16_t currentFileNumber = -1; // 1..
    
    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == -1)
        {
            if (currentFileNumber != -1 && !player->isPlaying())
            {
                player->playFolder(11, currentFileNumber);
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
        player->playFolder(11, currentFileNumber);
    }
}