#pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Motor,  port2,           leftWheel,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightWheel,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           carrier,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armRight,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//************************
//       VARIABLES
//************************
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;


//*************************
//         METHODS
//*************************

/***** MOVEMENT *****/

//move the robot forward or backward
//wheelPower is how fast the robot goes, values -127 to 127 are acceptable
	//if wheelPower is positive, robot goes forwards
	//if wheelPower is negative, robot goes backwards
//curve is how much the robot should turn tbd how the robot will use that value to turn though...
void moveWheels(int wheelPower)
{
	leftMotorSpeed = wheelPower;
	rightMotorSpeed = -wheelPower-1;
	motor[leftWheel] = leftMotorSpeed;
	motor[rightWheel] = rightMotorSpeed;
}

//stops wheel motors so robot stops moving
void stopWheels(){
	motor[leftWheel] = 0;
	motor[rightWheel] = 0;
}

//***** CLAW *****

//opens the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void openClaw()
{
	motor[claw] = 35;
	sleep(1100);
	motor[claw] = 0;
}

//closes the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void closeClaw(int power)
{
	motor[claw] = -power;
	sleep(700);
	motor[claw] = 0;
}

//***** ARM *****

int horizontal = 120;
int gravConst = 40;
void moveArm(int speed) {
  int gravity = gravConst-abs(horizontal-SensorValue[pot])*gravConst/600;

  motor[armLeft] = -(speed+gravity);
  motor[armRight] = speed+gravity;
}

//lifts up a yellow cone in its claw and holds it mid air
void liftCone()
{
	motor[claw] = -45;
	sleep(750);
	motor[claw] = -20;
	motor[armLeft] = -110;
	motor[armRight] = 110;
	//wait 1 second
	sleep(1000);
	//stop motors
	motor[armLeft] = -30;
	motor[armRight] = 30;
}

//places the cone the robot is holding midair on the mobile goal in front of it
void coneOnMobileGoal()
{
	//move arm motors until cone on goal
	motor[armLeft] = -10;
	motor[armRight] = 10;
	sleep(2500);	//wait .25 seconds
	motor[armLeft] = -30;
	motor[armRight] = 30;
	//let go of cone
	openClaw();
}

//***** AUTONOMOUS *****

void auto()
{
	closeClaw(35);
	liftCone();
	moveWheels(50);
	sleep(3500);
	stopWheels();
	coneOnMobileGoal();
	moveWheels(50);
	sleep(1750);
	stopWheels();
}

//***** DRIVING *****

int modify(int input) {
	//return pow(input,3)/16384;
  return (input+(pow(input,5)/8192-pow(input,3))/8192)/3;
}

//move the wheels depending on the values sent from the right and left joysticks
//tank controls used for 2 joysticks
	//left joystick moves left wheel
	//right joystick moves right wheel
	//joystick up moves wheel forward
	//joystick down moves that wheel backward
	//move robot straight forward = left and right forward
	//move robot straight backward = left and right backward
	//pivot robot left = left backward, right forward
	//pivot robot right = left forward, right backward
	//car turn left = left not moved, right forward
	//car turn right = left forward, right not moved
	//left curve = left and right forward, but right is more forward than the other
	//right curve = left and right forward, but left is more forward than the other
