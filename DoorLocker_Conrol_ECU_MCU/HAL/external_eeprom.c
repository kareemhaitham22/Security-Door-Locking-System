#include "../MCAL/i2c.h"
/*3shan m7tag el hash defines ely 3mltaha fe 2ol el h file bta3 el i2c 3shan a3rf status bta3tha(TWI_getStatus()*/
#include "external_eeprom.h"

/*el eeprom hya ely btt7km fl i2c e3ny ana fel app maleesh da3wa bl i2c
 * app -> eeprom , eeprom -> i2c  (app,mcal,hcal)*/

void EEPROM_init(void) {
	TWI_init();
}

uint8 EEPROM_writeByte (uint16 addr , uint8 data) {

	TWI_start();
	if (TWI_getStatus() != TW_START) { return ERROR; }

	/*ab3t 2ol tlata bit fl 10bit address m3 R/W*/
    TWI_write((uint8)(0xA0 | ((addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK) { return ERROR; }

    /*ab3t b2et el address (typecasting 3shan ta5od a5r 8 bit bs
     *  (you have already taken the first 3 bits of the address))*/
    TWI_write((uint8)(addr));
     if (TWI_getStatus() != TW_MT_DATA_ACK) { return ERROR; }

     TWI_write(data);
     if (TWI_getStatus() != TW_MT_DATA_ACK) { return ERROR; }

     TWI_stop();
     return SUCCESS;

}

uint8 EEPROM_readByte (uint16 addr , uint8 *data) {

	/*read lazm ab3t el R/W be zero el 2ol 3shan a3rf a write el address b3d keda repeat start we
	 * ab3t el address tany bs m3 R/W=1 (3shan t3ml read b2a)*/

	TWI_start();
	if (TWI_getStatus() != TW_START) { return ERROR; }

	/*ab3t 2ol tlata bit fl 10bit address m3 R/W=0*/
    TWI_write((uint8)(0xA0 | ((addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK) { return ERROR; }

    /*ab3t b2et el address (typecasting 3shan ta5od a5r 8 bit bs
     *  (you have already taken the first 3 bits of the address))*/
    TWI_write((uint8)(addr));
     if (TWI_getStatus() != TW_MT_DATA_ACK) { return ERROR; }


     /* Send the Repeated Start Bit */
     TWI_start();
     if (TWI_getStatus() != TW_REP_START)  { return ERROR; }

     /* R/W=1 (Read) ( |1 )*/
     TWI_write((uint8)((0xA0) | ((addr & 0x0700)>>7) | 1));
     if (TWI_getStatus() != TW_MT_SLA_R_ACK)  {  return ERROR; }

     *data = TWI_readWithNACK();
     if (TWI_getStatus() != TW_MR_DATA_NACK)  {  return ERROR; }

     TWI_stop();
     return SUCCESS;

}


