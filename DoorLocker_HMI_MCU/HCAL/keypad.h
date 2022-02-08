#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../Complex_Drivers/std_types.h"
#include "../Complex_Drivers/micro_config.h"
#include "../Complex_Drivers/common_macros.h"

#define N_COL 4
#define N_ROW 4

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_DIR DDRA

uint8 keypad_getPressedKey(void);

#endif
