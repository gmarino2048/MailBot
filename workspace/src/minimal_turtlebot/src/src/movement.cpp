#include<stdlib.h>
#include "../lib/movement.hpp"

namespace Movement{
    // The state responsible for controlling robot behavior

    uint8_t movement_state = STOPPED;

    uint8_t get_state () {
        return movement_state;
    }

    void do_action(uint8_t desired_state, float velocity, float angular, float * vel, float * ang_vel){
        halt(vel, ang_vel);

        switch (desired_state){
            case STOPPED: 
                break;
            case FORWARD:
                if (!(movement_state == FORWARD)) advance(vel, velocity);
                break;
            case REVERSE: 
                if (!(movement_state == REVERSE)) reverse(vel, velocity);
                break;
            case RIGTURN:
                if (!(movement_state == RIGTURN)) right_turn(ang_vel, angular);
                break;
            case LEFTURN:
                if (!(movement_state == LEFTURN)) left_turn(ang_vel, angular);
                break;
            default: 
                break;
        }
    }

    void halt (float * vel, float * ang_vel){
        * vel = 0;
        * ang_vel = 0;
        
        movement_state = STOPPED;
    }

    void advance (float * vel, float velocity) {
        * vel = velocity;
        
        movement_state = FORWARD;
    }

    void reverse(float * vel, float velocity) {
        * vel = -1.0 * velocity;
        
        movement_state = REVERSE;
    }

    void right_turn (float * ang_vel, float angular) {
        * ang_vel = angular;
        
        movement_state = RIGTURN;
    }

    void left_turn (float * ang_vel, float angular) {
        * ang_vel = -1 * angular;
        
        movement_state = LEFTURN;
    }
}