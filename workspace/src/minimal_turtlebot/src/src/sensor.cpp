#include <stdlib.h>
#include "../lib/sensor.hpp"
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Turtlebot_Library {

    struct SENSOR_STATES {
        uint8_t BUMPER;
        uint8_t WHEEL;
        uint8_t CLIFF;
        uint8_t LASERSCAN;
        uint8_t IMU;
    };

    SENSOR_STATES current_state;

    SENSOR_STATES * get_sensor_state () {
        return &current_state;
    }

    void set_sensor_state (turtlebotInputs inputs) {
        bool bumper = check_bumpers(inputs);
        bool wheels = check_wheels(inputs);
    }

    /**
     * Distills which bumpers have been pressed and saves
     * the result in the three LSB's of the return value.
     * The least significant bit denotes the right bumper,
     * the second least denotes the left bumper, and the
     * third least denotes the right bumper.
     */
    uint8_t check_bumpers (turtlebotInputs inputs) {
        uint8_t value = 0;

        if (inputs.rightBumperPressed){
            value += 0b00000001;
        }
        if (inputs.centerBumperPressed){
            value += 0b00000010;
        }
        if (inputs.leftBumperPressed){
            value += 0b00000100;
        }

        return value;
    }

    /**
     * Saves the state of the wheel drop sensors in another
     * uint8_t structure. If LSB is hot, then right wheel has
     * dropped, if LSB2 is hot, then left wheel has dropped.
     */
    bool check_wheels (turtlebotInputs inputs){
        uint8_t value = 0;

        if (inputs.rightWheelDropped){
            value += 0b00000001;
        }
        if (inputs.leftWheelDropped){
            value += 0b00000010;
        }

        return value;
    }

    /**
     * Checks the cliff sensor and stores the sensor data in
     * a single uint. If sensor 0 triggered, then LSB is hot,
     * if sensor 1 is triggered, then LSB2 is hot. If sensor 2
     * is triggered, then LSB3 is hot.
     */
    bool check_cliff (turtlebotInputs inputs) {
        uint8_t value = 0;

        if (inputs.sensor0State){
            value += 0b00000001;
        }
        if (inputs.sensor1State){
            value += 0b00000010;
        }
        if (inputs.sensor2State){
            value += 0b00000100;
        }
    }
 
    bool check_laserscan (turtlebotInputs inputs) {

    }

    bool check_imu (turtlebotInputs inputs) {

    }
}