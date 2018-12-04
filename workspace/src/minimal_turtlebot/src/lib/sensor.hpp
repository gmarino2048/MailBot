#ifndef _sensor_h
#define _sensor_h

#include <stdlib.h>
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Sensor {
    struct SENSOR_STATES;

    SENSOR_STATES * get_sensor_state ();

    void set_sensor_state (turtlebotInputs sensor_inputs);

    uint8_t check_bumpers (turtlebotInputs inputs);
    uint8_t check_wheels (turtlebotInputs inputs);
    uint8_t check_cliff (turtlebotInputs inputs);
    float check_laserscan (turtlebotInputs inputs);
    float check_imu (turtlebotInputs inputs);
};

#endif