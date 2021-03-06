#include "Const.h"
#include "Button.h"
#include "ButtonsArray.h"
#include <EEPROM.h>

const uint8_t GAME1_STORAGE = 1;

void game1_songs(ButtonsArray *buttonsArray, DFPlayerMini_Fast *player)
{
    player->playFolder(01, 002); // "bus stop"
    delay(700);

    player->playFolder(10, 001); // "площадь Исполнителей"
    delay(300);
    while (player->isPlaying())
        delay(100); // wait until the song is played

    int8_t pressedIndex;
    Button *pressedButton = NULL;
    Button *previouslyPressedButton = NULL;
    uint8_t buttonSongIndex;   // 0..4
    uint8_t playingSongNumber; // 1..25
    uint16_t volumePreset = 0;
    bool isNightMode = false;

    // play one of songs
    playingSongNumber = EEPROM.read(GAME1_STORAGE);
    playingSongNumber = playingSongNumber == 255 ? 1 : playingSongNumber;
    playingSongNumber++;
    if (playingSongNumber > 25)
        playingSongNumber = 1;
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

        if (buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            volumePreset++;
            if (volumePreset % 3 == 1)
            {
                isNightMode = true;
                player->volume(INITIAL_VOLUME - 8);
                for (int i = 0; i < BUTTONS_COUNT; i++)
                {
                    buttonsArray->getButton(i)->setLED(false);
                }
                continue;
            }
            isNightMode = false;
            if (volumePreset % 3 == 2)
                player->volume(INITIAL_VOLUME + 8);
            if (volumePreset % 3 == 0)
                player->volume(INITIAL_VOLUME);
            continue;
        }

        if (++buttonSongIndex > 4)
            buttonSongIndex = 0;

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
        if (!isNightMode)
        {
            pressedButton->setLED(true);
        }
        playingSongNumber = pressedIndex * 5 + buttonSongIndex + 1;
        player->playFolder(11, playingSongNumber);
    }
}