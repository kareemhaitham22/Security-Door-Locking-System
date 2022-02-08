#ifndef UART_H_
#define UART_H_


#include "../Complex_Drivers/std_types.h"
#include "../Complex_Drivers/micro_config.h"
#include "../Complex_Drivers/common_macros.h"


#define UART_BAUDRATE 9600UL

void UART_init(void);

void UART_sendByte (const uint8 data);

uint8 UART_recieveByte (void);

void UART_sendString (const uint8 *str);

void UART_recieveString (uint8 *str);


#endif
