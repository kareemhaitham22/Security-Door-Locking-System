#include "i2c.h"


void TWI_init(void){

	/*2o l7aga 3ndk equation ely btzbt el rate el anta 3aiz t3ml send/recieve bih
	 * anta m3ak el rate (known 3shan da el anta 3aizo) , we 3aiz t7sb el twbr
	 * (lazm twbr ttl3 positive) , m3ak 7agteen t2dr t3'yr feehom
	 * 1) microntroller freq(1-2-4-8MHZ)
	 * 2) prescaler (4 to the power(0-1-2-3))
	 * htgrb el 2ol 1 MHZ we t7ot el 2rb3a prescaler htl3 el twbr -ve
	 * htzod el freq l7d 8MHZ we m3 prescaler=0 (4 to the power 0)
	 * hytl3 el TWBR be 2 (positive integer)*/
	TWBR=0X02;
	TWSR=0X00;	/*prescaler*/

    /* Two Wire Bus address my address if any master device want to call me: 0x1
     * (used in case this MC is a slave device)
       General Call Recognition: Off */
	TWAR = 0b00000010; // my address = 0x01
	TWCR = (1<<TWEN); /* enable TWI */

}

void TWI_start(void){

    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  /*5alibalk dy ( = ) ms ( |= )*/

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));

}

void TWI_stop(void){
	/*zy el start bs TWSTO bdl TWSTA (stop bdl el start bit)*/
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data){
    TWDR = data;
    /*zy el start wl stop bs shyl el set bta3t start/stop*/
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void){
	/* Enable sending ACK after reading or receiving data TWEA=1 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while(BIT_IS_CLEAR(TWCR,TWINT));
    return TWDR;
}

uint8 TWI_readWithNACK(void) {
	/*zy ely bel ack bs mn 3'ir ma t3ml set lel TWEA(don't enable sending ack)*/
    TWCR = (1 << TWINT) | (1 << TWEN) ;
    while(BIT_IS_CLEAR(TWCR,TWINT));
    return TWDR;
}

uint8 TWI_getStatus(void){
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}



