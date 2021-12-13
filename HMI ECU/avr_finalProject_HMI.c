#include "keypad.h"
#include "lcd.h"
#include "uart.h"

#define  BUZZER 0x01
#define  DC_MOTOR_CW 0x02
#define  DC_MOTOR_CCW 0x03
#define  NONE 0x04

int main (void) {

	uint8 wrong_pass_count = 0;
	uint8 key;
	uint8 pass1 = '7';
	uint8 pass2 = '7';
	uint8 pass3 = '7';
	uint8 pass4 = '7';
	uint8 pass5 = '7';
	uint8 pass1_in = '7';
	uint8 pass2_in = '7';
	uint8 pass3_in = '7';
	uint8 pass4_in = '7';
	uint8 pass5_in = '7';
	LCD_init();
	UART_init();

	LCD_displayString("new pass");  /*first pass to be set*/
	LCD_goToRowColumn(1,0);
	for (uint8 i=0 ; i<5 ;i++) {
		key = keypad_getPressedKey();
		switch (i) {
			case 0 : pass1 = key; break;
			case 1 : pass2 = key; break;
			case 2 : pass3 = key; break;
			case 3 : pass4 = key; break;
			case 4 : pass5 = key; break;
			default : break;
		}
		LCD_displayCharacter('*');
		_delay_ms(500);
	}

	while (1) {

		wrong_pass_count = 0;
		do {
		if (wrong_pass_count == 3) { wrong_pass_count=0; 	UART_sendByte(BUZZER); }
		wrong_pass_count++;
		LCD_clearScreen();
		LCD_displayString("enter pass");
		LCD_goToRowColumn(1,0);
		for (uint8 i=0 ; i<5 ;i++) {
			key = keypad_getPressedKey();
			switch (i) {
				case 0 : pass1_in = key; break;
				case 1 : pass2_in = key; break;
				case 2 : pass3_in = key; break;
				case 3 : pass4_in = key; break;
				case 4 : pass5_in = key; break;
				default : break;
				}
			LCD_displayCharacter('*');
			_delay_ms(500);
			}
		}
		while (!(pass1==pass1_in && pass2==pass2_in && pass3==pass3_in && pass4==pass4_in && pass5==pass5_in));

		do {
		LCD_clearScreen();
		LCD_displayString("+ : open door");
		LCD_goToRowColumn(1,0);
		LCD_displayString("- : change pass");
		key = keypad_getPressedKey();  } while (!(key == '+' || key == '-'));

		_delay_ms(500);
		if (key =='+') {
			wrong_pass_count = 0;
			do {
			if (wrong_pass_count == 3) { wrong_pass_count=0; 	UART_sendByte(BUZZER); }
			wrong_pass_count++;
			LCD_clearScreen();
			LCD_displayString("enter pass");
			LCD_goToRowColumn(1,0);
			for (uint8 i=0 ; i<5 ;i++) {
				key = keypad_getPressedKey();
				switch (i) {
					case 0 : pass1_in = key; break;
					case 1 : pass2_in = key; break;
					case 2 : pass3_in = key; break;
					case 3 : pass4_in = key; break;
					case 4 : pass5_in = key; break;
					default : break;
					}
				LCD_displayCharacter('*');
				_delay_ms(500);
				}
			}
			while (!(pass1==pass1_in && pass2==pass2_in && pass3==pass3_in && pass4==pass4_in && pass5==pass5_in));
			LCD_clearScreen();
			UART_sendByte(DC_MOTOR_CW);
			LCD_displayString("OPENING DOOR");
			while ( UART_recieveByte() != NONE);
			UART_sendByte(DC_MOTOR_CCW);
			LCD_clearScreen();
			LCD_displayString("CLOSING DOOR");
			while ( UART_recieveByte() != NONE);

		}
		else if (key == '-') {
			wrong_pass_count = 0;
			do {
			if (wrong_pass_count == 3) { wrong_pass_count=0; 	UART_sendByte(BUZZER);}
			wrong_pass_count++;
			LCD_clearScreen();
			LCD_displayString("enter pass");
			LCD_goToRowColumn(1,0);
			for (uint8 i=0 ; i<5 ;i++) {
				key = keypad_getPressedKey();
				switch (i) {
					case 0 : pass1_in = key; break;
					case 1 : pass2_in = key; break;
					case 2 : pass3_in = key; break;
					case 3 : pass4_in = key; break;
					case 4 : pass5_in = key; break;
					default : break;
					}
				LCD_displayCharacter('*');
				_delay_ms(500);
				}
			}
			while (!(pass1==pass1_in && pass2==pass2_in && pass3==pass3_in && pass4==pass4_in && pass5==pass5_in));
			LCD_clearScreen();
			LCD_displayString("new pass");  /*pass to be set*/
			LCD_goToRowColumn(1,0);
			for (uint8 i=0 ; i<5 ;i++) {
				key = keypad_getPressedKey();
				switch (i) {
					case 0 : pass1 = key; break;
					case 1 : pass2 = key; break;
					case 2 : pass3 = key; break;
					case 3 : pass4 = key; break;
					case 4 : pass5 = key; break;
					default : break;
				}
				LCD_displayCharacter('*');
				_delay_ms(500);

			}

		}

	}
}
