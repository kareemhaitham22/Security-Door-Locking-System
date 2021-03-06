#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


#include "../Complex_Drivers/micro_config.h"
#include "../Complex_Drivers/std_types.h"
#include "../Complex_Drivers/common_macros.h"

#define ERROR 0
#define SUCCESS 1

void EEPROM_init(void);
uint8 EEPROM_writeByte (uint16 addr , uint8 data);
/*fl read el data btb2a pointer to unsigned char msh unsigned char*/
uint8 EEPROM_readByte (uint16 addr , uint8 *data);


#endif
