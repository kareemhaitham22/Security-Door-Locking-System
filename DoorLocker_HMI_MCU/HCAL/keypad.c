#include "keypad.h"

#if (N_COL==3)

static uint8 keyPad_4x3_adjustKeyNumber(uint8 button_number) {
	switch (button_number) {
		case 10 : return '*'; break;
		case 11 : return 0; ; break;
		case 12 : return '#'; break;
		default : return button_number;
	}
}


#elif (N_COL==4)

static uint8 keyPad_4x4_adjustKeyNumber(uint8 button_number) {
	switch(button_number)
	{
		case 1: return 7; break;
		case 2: return 8; break;
		case 3: return 9; break;
		case 4: return '%'; break;
		case 5: return 4; break;
		case 6: return 5; break;
		case 7: return 6; break;
		case 8: return '*'; /* ASCII Code of '*' */ break;
		case 9: return 1; break;
		case 10: return 2; break;
		case 11: return 3; break;
		case 12: return '-'; /* ASCII Code of '-' */ break;
		case 13: return 13;  /* ASCII of Enter */ break;
		case 14: return 0; break;
		case 15: return '='; /* ASCII Code of '=' */ break;
		case 16: return '+'; /* ASCII Code of '+' */ break;
		default: return button_number;
	}
}

#endif

uint8 keypad_getPressedKey(void) {
	uint8 col;
	uint8 row;
	while (1) {
		for (col=0;col<N_COL;col++) {
			/* 2ol arb3a bits fe porta (0-3) ma7gozeen ll row fa ana h3ml shift by col mn 2ol bit4 */
			KEYPAD_PORT_DIR = (0b00010000<<col); //only one output pin and rest are inputs
			KEYPAD_PORT_OUT = (~(0b00010000<<col));	/* zy el fo2iha bs zowad complement */
			//activate internal pull up to all except the output pin (3shan mt7otsh fiha high) (lazm tb2a ground)
			//3shan el configuration lma el key ydas yfdl mazboot
			for (row=0;row<N_ROW;row++) {
				if ( BIT_IS_CLEAR(KEYPAD_PORT_IN,row) ) {
					#if (N_COL==3)
						return keyPad_4x3_adjustKeyNumber( (row*N_COL)+col+1 );
					#elif (N_COL==4)
						return keyPad_4x4_adjustKeyNumber( (row*N_COL)+col+1 );
					#endif
				}
			}

		}
	}
}



