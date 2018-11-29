#include <stdint.h>
#include "../lib/sound.hpp"

void play_sound (uint8_t * sound_value, uint8_t soundVal){
    * sound_value = soundVal;
}