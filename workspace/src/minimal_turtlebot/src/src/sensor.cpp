#include <stdlib.h>
#include "../lib/sensor.hpp"
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

#include <math.h>
#include <cmath>

namespace Sensor {

    SENSOR_STATES current_state;

    SENSOR_STATES * get_sensor_state () {
        return &current_state;
    }

    SENSOR_STATES set_sensor_state (turtlebotInputs inputs) {
        uint8_t bumper = check_bumpers(inputs);
        uint8_t wheels = check_wheels(inputs);
        uint8_t cliff = check_cliff(inputs);

        SENSOR_STATES * state = new SENSOR_STATES();
        state->BUMPER = bumper;
        state->WHEEL = wheels;
        state->CLIFF = cliff;

        check_laserscan(inputs, state);

        return * state;
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
    uint8_t check_wheels (turtlebotInputs inputs){
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
    uint8_t check_cliff (turtlebotInputs inputs) {
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
 
    void check_laserscan (turtlebotInputs inputs, SENSOR_STATES * sensors) {
        float fov = 57.0f;
        float delta = 57.0f/640.0f;

        int min = 0;
        float max_dist = 1000.0f;
        float min_val = max_dist;
        for (int i = 0; i < 640; i++)
        {
            float distance = inputs.ranges[i];
            if (std::isnan(distance)) distance = max_dist;
            if (distance < min_val)
            {
                min = i;
                min_val = distance;
            }
        }

        float theta = ((float)min - 640.0f) * delta;


        ROS_INFO("theta: %f", theta);

        sensors->LASERSCAN_ANGLE = theta;
        sensors->LASERSCAN_DISTANCE = min_val;
    }

    float check_imu (turtlebotInputs inputs) {

    }
}