#include "dc_motor.h"


void DC_MOTOR_init (const DcMotor_configType * Config_Ptr) {

	SET_BIT( DC_MOTOR_PORT_DIR , DC_MOTOR_port_in1 );
	SET_BIT( DC_MOTOR_PORT_DIR , DC_MOTOR_port_in2 );
	SET_BIT( DC_MOTOR_PORT_DIR , DC_MOTOR_port_EN1 );

	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
	//fast pwm at N=8(500hz)
	/*mtnsash tft7 el global interrupt fl main app*/	/*(sei())*/
	TCCR0 |= 0X68;	//fast pwm N=8(500hz)
	OCR0 = Config_Ptr->duty;

}


void DC_MOTOR_counterClockwise(void) {

	CLEAR_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in1 );
	SET_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in2 );

}

void DC_MOTOR_clockwise (void) {

	CLEAR_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in2 );
	SET_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in1 );

}

void DC_MOTOR_stop (void) {

	CLEAR_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in1 );
	CLEAR_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in2 );

}

void DC_MOTOR_reverseDirection(void) {

	TOGGLE_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in1 );
	TOGGLE_BIT( DC_MOTOR_PORT_OUT , DC_MOTOR_port_in2 );

}

void DC_MOTOR_setPwm (uint8 duty) {

	OCR0 = duty;

}



