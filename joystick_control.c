#pragma config(Sensor, dgtl1,  leftMotorEncoder, sensorRotation)
#pragma config(Sensor, dgtl2,  rightMotorEncoder, sensorRotation)
#pragma config(Sensor, dgtl3,  bottomLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl4,  topLimitSwitch, sensorTouch)
#pragma config(Motor,  port1,           frontLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftArm1,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           leftArm2,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           backLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           conveyer,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           rightArm2,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           rightArm1,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           backRightMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          frontRightMotor, tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "constants.h"

/*----------------------------------------------------------------------------------------------------*\
|*                              - Dual Joystick Control with 4 Motors -                               *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses both the Left and the Right joysticks to run the robot using "tank control".    *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing both right-side motors (ports 2 and 3) in the "Motors and Sensors Setup" is       *|
|*        needed with the "VEX Tumbler" model, but may not be needed for all robot xconfigurations.    *|
|*    2)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    3)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]                [Type]                [Description]                   *|
|*    Motor Port 2        frontRightMotor       VEX 3-wire module     Right side motor                *|
|*    Motor Port 3        backRightMotor        VEX 3-wire module     Right side motor                *|
|*    Motor Port 4        frontLefttMotor       VEX 3-wire module     Left side motor                 *|
|*    Motor Port 5        backLeftMotor         VEX 3-wire module     Left side motor                 *|
\*----------------------------------------------------------------------------------------------------*/

void setArmsAt(int power);

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	while(true)
	{
		//Right side of the robot is controlled by the right joystick, Y-axis
		motor[frontRightMotor] = vexRT[Ch2];
		motor[backRightMotor]  = vexRT[Ch2];
		//Left side of the robot is controlled by the left joystick, Y-axis
		motor[frontLeftMotor] = vexRT[Ch3];
		motor[backLeftMotor]  = vexRT[Ch3];
		if (vexRT[Btn6U] == 1) {
			if (SensorValue[topLimitSwitch] == 0) {
				setArmsAt(ARM_POWER_HIGH);
			} else {
				setArmsAt(0);
			}
		} else if (vexRT[Btn6D] == 1) {
			if (SensorValue[bottomLimitSwitch] == 0) {
				setArmsAt(-ARM_POWER_HIGH);
			}else {
				setArmsAt(0);
			}
		} else {
			setArmsAt(0);
		}

		if (vexRT[Btn5U] ==1) {
			motor[conveyer] = CONVEYOR_POWER;
		} else if (vexRT[Btn5D] == 1) {
			motor[conveyer] = -CONVEYOR_POWER;
		} else {
			motor[conveyer] = 0;
		}
	}
}
void setArmsAt(int power) {
	motor[rightArm1] = power;
	motor[rightArm2] = power;
	motor[leftArm1] = -power;
	motor[leftArm2] = -power;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
