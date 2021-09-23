#include "Button.h"
#include "ButtonsArray.h"
#include <EEPROM.h>

const uint8_t GAME1_STORAGE = 1;

void game1_songs(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    player->playFolder(01, 002); // "bus stop"
    delay(3500);
    
    player->playFolder(10, 001); // "площадь Исполнителей"
    delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 

    int8_t pressedIndex;
    Button* pressedButton = NULL;
    Button* previouslyPressedButton = NULL;
    uint8_t buttonSongIndex; // 0..4
    uint8_t playingSongNumber; // 1..25
    
    // play one of songs
    playingSongNumber = EEPROM.read(GAME1_STORAGE);
    playingSongNumber = playingSongNumber == 255 ? 1 : playingSongNumber;
    playingSongNumber++;
    if (playingSongNumber > 25) playingSongNumber = 1; 
    EEPROM.write(GAME1_STORAGE, playingSongNumber);

    pressedIndex = (playingSongNumber - 1) / 5;
    buttonSongIndex = (playingSongNumber - 1) % 5;
    pressedButton = buttonsArray->getButton(pressedIndex);
    buttonsArray->getButton(pressedIndex)->setLED(true);
    uint32_t gameStartTime = millis();
    
    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == 4 && buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            return;
        }
        
        if (pressedIndex == -1)
        {
            if (player->isPlaying())
            {
                continue;
            }

            if (playingSongNumber != 0)
            {
                player->playFolder(11, playingSongNumber);
            }
            continue;
        }

        if (millis() - gameStartTime > 300000) return;

        if (buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            player->stop();
            playingSongNumber = 0;
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
        playingSongNumber = pressedIndex * 5 + buttonSongIndex + 1;
        player->playFolder(11, playingSongNumber);
    }
}