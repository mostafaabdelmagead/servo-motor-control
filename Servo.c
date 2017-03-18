/*
 * Servo.c
 *
 *  Created on: Apr 29, 2015
 *      Author: Ahmed
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "Servo.h"
#include "Servo_private.h"
#include "utils_functions.h"

//////////global variables for timer interrupt and degrees of SW PWM Angles/////////////
volatile uint8_t anglesArr[180];
volatile uint8_t thisTime = 0;
/////////////////////////////////////////////////////////////////////////////////////////

/////////for PWM configrations/////////////
volatile static uint32_t ui32Load;
volatile static uint32_t ui32PWMClock;
volatile static uint8_t ui8Adjust;
/////////for TIMER configration///////////
volatile static uint32_t ui32Period;
volatile bool flagEnableInt = false;
////////////////////////////////////

void Servo_Init(void) { // for make some calculations for frequency

	SysCtlClockSet(
	SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

	ui32PWMClock = SysCtlClockGet() / 64;

	ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	ui32Period = ((SysCtlClockGet() / 1000) / 2); // load in the timer 500u second for first time
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
	TimerEnable(TIMER0_BASE, TIMER_A);

}

void Servo_AttachChannel(uint32_t ui32Channel, int32_t ui32InitialAngle) {
	// for make the servo position in the Initial Angle
	if (ui32InitialAngle == 200)
		ui8Adjust = 0;			//make the duty cycle ZERO
	else {
		if (ui32InitialAngle > SERVO_MAX_ANGLE)
			ui32InitialAngle = SERVO_MAX_ANGLE;
		if (ui32InitialAngle < SERVO_MIN_ANGLE)
			ui32InitialAngle = SERVO_MIN_ANGLE;
		ui8Adjust = map(ui32InitialAngle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, 26,
				138); //mapping the values which are tested on real servo-motor
	}
	if (ui32Channel == SERVO_CHANNEL0) {
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		//
		// Enable pin PA2 for GPIOOutput
		//
		GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);
		Servo_SoftWare_SetAngle(16,ui32InitialAngle);
		//enable timer of SW PWM timerA
		flagEnableInt = 1;

	} else if (ui32Channel == SERVO_CHANNEL1) {
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		//
		// Enable pin PA3 for GPIOOutput
		//
		GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
		Servo_SoftWare_SetAngle(17,ui32InitialAngle);

		//enable timer of SW PWM timerA
		flagEnableInt = 1;
	} else if (ui32Channel == SERVO_CHANNEL16) {
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		//
		// Enable pin PA4 for GPIOOutput
		//
		GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
		Servo_SoftWare_SetAngle(18,ui32InitialAngle);

		//enable timer of SW PWM timerA
		flagEnableInt = 1;
	}

	if (ui32Channel <= SERVO_CHANNEL7 && ui32Channel >= SERVO_CHANNEL2) {
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

		switch (ui32Channel) {

		/*case SERVO_CHANNEL0:
		 //
		 // Enable pin PB6 for PWM0 M0PWM0
		 //
		 GPIOPinConfigure(GPIO_PB6_M0PWM0);
		 GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

		 PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
		 PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ui32Load);

		 PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
		 ui8Adjust * ui32Load / 1000);
		 PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
		 PWMGenEnable(PWM0_BASE, PWM_GEN_0);
		 break;
		 case SERVO_CHANNEL1:
		 //
		 // Enable pin PB7 for PWM0 M0PWM1
		 //
		 GPIOPinConfigure(GPIO_PB7_M0PWM1);
		 GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);

		 PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
		 PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ui32Load);

		 PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
		 ui8Adjust * ui32Load / 1000);
		 PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
		 PWMGenEnable(PWM0_BASE, PWM_GEN_0);

		 break;*/
		case SERVO_CHANNEL2:
			//
			// Enable pin PB4 for PWM0 M0PWM2
			//
			GPIOPinConfigure(GPIO_PB4_M0PWM2);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_1);

			break;
		case SERVO_CHANNEL3:
			//
			// Enable pin PB5 for PWM0 M0PWM3
			//
			GPIOPinConfigure(GPIO_PB5_M0PWM3);
			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_1);

			break;
		case SERVO_CHANNEL4:
			//
			// Enable pin PE4 for PWM0 M0PWM4
			//
			GPIOPinConfigure(GPIO_PE4_M0PWM4);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_2);

			break;
		case SERVO_CHANNEL5:
			//
			// Enable pin PE5 for PWM0 M0PWM5
			//
			GPIOPinConfigure(GPIO_PE5_M0PWM5);
			GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_2);

			break;
		case SERVO_CHANNEL6:
			//
			// Enable pin PC4 for PWM0 M0PWM6
			//
			GPIOPinConfigure(GPIO_PC4_M0PWM6);
			GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_3);

			break;
		case SERVO_CHANNEL7:
			//
			// Enable pin PC5 for PWM0 M0PWM7
			//
			GPIOPinConfigure(GPIO_PC5_M0PWM7);
			GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);

			PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, ui32Load);

			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
			PWMGenEnable(PWM0_BASE, PWM_GEN_3);

			break;
		default:
			ASSERT((ui32Channel>15||ui32Channel<0));
		}
	} else if ((ui32Channel >= SERVO_CHANNEL8)
			&& (ui32Channel <= SERVO_CHANNEL15)) {
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

		switch (ui32Channel) {

		case SERVO_CHANNEL8:
			//
			// Enable pin PD0 for PWM1 M1PWM0
			//
			GPIOPinConfigure(GPIO_PD0_M1PWM0);
			GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_0);

			break;
		case SERVO_CHANNEL9:

			//
			// Enable pin PD1 for PWM1 M1PWM1
			//
			GPIOPinConfigure(GPIO_PD1_M1PWM1);
			GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_0);

			break;
		case SERVO_CHANNEL10:
			//
			// Enable pin PA6 for PWM1 M1PWM2
			//
			GPIOPinConfigure(GPIO_PA6_M1PWM2);
			GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_1);

			break;
		case SERVO_CHANNEL11:
			//
			// Enable pin PA7 for PWM1 M1PWM3
			//
			GPIOPinConfigure(GPIO_PA7_M1PWM3);
			GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_1);

			break;
		case SERVO_CHANNEL12:
			//
			// Enable pin PF0 for PWM1 M1PWM4
			// First open the lock and select the bits we want to modify in the GPIO commit register.
			//
			HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
			HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

			//
			// Now modify the configuration of the pins that we unlocked.
			//
			GPIOPinConfigure(GPIO_PF0_M1PWM4);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_2);

			break;
		case SERVO_CHANNEL13:
			//
			// Enable pin PF1 for PWM1 M1PWM5
			//
			GPIOPinConfigure(GPIO_PF1_M1PWM5);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_2);

			break;
		case SERVO_CHANNEL14:
			//
			// Enable pin PF2 for PWM1 M1PWM6
			//
			GPIOPinConfigure(GPIO_PF2_M1PWM6);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_3);

			break;
		case SERVO_CHANNEL15:
			//
			// Enable pin PF3 for PWM1 M1PWM7
			//
			GPIOPinConfigure(GPIO_PF3_M1PWM7);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);

			PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
			PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);

			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,
					ui8Adjust * ui32Load / 1000);
			PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
			PWMGenEnable(PWM1_BASE, PWM_GEN_3);

			break;
		default:
			ASSERT((ui32Channel>15||ui32Channel<0));
		}
	} else
		ASSERT((ui32Channel>15||ui32Channel<0));

}
/******************************************************************************************************
 * ******************************************************************************************************
 * ******************************************************************************************************
 * ******************************************************************************************************
 */

