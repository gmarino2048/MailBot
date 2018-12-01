#ifndef _sound_h
#define _sound_h

#include<stdint.h>

namespace Sound{
    const uint8_t TURN_ON = 0;
    const uint8_t TURN_OFF = 1;
    const uint8_t RECHARGE = 2;
    const uint8_t BUTTON_PRESS = 3;
    const uint8_t ERROR = 4;
    const uint8_t START_CLEAN = 5;
    const uint8_t STOP_CLEAN = 6;

    void play_sound(uint8_t * sound_value, uint8_t soundVal);
};

#endif