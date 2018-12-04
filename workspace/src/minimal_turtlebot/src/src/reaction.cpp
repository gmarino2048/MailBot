#include "../lib/reaction.hpp"
#include "../lib/control.hpp"
#include "../lib/movement.hpp"

#include <iostream>

namespace Reaction 
{

    bool running;
    uint8_t current_reaction;

    Turtlebot_Reaction run_reaction (Sensor::SENSOR_STATES sensors, long current_time)
    {
        uint8_t next_state = Default;
        Turtlebot_Reaction reaction;

        // State machine should always stop if lifted
        if (sensors.WHEEL != 0)
        {
            ROS_INFO("Wheel Drop: %d", sensors.WHEEL);

            Control::reset_time();
            next_state = stop_error(&reaction, current_time);
        }
        
        // Next check for bumper input
        bool shouldBacktrack = !running && sensors.BUMPER != 0;
        bool isBacktracking = current_reaction == Backtrack;

        ROS_INFO("Should Backtrack: %d", shouldBacktrack);
        ROS_INFO("Running: %d", running);

        if (isBacktracking) next_state = backtrack(&reaction, -1, current_time);
        else if (shouldBacktrack) 
        {
            Control::reset_time();
            uint8_t direction;
            uint8_t bumpers = sensors.BUMPER;
            direction = bumpers && 1;

            backtrack(&reaction, direction, current_time);
        }
        

        // See if the robot is currently reacting
        if (next_state == Default) running = false;
        else running = true;

        current_reaction = next_state;
        // Last! If the robot shouldn't be doing anything else... keep advancing
        if (current_reaction == Default)
        {
            Control::reset_time();
            Movement::halt(&reaction.velocity, &reaction.angular);
            Movement::advance(&reaction.velocity, Control::velocity);
        }

        return reaction;
    }

    // -1 is last direction
    // 0 is a left turn
    // 1 is a right turn;
    uint8_t current_direction;
    uint8_t backtrack (Turtlebot_Reaction * reaction, uint8_t direction, long current_time)
    {
        // Declare Parameters
        float vel;
        float ang;
        uint8_t sound = 7;

        // Reset Direction
        if (direction < 0) direction = current_direction;
        else current_direction == direction;

        // Set Values so that pointers fill values later
        reaction->velocity = vel;
        reaction->angular = ang;
        reaction->sound = sound;

        // Stop for 1s
        if (current_time < 1e9)
        {
            Movement::halt(&vel, &ang);
            return Backtrack;
        }
        // Reverse for 2s
        if (current_time < 3e9)
        {
            Movement::halt(&vel, &ang);
            Movement::reverse(&vel, Control::velocity);
            return Backtrack;
        }
        // Turn for  3s
        if (current_time < 6e9)
        {
            if (direction)
            {
                Movement::halt(&vel, &ang);
                Movement::right_turn(&ang, Control::angular);
                return Backtrack;
            }
            else 
            {
                Movement::halt(&vel, &ang);
                Movement::left_turn(&ang, Control::angular);
                return Backtrack;
            }
        }

        return Default;
    }

    uint8_t stop_error (Turtlebot_Reaction * reaction, long current_time)
    {
        float vel = 0;
        float ang = 0;
        uint8_t sound = 4;

        reaction->velocity = vel;
        reaction->angular = ang;
        reaction->sound = sound;

        return Stop_Error;
    }

    uint8_t avoid_obstacle (Turtlebot_Reaction * reaction, long current_time)
    {

    }
}