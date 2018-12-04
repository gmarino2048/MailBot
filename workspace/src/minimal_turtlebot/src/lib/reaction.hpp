#ifndef _reaction_h
#define _reaction_h

#include <stdint.h>
#include "sensor.hpp"

namespace Reaction 
{
    struct Turtlebot_Reaction 
    {
        float velocity;
        float angular;
        uint8_t sound;
    };

    enum ReactionStates 
    {
        Default = 0,
        Backtrack = 1,
        Stop_Error = 2,
        Avoid_Obstacle = 3
    };

    extern bool running;
    extern uint8_t current_reaction;

    Turtlebot_Reaction run_reaction (Sensor::SENSOR_STATES sensors, long current_time);

    uint8_t backtrack (Turtlebot_Reaction * reaction, uint8_t direction, long current_time);
    uint8_t stop_error (Turtlebot_Reaction * reaction, long current_time);
    uint8_t avoid_obstacle (Turtlebot_Reaction * reaction, long current_time);
}
#endif