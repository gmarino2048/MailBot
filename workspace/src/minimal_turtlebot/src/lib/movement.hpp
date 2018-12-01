#ifndef _movement_h
#define _movement_h

#include <stdint.h>

namespace Movement {
    // Define the action state values

    enum MOVEMENT_STATES{
        STOPPED = 0,
        FORWARD = 1,
        REVERSE = 2,
        RIGTURN = 3,
        LEFTURN = 4
    };

    // Action State machine
    uint8_t get_state ();
    void do_action(uint8_t desired_state, float velocity, float angular, float * vel, float * ang_vel);

    // Robot movement functions
    void halt (float * vel, float * ang_vel);
    void advance (float * vel, float velocity);
    void reverse (float  * vel, float velocity);
    void right_turn (float * ang_vel, float angular);
    void left_turn (float * ang_vel, float angular);
}

#endif