#include "../include/minimal_turtlebot/turtlebot_controller.h"
#include "./lib/control.hpp"
#include "./lib/reaction.hpp"

// Define the movement constants
#define VEL 0.1
#define ANG_VEL 0.3

// The state responsible for sensor input
uint8_t sensor_state;
void set_sensor_state (turtlebotInputs inputs);

// Define the sensor state values
#define OK 0
#define BUMPER 1
#define CLIFF 2
#define WHEEL_DROP 4

// Robot reaction functions


void turtlebot_controller(turtlebotInputs turtlebot_inputs, uint8_t *soundValue, float *vel, float *ang_vel)
 {
	//Place your code here! you can access the left / right wheel 
	//dropped variables declared above, as well as information about
	//bumper status. 
	
	//outputs have been set to some default values. Feel free 
	//to change these constants to see how they impact the robot. 

	//*vel = 0.2; // Robot forward velocity in m/s
	//0.7 is max and is a lot
	//*ang_vel = 0.2;  // Robot angular velocity in rad/s
	//0.7 is max and is a lot 
  
	//*soundValue = 0;
  
	//here are the various sound value enumeration options
	//soundValue.OFF
	//soundValue.RECHARGE
	//soundValue.BUTTON
	//soundValue.ERROR
	//soundValue.CLEANINGSTART
	//soundValue.CLEANINGEND 

	// Sensor input zone

/*
	switch (state) {
		case 0: // Move forward
			*vel = VEL;
			*ang_vel = 0.0;
			if (turtlebot_inputs.centerBumperPressed) {
				state = 1;
				direction = true;
			}
			else if (turtlebot_inputs.rightBumperPressed) {
				state = 1;
				direction = true;
			}
			else if (turtlebot_inputs.leftBumperPressed) {
				state = 1;
				direction = false;
			}
			break;
		case 1: // Move backward for 1 second
			*vel = 0;
			timer_start = turtlebot_inputs.nanoSecs;
			state = 2;
			break;
		case 2: // Wait for 1 sec, then enter turn
			*vel = -VEL;
			if (turtlebot_inputs.nanoSecs - timer_start >= backward_time) {
				timer_start = turtlebot_inputs.nanoSecs;
				state = 3;
			}
			break;
		case 3: // Rotate for 2 secs
			*vel = 0;
			if (direction) *ang_vel = ANGULAR_VEL;
			else *ang_vel = -0.3;

			if (turtlebot_inputs.nanoSecs - timer_start >= rotation_time){
				state = 0;
			}
			break;
	}*/

	Reaction::Turtlebot_Reaction reaction = Control::refresh(turtlebot_inputs);
	
	*vel = reaction.velocity;
	*ang_vel = reaction.angular;
	*soundValue = reaction.sound;
}