void Servo_HardWareSetAngle(uint32_t ui32Channel, int32_t i32Angle) {
	if (i32Angle == 200)
		ui8Adjust = 0;			//make the duty cycle ZERO
	else {
		if (i32Angle > SERVO_MAX_ANGLE)
			i32Angle = SERVO_MAX_ANGLE;
		if (i32Angle < SERVO_MIN_ANGLE)
			i32Angle = SERVO_MIN_ANGLE;
		ui8Adjust = map(i32Angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, 26, 138); //mapping the values which are tested on real servo-motor
	}
	switch (ui32Channel) {

	/*case SERVO_CHANNEL0:

	 PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
	 break;
	 case SERVO_CHANNEL1:

	 PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, ui8Adjust * ui32Load / 1000);
	 break;*/
	case SERVO_CHANNEL2:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL3:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL4:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL5:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL6:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL7:

		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL8:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL9:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL10:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL11:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL12:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL13:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL14:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, ui8Adjust * ui32Load / 1000);
		break;

	case SERVO_CHANNEL15:

		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, ui8Adjust * ui32Load / 1000);
		break;

	default:
		ASSERT((ui32Channel>15||ui32Channel<0));
	}

}

void Servo_SoftWare_SetAngle(uint32_t ui32Channel, int32_t i32AngleVal) {
	int32_t var; // temp variable to use it in the for loops
	int32_t tempIndex = 0;
	if (i32AngleVal == 200) {

		//disable timer of SW PWM timerA
		flagEnableInt = 0;
	} else {
		if (i32AngleVal > SERVO_MAX_ANGLE)
			i32AngleVal = SERVO_MAX_ANGLE;
		if (i32AngleVal < SERVO_MIN_ANGLE)
			i32AngleVal = SERVO_MIN_ANGLE;
		//enable timer of SW PWM timerA
		flagEnableInt = 1;
	}

	switch (ui32Channel) {
	case SERVO_CHANNEL16:
		for (var = SERVO_MIN_ANGLE; var < i32AngleVal; ++var) {
			anglesArr[tempIndex] |= GPIO_PIN_2; //Set the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		for (var = i32AngleVal; var < SERVO_MAX_ANGLE; ++var) {
			anglesArr[tempIndex] &= ~GPIO_PIN_2; //clear the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		break;
	case SERVO_CHANNEL17:
		for (var = SERVO_MIN_ANGLE; var < i32AngleVal; ++var) {
			anglesArr[tempIndex] |= GPIO_PIN_3; //Set the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		for (var = i32AngleVal; var < SERVO_MAX_ANGLE; ++var) {
			anglesArr[tempIndex] &= ~GPIO_PIN_3; //clear the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		break;
	case SERVO_CHANNEL18:
		for (var = SERVO_MIN_ANGLE; var < i32AngleVal; ++var) {
			anglesArr[tempIndex] |= GPIO_PIN_4; //Set the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		for (var = i32AngleVal; var < SERVO_MAX_ANGLE; ++var) {
			anglesArr[tempIndex] &= ~GPIO_PIN_4; //clear the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		break;
	case SERVO_CHANNEL19:
		for (var = SERVO_MIN_ANGLE; var < i32AngleVal; ++var) {
			anglesArr[tempIndex] |= GPIO_PIN_5; //Set the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		for (var = i32AngleVal; var < SERVO_MAX_ANGLE; ++var) {
			anglesArr[tempIndex] &= ~GPIO_PIN_5; //clear the bit corresponding to the channel in the each byte of array
			tempIndex++;
		}
		break;

	}

}

void Servo_SetAngle(uint32_t ui32Channel, int32_t i32Angle) {

	if (ui32Channel <= SERVO_CHANNEL15 && ui32Channel >= SERVO_CHANNEL2) {
		Servo_HardWareSetAngle(ui32Channel, i32Angle);
	} else if (ui32Channel == SERVO_CHANNEL0) {
		Servo_SoftWare_SetAngle(16, i32Angle);
	} else if (ui32Channel == SERVO_CHANNEL1) {
		Servo_SoftWare_SetAngle(17, i32Angle);
	} else if (ui32Channel == SERVO_CHANNEL16) {
		Servo_SoftWare_SetAngle(18, i32Angle);
	} else {
		ASSERT(ui32Channel>16);
	}

}
void Timer0IntHandlerForSWPWM(void) {
// Clear the timer interrupt
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	if (flagEnableInt) {

		//first time for 500 uSec
		if (thisTime == 0) {
			GPIOPinWrite(GPIO_PORTA_BASE,
			GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, 0xff);
			ui32Period = ((SysCtlClockGet() / 1000) / 2); // load in the timer 500u second for first time
			TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
			thisTime = 1; //increase thisTime to

		}
		//set timer interrupt each 12uSec
		else if (thisTime > 0 && thisTime <= 180) {

			GPIOPinWrite(GPIO_PORTA_BASE,
			GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5,
					anglesArr[thisTime - 1]);
			ui32Period = ((SysCtlClockGet() / 1000) / 161); // load in the timer 12u second for each time every 180 degree
			TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
			thisTime++;
		}
		//set timer interrupt after 17500uSec
		else if (thisTime == 181) {
			GPIOPinWrite(GPIO_PORTA_BASE,
			GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, 0);
			ui32Period = ((SysCtlClockGet() / 1000) / 2 * 31); // load in the timer 17500u second for last time
			TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
			thisTime = 0; //go to first time to begin next cycle

		}
	}
}
