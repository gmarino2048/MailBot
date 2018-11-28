#include <stdlib.h>
#include "../lib/sensor.hpp"
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Turtlebot_Library {

    struct SENSOR_STATES {
        bool BUMPER;
        bool WHEEL;
        bool CLIFF;
        bool LASERSCAN;
        bool IMU;
        turtlebotInputs * inputs;
    };

    SENSOR_STATES current_state;

    SENSOR_STATES * get_sensor_state () {
        return &current_state;
    }

    void set_sensor_state (turtlebotInputs inputs) {

    }

    bool check_bumpers (turtlebotInputs inputs) {

    }

    bool check_wheels (turtlebotInputs inputs){

    }

    bool check_cliff (turtlebotInputs inputs) {

    }

    bool check_laserscan (turtlebotInputs inputs) {

    }

    bool check_imu (turtlebotInputs inputs) {

    }
}