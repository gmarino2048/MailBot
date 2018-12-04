#include "../lib/control.hpp"
#include "../lib/sensor.hpp"
#include "../lib/reaction.hpp"
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

using namespace Reaction;

namespace Control
{
    long start_time;
    turtlebotInputs current;

    Turtlebot_Reaction refresh (turtlebotInputs inputs)
    {
        current = inputs;
        Sensor::SENSOR_STATES states = Sensor::set_sensor_state(current);
        
        long timeVal = current_time();
        return Reaction::run_reaction(states, timeVal);
    }

    void reset_time ()
    {
        start_time = current.nanoSecs;
    }

    long current_time ()
    {
        return current.nanoSecs - start_time;
    }
}