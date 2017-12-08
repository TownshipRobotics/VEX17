#include "config.c"

#ifndef _MOVEMENT_C_
#define _MOVEMENT_C_



/* moveWheels - DRIVES ROBOT
wheelPower: [-127, 127] fastest wheel speed (negative to go backwards)
curve: [-127, 127] amount to curve (negative curves counterclockwise)

Example Wheel Outputs
curve ->  left,         right        (description)
0     ->  wheelPower,   wheelPower   (forward)
64    ->  wheelPower,   0            (spin around right wheels)
128   ->  wheelPower,   -wheelPower  (in place spin clockwise)
-128  ->  -wheelPower,  wheelPower   (in place spin counterclockwise)
*/
void moveWheels(int wheelPower, int curve)
{
	// Amount to lower wheelPower on respective wheel
	int curveMod = abs(curve)*wheelPower*2/128;

	// Start left and right at wheelPower
	int left, right;
	left = right = wheelPower;

	// Subtract curveMod from one of them
	if (curve < 0) left -= curveMod;
	else right -= curveMod;

	// Set left and right motors
	motor[leftFront] = -test;
	motor[leftBack] = -left;
	motor[rightFront] = right;
	motor[rightBack] = right;
}

/*

*/


#endif // _MOVEMENT_C_
