#ifndef I2C_H_
#define I2C_H_


#include "../Complex_Drivers/micro_config.h"
#include "../Complex_Drivers/std_types.h"
#include "../Complex_Drivers/common_macros.h"

/* I2C Status Bits in the TWSR Register (most significant 5 bits) */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
/*dool 3shan for example external eeprom lma tsd5dm el i2c*/

/*TWI = two wire interface*/

void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);



#endif
