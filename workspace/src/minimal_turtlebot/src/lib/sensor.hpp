#ifndef _sensor_h
#define _sensor_h

#include <stdlib.h>
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Sensor {
    struct SENSOR_STATES;

    SENSOR_STATES * get_sensor_state ();

    void set_sensor_state (turtlebotInputs sensor_inputs);

    bool check_bumpers (turtlebotInputs inputs);
    bool check_wheels (turtlebotInputs inputs);
    bool check_cliff (turtlebotInputs inputs);
    bool check_laserscan (turtlebotInputs inputs);
    bool check_imu (turtlebotInputs inputs);
};

#endif