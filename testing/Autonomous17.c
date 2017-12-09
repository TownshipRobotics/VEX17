#pragma config(Motor,  port2,           leftFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           armRight,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
//int leftFrontMotor = motor1;
//int rightFrontMotor = motor2;
//int leftBackMotor = motor3;
//int rightBackMotor = motor4;
//int claw = motor5;
//int armLeftMotor = motor6;
//int armRightMotor = motor11;
//int pouchBackLeftMotor = motor7;
//int pouchFrontLeftMotor = motor8;
//int pouchBackRightMotor = motor9;
//int pouchFrontRightMotor = motor10;
boolean left = true;

/***** MOVEMENT *****/

//move the robot forward or backward
//wheelPower is how fast the robot goes, values -127 to 127 are acceptable
	//if wheelPower is positive, robot goes forwards
	//if wheelPower is negative, robot goes backwards
//curve is how much the robot should turn tbd how the robot will use that value to turn though...
void moveWheels(int wheelPower)
{
	leftMotorSpeed = -wheelPower;
	rightMotorSpeed = wheelPower;
	motor[leftFrontMotor] = leftMotorSpeed;
	motor[leftBackMotor] = leftMotorSpeed;
	motor[rightFrontMotor] = rightMotorSpeed;
	motor[rightBackMotor] = rightMotorSpeed;
}

//turn in place
//power is what direction and how fast to turn, values -127 to 127 are acceptable
	//if power is a positive integer it goes clockwise
	//if power is a negative integer it goes counterclockwise
void turn(int power)
{
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor] = -power;
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = -power;
}

//stops wheel motors so robot stops moving
void stopWheels(){
	motor[leftFrontMotor] = 0;
	motor[leftBackMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightBackMotor] = 0;
}

//lowers mobile goal lift and moves back to get lift under mobile goal
void lowerMobileGoal()
{

}

//lifts the mobile goal behind it and places it into the pouch
void liftMobileGoal()
{

}

//opens the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void openClaw()
{
	motor[claw] = 35;
	sleep(500);
	motor[claw] = 0;
}

//closes the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void closeClaw()
{
	motor[claw] = -35;
	sleep(500);
	motor[claw] = 0;
}

//lifts up a yellow cone in its claw and holds it mid air
void liftCone()
{
	closeClaw();
	motor[armLeft] = -50;
	motor[armRight] = 50;
	//wait 1 second
	sleep(1000);
	//stop motors
	motor[armLeft] = 0;
	motor[armRight] = 0;
}

//places the cone the robot is holding midair on the mobile goal in the pouch
void coneOnMobileGoal()
{
	//move arm motors until cone on goal
	motor[armLeft] = 50;
	motor[armRight] = -50;
	sleep(750);	//wait .75 seconds
	motor[armLeft] = 0;
	motor[armRight] = 0;
	//let go of cone
	openClaw();
}

/***** AUTONOMOUS *****/
task main()
{
	//new algorithm
	//if left
	if(left)
	{
		//turn 45 degrees? left
		turn(-30);
		sleep(150);
		stopWheels();
		//go straight until you reach white line
		moveWheels(50);
		waitUntil(SensorValue(lineTracker) < 1000);
		stopWheels();
		//turn 20 degrees? right
		turn(30);
		sleep(70);
		stopWheels();
		//close claw
		closeClaw();
		//open claw
		openClaw();
		//pick up cone
		liftCone();
		//turn back 20 degrees left (or however much you turned before)
		turn(-30);
		sleep(70);
		stopWheels();
		//move forward until you reach colored square where mobile goal is
		moveWheels(50);
		waitUntil(SensorValue(lineTracker) < 1500);
		stopWheels();
		//place cone on mobile goal
		coneOnMobileGoal();
		//maybe ready robot for driver phase
	}
	//else 
	else
	{
		//turn 45 degrees? right
		turn(30);
		sleep(150);
		stopWheels();
		//go straight until you reach white line
		moveWheels(50);
		waitUntil(SensorValue(lineTracker) < 1500);
		stopWheels();
		//turn 20 degrees? left
		turn(-30);
		sleep(70);
		stopWheels();
		//close claw
		closeClaw();
		//open claw
		openClaw();
		//pick up cone
		liftCone();
		//turn back 20 degrees right (or however much you turned before)
		turn(30);
		sleep(70);
		stopWheels();
		//move forward until you reach colored square where mobile goal is
		moveWheels(50);
		waitUntil(SensorValue(lineTracker) < 1500);
		stopWheels();
		//place cone on mobile goal
		coneOnMobileGoal();
		//maybe ready robot for driver phase
	}

	//og algotithm
	//turn clockwise
		//45 degrees i think
	//turn(50);
		//move forward until you can grab cone
		//stop
	//pick up cone
	//drive clockwise forward
	//drive backwards
		//until bumper sensor hits mobile goal(then have robot move forward a little and lower the mobile goal lift, and move forward to pick up mobile goal)
	//pick up mobile goal
	//place cone on mobile goal
	//turn clockwise in an arc until you reach the 10 point zone ( set one motor to a higher speed than the other)
	//wait for driver phase
}
