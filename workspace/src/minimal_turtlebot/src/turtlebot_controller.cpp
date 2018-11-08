#include "minimal_turtlebot/turtlebot_controller.h"

uint64_t timer_start;
uint64_t backward_time = 1e6;
uint64_t rotation_time = 2e6;

int state = 0;

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
	if (turtlebot_inputs.centerBumperPressed) {
		state = 1;
	}

	switch (state) {
		case 0: // Move forward
			*vel = 0.1;
			*ang_vel = 0.0;
			if (turtlebot_inputs.centerBumperPressed) {
				state = 1;
			}
			break;
		case 1: // Move backward for 1 second
			timer_start = turtlebot_inputs.nanoSecs;
			state = 2;
			break;
		case 2: // Wait for 1 sec, then enter turn
			*vel = 0.1;
			if (turtlebot_inputs.nanoSecs - timer_start >= backward_time) {
				timer_start = turtlebot_inputs.nanoSecs;
				state = 3;
			}
			break;
		case 3: // Rotate for 2 secs
			*vel = 0;
			*ang_vel = 0.1;
			if (turtlebot_inputs.nanoSecs - timer_start >= rotation_time){
				state = 0;
			}
	}
}

