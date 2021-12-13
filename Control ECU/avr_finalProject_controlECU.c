#include "dc_motor.h"
#include "external_eeprom.h"
#include "uart.h"
#include "timer1.h"

#define  BUZZER 0x01
#define  DC_MOTOR_CW 0x02
#define  DC_MOTOR_CCW 0x03
#define  NONE 0x04
/*#define recieved_address 0x0300
#define working_address 0x0301*/

/*don't forget to initialize  timer and modules and i2c eeprom*/
uint8 working = 0;
uint8 sec = 0;
uint8 recieved = 0;


ISR (TIMER1_COMPA_vect) {
	TCNT1 = 0;
	sec++;
	if (sec == 15 && (working == DC_MOTOR_CW || working == DC_MOTOR_CCW)) {
			sec = 0;
			DC_MOTOR_stop();
			timer1_deinit();
			working = NONE;
			/*EEPROM_writeByte(working_address, NONE);
			EEPROM_readByte(working_address, &working);*/
			UART_sendByte (working);
		}
	else if (sec == 60 && working == BUZZER) {
			sec = 0;
			CLEAR_BIT(PORTA,0);    /*buzzer off*/
			timer1_deinit();
			working = NONE;
			/*EEPROM_writeByte(working_address, NONE);
			EEPROM_readByte(working_address, &working);*/
			UART_sendByte (working);
	  }
	else {}
}


int main (void) {

	timer1_configType_comp y = { T1_F_CPU_64 , 7000 , OC1A_DISCONNECTED };
	DcMotor_configType x = {T0_F_CPU_CLOCK , 128};
	UART_init();
	DC_MOTOR_init(&x);
	DC_MOTOR_stop();
	EEPROM_init();
	SET_BIT(DDRA,0);
	CLEAR_BIT(PORTA,0);   /*initially buzzer off */

	while (1) {

		recieved = UART_recieveByte();
		/*EEPROM_writeByte(recieved_address, UART_recieveByte());
		EEPROM_readByte(recieved_address, &recieved);*/
		if (recieved == BUZZER) {
			SET_BIT(PORTA,0);    /*buzzer on*/
			working = BUZZER;
			/*EEPROM_writeByte(working_address, BUZZER);
			EEPROM_readByte(working_address, &working);*/
			timer1_init_compA(&y);
		}
		else if (recieved == DC_MOTOR_CW) {
			DC_MOTOR_clockwise();
			working = DC_MOTOR_CW;
			/*EEPROM_writeByte(working_address, DC_MOTOR_CW);
			EEPROM_readByte(working_address, &working);*/
			timer1_init_compA(&y);
		}
		else if (recieved == DC_MOTOR_CCW) {
			DC_MOTOR_counterClockwise();
			working = DC_MOTOR_CCW;
			/*EEPROM_writeByte(working_address, DC_MOTOR_CCW);
			EEPROM_readByte(working_address, &working);*/
			timer1_init_compA(&y);
		}
		else {}

	}
}
