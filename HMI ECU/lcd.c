#include "lcd.h"


void LCD_init (void) {

	LCD_CONTROL_PORT_DIR |= (1<<E) | (1<<RW) | (1<<RS);

	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0XF0;	/*upper ports in micro controller*/
		#else
			LCD_DATA_PORT_DIR |= 0X0F;	/*lower ports in micro controller*/
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0XFF;
		LCD_sendCommand( TWO_LINE_LCD_EIGHT_BIT_MODE );
	#endif

	LCD_sendCommand( CURSOR_OFF );
	LCD_sendCommand ( CLEAR_COMMAND );

}


void LCD_sendCommand (uint8 command) {

	CLEAR_BIT( LCD_CONTROL_PORT , RS );		/*instruction mode*/
	CLEAR_BIT( LCD_CONTROL_PORT , RW );		/*write*/
	_delay_ms(1);
	SET_BIT( LCD_CONTROL_PORT , E );
	_delay_ms(1);
	#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
		#endif
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
		SET_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
	#endif

}


void LCD_displayCharacter (uint8 data) {

	SET_BIT( LCD_CONTROL_PORT , RS );		/*instruction mode*/
	CLEAR_BIT( LCD_CONTROL_PORT , RW );		/*write*/
	_delay_ms(1);
	SET_BIT( LCD_CONTROL_PORT , E );
	_delay_ms(1);
	#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
		#endif
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
		SET_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data;
		_delay_ms(1);
		CLEAR_BIT( LCD_CONTROL_PORT , E );
		_delay_ms(1);
	#endif

}


void LCD_displayString (const char* str) {

	uint8 i=0;
	while (str[i] != '\0') {
		LCD_displayCharacter (str[i]);
		i++;
	}

}


void LCD_goToRowColumn (uint8 row , uint8 col) {

	uint8 address;
	switch (row) {
		case 0: address = col;	break;
		case 1: address = col + 0x40;	break;
		case 2: address = col + 0x10;	break;
		case 3: address = col + 0x50;	break;
	}
	LCD_sendCommand ( address | SET_CURSOR_LOCATION );

}


void LCD_displayStringRowColumn (uint8 row , uint8 col , const char* str) {

	LCD_goToRowColumn( row , col );
	LCD_displayString ( str );

}


void LCD_integerToString (int data) {

	char buff[16];
	itoa( data , buff  , 10 );	 /*10 for decimal integer*/
	LCD_displayString ( buff );

}


void LCD_clearScreen (void) {
	LCD_sendCommand(CLEAR_COMMAND);
}




