#ifndef _sensor_h
#define _sensor_h

#include <stdlib.h>
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Sensor {
    struct SENSOR_STATES {
        uint8_t BUMPER;
        uint8_t WHEEL;
        uint8_t CLIFF;
        uint8_t LASERSCAN;
        float LASERSCAN_ANGLE;
        float LASERSCAN_DISTANCE;
    };

    SENSOR_STATES * get_sensor_state ();

    SENSOR_STATES set_sensor_state (turtlebotInputs sensor_inputs);

    uint8_t check_bumpers (turtlebotInputs inputs);
    uint8_t check_wheels (turtlebotInputs inputs);
    uint8_t check_cliff (turtlebotInputs inputs);
    float check_laserscan (turtlebotInputs inputs, SENSOR_STATES * sensors);
};

#endif