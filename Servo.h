/*
 * Servo.h
 *
 *  Created on: Apr 29, 2015
 *      Author: Ahmed
 */

#ifndef SAMURAIBOT_UTILS_SERVO_H_
#define SAMURAIBOT_UTILS_SERVO_H_

#define PWM_FREQUENCY 55
#define SERVO_MAX_ANGLE	180
#define SERVO_MIN_ANGLE	0


#define SERVO_CHANNEL0 0
#define SERVO_CHANNEL1 1
#define SERVO_CHANNEL2 2
#define SERVO_CHANNEL3 3
#define SERVO_CHANNEL4 4
#define SERVO_CHANNEL5 5
#define SERVO_CHANNEL6 6
#define SERVO_CHANNEL7 7
#define SERVO_CHANNEL8 8
#define SERVO_CHANNEL9 9
#define SERVO_CHANNEL10 10
#define SERVO_CHANNEL11 11
#define SERVO_CHANNEL12 12
#define SERVO_CHANNEL13 13
#define SERVO_CHANNEL14 14
#define SERVO_CHANNEL15 15
#define SERVO_CHANNEL16 16


#define R_0	SERVO_CHANNEL0
#define R_1 SERVO_CHANNEL12
#define R_2 SERVO_CHANNEL10
#define R_3 SERVO_CHANNEL8
#define R_4 SERVO_CHANNEL6
#define R_5 SERVO_CHANNEL4
#define R_6	SERVO_CHANNEL2
#define R_7 SERVO_CHANNEL14

#define L_0 SERVO_CHANNEL1
#define L_1 SERVO_CHANNEL13
#define L_2 SERVO_CHANNEL11
#define L_3 SERVO_CHANNEL9
#define L_4 SERVO_CHANNEL7
#define L_5 SERVO_CHANNEL5
#define L_6 SERVO_CHANNEL3
#define L_7 SERVO_CHANNEL15

#define HEAD SERVO_CHANNEL16

#define OFFSET_R_0 90
#define OFFSET_R_1 165
#define OFFSET_R_2 90
#define OFFSET_R_3 150
#define OFFSET_R_4 60
#define OFFSET_R_5 70
#define OFFSET_R_6 110
#define OFFSET_R_7 130

#define OFFSET_L_0 90
#define OFFSET_L_1 25
#define OFFSET_L_2 90
#define OFFSET_L_3 30
#define OFFSET_L_4 127
#define OFFSET_L_5 110
#define OFFSET_L_6 90
#define OFFSET_L_7 115

#define OFFSET_HEAD 115



extern void Servo_Init(void);
extern void Servo_AttachChannel(uint32_t ui32Channel, int32_t i32InitialAngle);
extern void Servo_SetAngle(uint32_t ui32Channel, int32_t i32Angle);
extern void Timer0IntHandlerForSWPWM(void);



#endif /* SAMURAIBOT_UTILS_SERVO_H_ */
