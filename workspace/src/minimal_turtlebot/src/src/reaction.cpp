#include "../lib/reaction.hpp"
#include "../lib/control.hpp"
#include "../lib/movement.hpp"

#include <math.h>
#include <iostream>

namespace Reaction 
{

    float MAX_ANG_VEL = 1;
    float MAX_ANGLE = 28.5f;

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

        bool shouldAvoid = sensors.LASERSCAN_DISTANCE < 0.5f;
        bool isAvoiding = current_reaction == Avoid_Obstacle;

        if (isAvoiding) next_state = avoid_obstacle(&reaction, &sensors, current_time);
        else if (shouldAvoid)
        {
            Control::reset_time();
            next_state = avoid_obstacle(&reaction, &sensors, current_time);
        }
        
        // Next check for bumper input
        bool shouldBacktrack = !running && (sensors.BUMPER != 0 || sensors.CLIFF != 0);
        bool isBacktracking = current_reaction == Backtrack;

        if (isBacktracking) next_state = backtrack(&reaction, -1, current_time);
        else if (shouldBacktrack) 
        {
            Control::reset_time();
            uint8_t direction;
            uint8_t bumpers = sensors.BUMPER;
            uint8_t cliff = sensors.CLIFF;

            // Bumpers take precedence
            if (bumpers) direction = bumpers && 1;
            else if (cliff) direction = cliff && 1;

            next_state = backtrack(&reaction, direction, current_time);
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

            // Object avoidance without stopping
            float ang;
            if (sensors.LASERSCAN_DISTANCE < 1)
            {
                bool direction = sensors.LASERSCAN_ANGLE > 0;
                ang = MAX_ANG_VEL;

                ROS_INFO("theta: %f, distance: %f", sensors.LASERSCAN_ANGLE, sensors.LASERSCAN_DISTANCE);

                float turn;
                if (sensors.LASERSCAN_ANGLE < 0) turn = 1.0f;
                else turn = -1.0f;

                float dist_scale = 1 - (2 * sensors.LASERSCAN_DISTANCE);
                float angle_scale = (1 - (abs(sensors.LASERSCAN_ANGLE) / MAX_ANGLE));

                ang = ang * turn * dist_scale * angle_scale;
            }
            else ang = 0;

            reaction.angular = ang;
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
            reaction->velocity = vel;
            reaction->angular = ang;
            reaction->sound = sound;

            return Backtrack;
        }
        // Reverse for 2s
        if (current_time < 3e9)
        {
            Movement::halt(&vel, &ang);
            Movement::reverse(&vel, Control::velocity);

            reaction->velocity = vel;
            reaction->angular = ang;
            reaction->sound = sound;

            return Backtrack;
        }
        // Turn for  3s
        if (current_time < 6e9)
        {
            if (direction)
            {
                Movement::halt(&vel, &ang);
                Movement::right_turn(&ang, Control::angular);

                reaction->velocity = vel;
                reaction->angular = ang;
                reaction->sound = sound;
                return Backtrack;
            }
            else 
            {
                Movement::halt(&vel, &ang);
                Movement::left_turn(&ang, Control::angular);

                reaction->velocity = vel;
                reaction->angular = ang;
                reaction->sound = sound;

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

    uint8_t avoid_obstacle (Turtlebot_Reaction * reaction, Sensor::SENSOR_STATES * sensors, long current_time)
    {
        float vel;
        float ang;
        uint8_t sound = 7;

        Movement::halt(&vel, &ang);
        sound = 2;

        if (current_time < 3e9)
        {
            reaction->velocity = vel;
            reaction->angular = ang;
            reaction->sound = sound;

            ROS_INFO("Waiting: %ld", current_time);
            return Avoid_Obstacle;
        }

        if (sensors->LASERSCAN_DISTANCE < 0.5f)
        {
            vel = 0;
            ang = Control::angular;
            sound = 7;

            reaction -> velocity = vel;
            reaction -> angular = ang;
            reaction -> sound = sound;

            ROS_INFO("Distance: %f", sensors->LASERSCAN_DISTANCE);

            return Avoid_Obstacle;
        }
        else return Default;
    }
}