#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include "../lib/movement.hpp"

namespace Turtlebot_Library{
    void bumper_hit (float * vel, float * ang_vel, float velocity, float angular, uint8_t * sound, uint8_t bumper_data){
        bool left = (bumper_data >> 0) & 1;
        bool center = (bumper_data >> 1) & 1;
        bool right = (bumper_data >> 2) & 1;

        // Stay still for 1 second
        halt(vel, ang_vel);
        sleep(1);

        // Reverse for two seconds
        reverse(vel, velocity);
        sleep(2);

        // Rotate for two seconds
        halt(vel, ang_vel);
        if (left || center){
            right_turn(ang_vel, angular);
        }
        else if (right){
            left_turn(ang_vel, angular);
        }
        sleep(2);
        halt(vel, ang_vel);

        // Continue forward
        advance(vel, velocity);
    }

    void wheel_drop (float * vel, float * ang_vel, float velocity, float angular, uint8_t * sound, uint8_t wheel_data){

    }
}