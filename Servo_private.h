/*
 * Servo_private.h
 *
 *  Created on: May 8, 2015
 *      Author: Ahmed
 */

#ifndef UTILS_SERVO_PRIVATE_H_
#define UTILS_SERVO_PRIVATE_H_


#define SERVO_CHANNEL17 17
#define SERVO_CHANNEL18 18
#define SERVO_CHANNEL19 19

static void Servo_HardWareSetAngle(uint32_t ui32Channel, int32_t i32Angle);
static void Servo_SoftWare_SetAngle(uint32_t ui32Channel,int32_t i32AngleVal);


#endif /* UTILS_SERVO_PRIVATE_H_ */
