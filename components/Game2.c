#include "Button.h"
#include "ButtonsArray.h"

const uint8_t GAME2_STORAGE = 2;

void game2_zoo(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    player->playFolder(01, 002); // "bus stop"
    delay(3500);

    player->playFolder(20, 001); // "Зоопарк"
    delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
    
    int8_t pressedIndex;
    Button* pressedButton = NULL;
    uint32_t gameStartTime = millis();
    uint8_t animalNumber = 1; // 1..22
    
    animalNumber = EEPROM.read(GAME2_STORAGE);
    animalNumber = animalNumber == 255 ? 1 : animalNumber;

    while (true)
    {
        pressedIndex = buttonsArray->waitForSingleButton(millis() + 1000);
        if (pressedIndex == 4 && buttonsArray->getButton(pressedIndex)->wasLongPressed())
        {
            return;
        }
        
        if (pressedIndex == -1)
        {
            continue;
        }
        pressedButton = buttonsArray->getButton(pressedIndex);
        
        pressedButton->setLED(true);
        
        player->playFolder(21, animalNumber);
        delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
        
        animalNumber++;
        if (animalNumber > 22) animalNumber = 1;
        EEPROM.write(GAME2_STORAGE, animalNumber);

        pressedButton->setLED(false);
    }
}