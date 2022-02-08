#include "timer1.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

/*
static void (*volatile g_T1CompareInterruptFunc_ptr)(void) = NULL;

static void (*volatile g_T1OverflowInterruptFunc_ptr)(void) = NULL;

void TIMER1_setCallBackCompareMode(void (*a_ptr)(void))
{
	g_T1CompareInterruptFunc_ptr = a_ptr;
}

void TIMER1_setCallBackOverflowMode(void (*a_ptr)(void))
{
	g_T1OverflowInterruptFunc_ptr = a_ptr;
}


ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;
	// the corresponding interrupt service routine function (IF EXIST) will be executed
	if(g_T1CompareInterruptFunc_ptr != NULL)
	{
		g_T1CompareInterruptFunc_ptr();
	}
}


ISR(TIMER1_OVF_vect)
{
	// the corresponding interrupt service routine function (IF EXIST) will be executed
	if(g_T1OverflowInterruptFunc_ptr != NULL)
	{
		g_T1OverflowInterruptFunc_ptr();
	}
}
*/

void timer1_init_ovf(const timer1_configType_ovf * Config_Ptr) {
	/*normal mode wgm13,12,11,10=0000*/
	sei();
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);  /*non pwm*/   				//NON-PWM MODE
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
	TCNT1 = Config_Ptr->timer1_counter;
	TIMSK |= (1<<2);	//TIMER1 OVF ENABLE
}

void timer1_init_compA(const timer1_configType_comp * Config_Ptr) {
	sei();							 //set I bit
	TCCR1A |= (1<<3);   				//NON-PWM MODE channel A
	TCCR1B |= (1<<3);				//CTC WGM12=1 - WGM10,WGM11,WGM13=0
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);    //011 N=64 CS12,CS11,CS10 BITS 2,1,0
	TCNT1 = 0;
	OCR1A = Config_Ptr->timer1_counter;					//combined with N=64 gives 1 sec exactly  (7000)

	if (Config_Ptr->oc1a == 0) {	TCCR1A &= ~(1<<7) &~(1<<6);	}
	else if (Config_Ptr->oc1a == 1) {	TCCR1A &= ~(1<<7);	TCCR1A |= (1<<6);	}
	else if (Config_Ptr->oc1a == 2) {	TCCR1A |= (1<<7);	TCCR1A &= ~(1<<6);	}
	else if (Config_Ptr->oc1a == 3) {	TCCR1A |= (1<<7);	TCCR1A |= (1<<6);	}
	else {}

	TIMSK |= (1<<4); 				 //timer1 compare A
}

void timer1_init_compB(const timer1_configType_comp * Config_Ptr) {
	sei();							 //set I bit
	TCCR1A |= (1<<2);   				//NON-PWM MODE channel B
	TCCR1B |= (1<<3);				//CTC WGM12=1 - WGM10,WGM11,WGM13=0
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);    //011 N=64 CS12,CS11,CS10 BITS 2,1,0
	TCNT1 = 0;
	OCR1A = Config_Ptr->timer1_counter;					//combined with N=64 gives 1 sec exactly  (7000)

	if (Config_Ptr->oc1a == 0) {	TCCR1A &= ~(1<<5) &~(1<<4);	}
	else if (Config_Ptr->oc1a == 1) {	TCCR1A &= ~(1<<5);	TCCR1A |= (1<<4);	}
	else if (Config_Ptr->oc1a == 2) {	TCCR1A |= (1<<5);	TCCR1A &= ~(1<<4);	}
	else if (Config_Ptr->oc1a == 3) {	TCCR1A |= (1<<5);	TCCR1A |= (1<<4);	}
	else {}

	TIMSK |= (1<<3); 				 //timer1 compare B
}

void tier1_init_pwmA (const timer1_configType_pwm * Config_Ptr) {
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
	//fast pwm at N=8(500hz)
	/*mtnsash tft7 el global interrupt fl main app*/	/*(sei())*/
	TCCR0 |= 0X68;	//fast pwm N=8(500hz)
	OCR0 = Config_Ptr->duty;

	if (Config_Ptr->oc1a == 0) {	TCCR1A &= ~(1<<7) &~(1<<6);	}
	else if (Config_Ptr->oc1a == 1) {	TCCR1A &= ~(1<<7);	TCCR1A |= (1<<6);	}
	else if (Config_Ptr->oc1a == 2) {	TCCR1A |= (1<<7);	TCCR1A &= ~(1<<6);	}
	else if (Config_Ptr->oc1a == 3) {	TCCR1A |= (1<<7);	TCCR1A |= (1<<6);	}
	else {}
}


void tier1_init_pwmB (const timer1_configType_pwm * Config_Ptr) {
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
	//fast pwm at N=8(500hz)
	/*mtnsash tft7 el global interrupt fl main app*/	/*(sei())*/
	TCCR0 |= 0X68;	//fast pwm N=8(500hz)
	OCR0 = Config_Ptr->duty;

	if (Config_Ptr->oc1a == 0) {	TCCR1A &= ~(1<<5) &~(1<<4);	}
	else if (Config_Ptr->oc1a == 1) {	TCCR1A &= ~(1<<5);	TCCR1A |= (1<<4);	}
	else if (Config_Ptr->oc1a == 2) {	TCCR1A |= (1<<5);	TCCR1A &= ~(1<<4);	}
	else if (Config_Ptr->oc1a == 3) {	TCCR1A |= (1<<5);	TCCR1A |= (1<<4);	}
	else {}
}


void timer1_deinit(void) {
	TCCR1B &= 0xF8;		/*no clock source (timer stopped)*/
}




