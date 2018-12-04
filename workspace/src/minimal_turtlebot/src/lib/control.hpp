#include "reaction.hpp"
#include "sensor.hpp"
#include "../../include/minimal_turtlebot/turtlebot_controller.h"

namespace Control 
{
    long start_time;

    const float velocity = 0.3f;
    const float angular = 0.2f;

    Reaction::TurtlebotInputs current;

    Reaction::Turtlebot_Reaction refresh (turtlebotInputs inputs);
    
    void reset_time ();
    long current_time ();
}