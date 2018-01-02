#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port2,           leftWheel,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightWheel,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           carrier,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armRight,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//declare variables below
//doubles don't exist in RobotC apparently, there is only floats


//move the wheels depending on the values sent from the right and left joysticks
//tank controls used
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
void moveWheels(){
	//original speed constants were .5, kept the same at request from testing
	motor[leftWheel] = .75*vexRT[Ch3];
	motor[rightWheel] = .75*-vexRT[Ch2];
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
	else if((SensorValue[potentiometer] <= 0)||((vexRT[Btn5U] == 0) && (vexRT[Btn5D] == 0)))
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


//method to raise arm but can't do anything else until it stops moving
//supposed to be used with if(vexRT[Btn5U] == 1)
//just here in case updateArm doesn't work out
//void raiseArm(){
//	motor[armLeft] = 50;
//	motor[armRight] = -50;
//	waitUntil(vexRT[Btn5U] == 0);
//	motor[armLeft] = 0;
//	motor[armRight] = 0;
//}

//method to lower arm but can't do anything else until it stops moving
//supposed to be used with if(vexRT[Btn5D] == 1)
//just here in case updateArm doesn't work out
//void lowerArm(){
//	motor[armLeft] = -50;
//	motor[armRight] = 50;
//	waitUntil(vexRT[Btn5D] == 0);
//	motor[armLeft] = 0;
//	motor[armRight] = 0;
//}

//lifts the mobile goal, needs to be heavily tested
void raiseCarrier()
{
	//move carrier motors at speed so it should difinitely be able to lift the mobile goal
	motor[carrier] = -100;
	//wait 1 second, needs to be tested and probably changed but this is the test value
	sleep(1000);
	//stop carrier motors
	motor[carrier] = 0;
}

//lowers the mobile goal, needs to be heavily tested
void lowerCarrier()
{
	//move carrier motors at the same descending speed the arm has, 6
	motor[carrier] = 10;
	//wait 1 second, needs to be tested and probably changed but this is the test value
	sleep(1000);
	//stop carrier motors
	motor[carrier] = 0;
}

//raises or lowers the mobile goal carrier depending if button 8D, 8R, or neither are pressed
	//8D lifts mobile goal
	//8R lowers mobile goal
void updateMobileGoal()
{
	if(vexRT[Btn8D] == 1)
		raiseCarrier();
	else if(vexRT[Btn8R] == 1)
		lowerCarrier();
}


//claw - 6U opens
// 6D close
//arm - 5U raises up
// 5D lowers
//mobile goal
//8D raises
//8R lowers
//left and right joysticks controls wheels with tank controls

//make sure main() is the last "task", weird C mechanic
task main()
{
	//apparently does not compile, but book says "this command should be the first thing in your "task main()" so idk
	//will not set up any motors and sensors, you must manually set the motos and sensors in the 'Motors and Sensors Setup' menu
	//robotType();

	//only two motors will be used for the base so we can use the rest to lift the cones and mobile goal

	while(true){
		moveWheels();
		updateClaw();
		updateArm();
		updateMobileGoal();
	}
}
