#include "Button.h"
#include "ButtonsArray.h"

void game4_trafficlight(ButtonsArray* buttonsArray, DFPlayerMini_Fast * player)
{
    player->playFolder(01, 002); // "bus stop"
    delay(3500);

    player->playFolder(40, 001); // "светофор"
    delay(300); while (player->isPlaying()) delay(100); // wait until the song is played 
    
    uint32_t gameStartTime = millis();
    int16_t initialVolume = 15;

    while (true)
    {
        if (millis() - gameStartTime > 300000) 
            return;

        
        buttonsArray->getButton(4)->setLED(true);
        delay(10000);

        buttonsArray->getButton(3)->setLED(true);
        delay(2000);

        buttonsArray->getButton(4)->setLED(false);
        buttonsArray->getButton(3)->setLED(false);
        buttonsArray->getButton(2)->setLED(true);
        player->volume(initialVolume);
        player->playFolder(40, 002); 
        delay(10000);

        buttonsArray->getButton(3)->setLED(true);
        buttonsArray->getButton(2)->setLED(false);
        for (int i = initialVolume; i > 0; i--)
        {
            player->volume(i);
            delay(2000/initialVolume);
        }
        
        buttonsArray->getButton(3)->setLED(false);
        player->stop();
        player->volume(initialVolume);
    }
}