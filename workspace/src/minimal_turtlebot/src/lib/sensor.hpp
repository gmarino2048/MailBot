#include <stdlib.h>
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Turtlebot_Library {
    struct SENSOR_STATES;

    SENSOR_STATES * get_sensor_state ();

    void set_sensor_state (turtlebotInputs sensor_inputs);
};