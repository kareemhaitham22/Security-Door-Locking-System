/* hn7ot fiha el 8bits mode we four bits mode with hash if/elif */

#ifndef LCD_H_
#define LCD_H_


#include "../Complex_Drivers/std_types.h"
#include "../Complex_Drivers/common_macros.h"
#include "../Complex_Drivers/micro_config.h"

#define DATA_BITS_MODE 8

#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
/*y3ny lo ana wa5ed upperpins mn el microcontroller h3ml define le UPPER_PORT_PINS lo l2 hasheel el define
 * ao h3ml undef*/
#endif

#define RS PD4
#define RW PD5
#define E PD6
#define LCD_CONTROL_PORT PORTD    //RS,RW,E
#define LCD_CONTROL_PORT_DIR DDRD

#define LCD_DATA_PORT PORTC		  //DATA/COMMAND
#define LCD_DATA_PORT_DIR DDRC

#define CLEAR_COMMAND 0X01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0X38
#define CURSOR_OFF 0X0C
#define CURSOR_ON 0X0E
#define SET_CURSOR_LOCATION 0X80

#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28

void LCD_sendCommand (uint8 command);
void LCD_displayCharacter (uint8 data);
void LCD_displayString (const char* str);
void LCD_init (void);
void LCD_clearScreen (void);
void LCD_displayStringRowColumn (uint8 row , uint8 col , const char* str);
void LCD_goToRowColumn (uint8 row , uint8 col);
void LCD_integerToString (int data);



#endif
