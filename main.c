#pragma config(Sensor, in1,             pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,           carrierBtn,     sensorTouch)
#pragma config(Sensor, dgtl2,           rightUltSensor, sensorSONAR_mm)
#pragma config(Sensor, dgtl4,           leftUltSensor,  sensorSONAR_mm)
#pragma config(Motor,  port2,           leftWheel,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightWheel,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           carrierRight,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           carrierLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armLeft,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armRight,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           claw,           tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//************************
//         CONFIG
//************************
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"


//************************
//       VARIABLES
//************************
bool up = true;   // Whether the carrier is up or not


//*************************
//         METHODS
//*************************

/***** MOVEMENT *****/

/* Move the robot forward/backward
		wheelPower: [-127, 127] how fast the robot goes
				(+) => forwards
				(-) => backwards      */
void moveWheels(int wheelPower) {
	motor[leftWheel] = wheelPower;
	motor[rightWheel] = -wheelPower-1;
}

/* Stops all wheel movement */
void stopWheels() {
	motor[leftWheel] = 0;
	motor[rightWheel] = 0;
}

/* Turns 180 counterclockwise */
void turnLeft() {
	motor[leftWheel] = 60;
	motor[rightWheel] = 60;
	sleep(3000);
	stopWheels();
}

/* Turns 180 clockwise */
void turnRight() {
	motor[leftWheel] = -60;
	motor[rightWheel] = -60;
	sleep(3000);
	stopWheels();
}


//***** CLAW *****
		//<nothing here...>


//***** ARM *****

int horizontal = 1100; // Should be the potentiometer value when the arm is fully horizontal
int vertical = 2850;   // Should be the potentiometer value when the arm is fully vertical
int weight = 25;       // Higher weight = more power against gravity

/* Moves the arm up or down- also compensates for gravity
		speed: [-127, 127] how fast the arm should move
				(+) => Up
				(-) => Down    */
void moveArm(int speed) {
	int gravity = (int) (weight*cos(PI/2*(SensorValue[pot]-horizontal)/(vertical-horizontal)));

	motor[armLeft] = speed+gravity;
	motor[armRight] = -(speed+gravity);
}


//***** CARRIER *****

/* Pulls the carrier up into the robot */
void raiseCarrier() {
	//gradually increase motor speed for about 2 seconds
	for(int base = 1; base <= 10; base++)
	{
		motor[carrierLeft] = base*base;
		motor[carrierRight] = -base*base;
		sleep(186);
	}
	//stop carrier motors
	motor[carrierLeft] = 0;
	motor[carrierRight] = 0;
}

/* Lowers the carrier onto the ground */
void lowerCarrier() {
	//gradually increase motor speed for about 2 seconds
	for(int base = 1; base <= 10; base++)
	{
		motor[carrierLeft] = -base*base;
		motor[carrierRight] = base*base;
		sleep(105);
	}
	//stop carrier motors
	motor[carrierRight] = 0;
	motor[carrierLeft] = 0;
}


//***** AUTONOMOUS *****

/* Execute autonomous period */
void auto() {
	//lower carrier
	lowerCarrier();
	//move forward until button sensor is pressed
	moveWheels(75);
	waitUntil(SensorValue[carrierBtn]==1);
	stopWheels();
	//raise carrier
	raiseCarrier();
	//move back for set amount of time
	moveWheels(-75);
	sleep(2550);
	//stop
	stopWheels();
	//turn 180 degrees in the direction that is opposite of the wall
	if(SensorValue[rightUltSensor] < SensorValue[leftUltSensor]){
		turnLeft();
	} else{
		turnRight();
	}
	//lower carrier and put mobile goal in 5 point zone
	lowerCarrier();
	//move back into colored square
	moveWheels(-75);
	sleep(3000);
	stopWheels();
}


//***** DRIVING *****
/* Controls:
		Left joystick  => Left wheels
		Right joystick => Right wheels
		5U ........... => Raise arm
		5D ........... => Lower arm
		6U ........... => Open claw
		6D ........... => Close claw
		8R ........... => Lower carrier
		8D ........... => Raise carrier
*/

/* Curves the input to give a smoother driving experience
https://www.desmos.com/calculator/xv2hbpabjm        */
int modify(int input) {
	return (input+(pow(input,5)/8192-pow(input,3))/8192)/3;
}

/* Update wheel powers based on controller */
void updateWheels() {
	motor[leftWheel] = modify(vexRT[Ch3]);
	motor[rightWheel] = -modify(vexRT[Ch2]);
}

/* Update claw power based on controller */
void updateClaw() {
	if(vexRT[Btn6U] == 1) // If upper Z button down
		motor[claw] = 25;
	else if(vexRT[Btn6D] == 1) // If lower Z button down
		motor[claw] = -25;
	else
		motor[claw] = 0;
}


int upSpeed = 25;
int downSpeed = 15;
/* Updates arm control based on controller and potentiometer */
void updateArm() {
	// If 5U button pressed
	if(vexRT[Btn5U] == 1) {
		if(SensorValue[pot] > vertical) {
			moveArm(downSpeed);
		} else {
			moveArm(upSpeed);
		}
	// If 5D button pressed
	} else if(vexRT[Btn5D] == 1) {
		if (SensorValue[pot] > vertical) {
			moveArm(-upSpeed);
		} else {
			moveArm(-downSpeed);
		}
	// Neither button pressed
	} else {
		moveArm(0);
	}
}

/* Updates carrier powers based on controller */
void updateMobileGoal() {
	// If carrier is currently up and lower button pressed
	if(up && vexRT[Btn8R] == 1) {
		lowerCarrier();
		up = false;
	// If carrier is currently down and raise button pressed
	} else if(!up && vexRT[Btn8D] == 1) {
		raiseCarrier();
		up = true;
	}
}


//*************************
//          TASKS
//*************************

void pre_auton() {
	bStopTasksBetweenModes = true;
}

task autonomous() {
	auto();
}

task usercontrol() {
	while (true) {
		updateWheels();
		updateClaw();
		updateArm();
		updateMobileGoal();
	}
}
