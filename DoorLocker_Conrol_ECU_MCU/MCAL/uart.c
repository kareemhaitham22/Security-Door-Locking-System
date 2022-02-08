#include "uart.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif


#define BAUD_PRESCALE ( ( ( F_CPU / (8UL * UART_BAUDRATE) ) ) - 1 )

static volatile void (* g_UART_receiveByteFunc_ptr)(void) = NULL;


ISR(USART_RXC_vect)
{
	if(g_UART_receiveByteFunc_ptr == NULL)
	{
		g_UART_receiveByteFunc_ptr();
	}
}


void UART_init(void) {

	/*UCSRA ONLY U2X FOR DOUBLE SPEED REST ARE FLAGS (POLLING & ERROR CHECKING)*/
	SET_BIT(UCSRA,1);
	/*bits 7,6,5 are for interrupts msh 3aiznhom dlo2ty , bits4,3=11 (transmotter and reciever enable)
	 * bit2=0 shan 3aiz normal 8 mode msh 9bits mode we bit1,0 mlnash d3wa beehom dol el ninth bit fl 9bit mode*/
	SET_BIT(UCSRB,4);
	SET_BIT(UCSRB,3);
	/*The URSEL must be one when writing the UCSRC (bit7 lazm tb2a be 1 3shan a3rf aktb fe control reg)*/
	/*bit6=0(asynchronous) , bit5,4=00(disable parity_check) bit3=0(1bit onle for stop)*/
	/*bit0 (mlnash da3wa beha dy bnstd5dmha fl synchronous bs) , bit2,1=11(8bit data)*/
	SET_BIT(UCSRC,7);
	SET_BIT(UCSRC,2);
	SET_BIT(UCSRC,1);
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	/*3shan 3aiz a7ot 12 bits 3la 2 registers 8 bits*/
	UBRRH = BAUD_PRESCALE >> 8 ;  //ya 7mar shift right msh left
	UBRRL = BAUD_PRESCALE ;

}

void UART_sendByte (const uint8 data) {

	/*ab3t el data 3l udr we astna l7d lma el transmission y5ls (bit6 : TXC)*/
	UDR = data ;
	while ( BIT_IS_CLEAR(UCSRA,6) );
	SET_BIT(UCSRA,6);	//ao3a tnsa t3ml clear ll flag b3d el polling

}

uint8 UART_recieveByte (void) {

	while ( BIT_IS_CLEAR(UCSRA,7) );
	//SET_BIT(UCSRA,7);   //cleared automatically after reading from udr
	return UDR;

}

void UART_sendString (const uint8 *str) {

	uint8 i = 0;
	while (str[i]!='\0') { UART_sendByte(str[i]);	i++; }

}

void UART_recieveString (uint8 *str) {

	uint8 i = 0;
	str[i] = UART_recieveByte();
	/*lazm a7ot 7aga fl string el 2ol 3shan a3rf a3ml check 3leha*/
	while (str[i]!='#') { i++; 	 str[i] = UART_recieveByte();		}
	str[i] =  '\0';
	/*# dy bn7toha zyada fl string ely bnb3tha (aw ay special character) 3shan el reciever y3rf a5r el string
	 * 3shan '/0' character mbytb3tsh
	 * we mtnsash t2fl el string bel character '/0' fl a5r */

}



