#ifndef _reaction_h
#define _reaction_h

#include <stdint.h>
#include "sensor.hpp"
#include "control.hpp"

namespace Reaction 
{
    struct Turtlebot_Reaction;

    enum ReactionStates 
    {
        Default = 0,
        Backtrack = 1,
        Stop_Error = 2,
        Avoid_Obstacle = 3
    };

    bool running;
    uint8_t current_reaction;

    Turtlebot_Reaction run_reaction (Sensor::SENSOR_STATES sensors, long current_time);

    uint8_t backtrack (Turtlebot_Reaction * reaction, uint8_t direction, long current_time);
    uint8_t stop_error (Turtlebot_Reaction * reaction, long current_time);
    uint8_t avoid_obstacle (Turtlebot_Reaction * reaction, long current_time);
}
#endif