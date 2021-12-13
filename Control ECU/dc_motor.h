#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define DC_MOTOR_PORT_OUT PORTB
#define DC_MOTOR_PORT_DIR DDRB

#define DC_MOTOR_port_in1 PB0
#define DC_MOTOR_port_in2 PB1
#define DC_MOTOR_port_EN1 PB3

typedef enum {
	T0_NO_CLOCK , T0_F_CPU_CLOCK , T0_F_CPU_8 , T0_F_CPU_64 , T0_F_CPU_256 , T0_F_CPU_1024 , T0_EXTERNAL_FALLING_EDGE , T0_EXTERNAL_RISING_EDGE
}Timer0_clock;

typedef struct {	Timer0_clock clock;		uint8 duty;	} DcMotor_configType;

void DC_MOTOR_init (const DcMotor_configType * Config_Ptr);

void DC_MOTOR_clockwise (void);

void DC_MOTOR_counterClockwise (void);

void DC_MOTOR_stop (void);

void DC_MOTOR_reverseDirection(void);

void DC_MOTOR_setPwm (uint8 duty);



#endif