void updateWheels(){
	//***** TANK CONTROLS *****
	//original speed constants were .5, kept the same at request from testing
	//motor[leftWheel] = modify(vexRT[Ch3]);
	//motor[rightWheel] = -modify(vexRT[Ch2]);

	//***** ONE JOYSTICK TURNS, ONE JOYSTICK GOES FORWARD AND BACKWARD *****
	//if joystick is being used, don't bother doing calculations
	if(vexRT[Ch1]==0 && vexRT[Ch3]==0){
		return;
	}
	//last year, we used the right joystick to drive the wheels
	//to calcuate the power to move the motor at, take the distance between (ch4 value, ch3 value) and (0,0) or the square root of ((x^2)+(y^2))
	//int calculatedPower = sqrt(pow(vexRT[Ch1],2)+pow(vexRT[Ch3],2));
	//if you were to face the same direction the robot is, left wheel moves -1*(calculated power) and right wheel moves the calculated power
	//to turn, make the power go to the motors at a percentage
	//percentage calculation is probably (ch4Value/254)+.5
		//254 is the denominator because it is the max motor speed, 127, times 2
	//if ch4 > 0
	if(vexRT[Ch1]<-10){
		//right motor speed = ((ch4Value/254)+.5)*(calculated power)
		rightMotorSpeed = (vexRT[Ch1]/254+.5)*vexRT[Ch3];	//calculatedPower;
		//left motor speed = 1-(right motor speed)
		leftMotorSpeed = -(1-rightMotorSpeed);
	}
	//if ch4 < 0
	else if(vexRT[Ch1]>10){
		//left motor speed = ((ch4Value/254)+.5)*(calculated power)
		leftMotorSpeed = -((vexRT[Ch1]/254+.5)*vexRT[Ch3]);	//calculatedPower);
		//right motor speed = 1-(left motor speed)
		rightMotorSpeed = 1-leftMotorSpeed;
	}
	//if joystick at center and up or down
	else{
		//return
		leftMotorSpeed = -calculatedPower;
		rightMotorSpeed = calculatedPower;
	}
	//add modify to motor speeds later
	//left motor go
	motor[leftWheel] = leftMotorSpeed;
	//right motor go
	motor[rightWheel] = rightMotorSpeed;
}

//opens or closes claw
	//if 6U is pressed, it opens
	//if 6D is pressed, it closes
void updateClaw()
{
    if(vexRT[Btn6U] == 1) // If upper Z button down
        motor[claw] = 25;
    else if(vexRT[Btn6D] == 1) // If lower Z button down
        motor[claw] = -25;
    else
    	motor[claw] = 0;
}

//raises, lowers, or stops moving the arm depending if button 5U, 5D, or neither are pressed
	//5U raises arm
	//5D lowers arm
void updateArm()
{
	int power = 0;

	if(vexRT[Btn5D] == 1) //if left lower Z button is pressed
	{
		power += 1;
		motor[armLeft] = -7-power;
		motor[armRight] = 6+power;
	}
	else if((SensorValue[pot] <= 0)||((vexRT[Btn5U] == 0) && (vexRT[Btn5D] == 0)))
	{
		motor[armLeft] = -30;
		motor[armRight] = 30;
	}
  else if(vexRT[Btn5U] == 1) //if left upper Z button is pressed
	{
		power += 60;
		motor[armLeft] = -50-power;
		motor[armRight] = 50+power;
	}

}

//lifts the mobile goal, needs to be heavily tested
void raiseCarrier()
{
	//move carrier motors at speed so it should difinitely be able to lift the mobile goal
	motor[carrier] = 100;
	//wait 1 second, needs to be tested and probably changed but this is the test value
	sleep(1000);
	//stop carrier motors
	motor[carrier] = 0;
}

//lowers the mobile goal, needs to be heavily tested
void lowerCarrier()
{
	//move carrier motors at the same descending speed the arm has, 6
	motor[carrier] = -50;
	//wait 1 second, needs to be tested and probably changed but this is the test value
	sleep(1000);
	//stop carrier motors
	motor[carrier] = 0;
}

//claw - 6U opens
// 6D close
//arm - 5U raises up
// 5D lowers
//mobile goal
//8D raises
//8R lowers
//left and right joysticks controls wheels with tank controls


//*************************
//          TASKS
//*************************

void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{
  auto();
}

task usercontrol()
{
  // User control code here, inside the loop
	//waitUntil(vexRT[Btn8R] == 1)
	//auto();

  while (true)
  {
    updateWheels();
		updateClaw();
		updateArm();
  }
}
