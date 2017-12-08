//********************
//     COMPETITION
//********************

#pragma platform(VEX)
#pragma competitionControl(Competition)

#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"


//********************
//     INCLUDES
//********************

#include "config.c"
#include "movement.c"
#include "auto.c"


//********************
//     CONTROL
//********************

// Preconfig
task pre_auton()
{

}

// What to do when autonomous period starts
task autonomous()
{
	autoLeft();
	//autoRight();
}

// What to do when user control period starts
task userControl()
{
	while (true) {

	}
}
