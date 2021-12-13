#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

typedef enum {	T1_NO_CLOCK , T1_F_CPU_CLOCK , T1_F_CPU_8 , T1_F_CPU_64 , T1_F_CPU_256 , T1_F_CPU_1024	}timer1_clock;

typedef enum { OC1A_DISCONNECTED , TOGGLE_OC1A , CLEAR_OC1A , SET_OC1A }TIMER1_OC1A;

typedef enum { DISCONNECTED_OC1A , TOGGLE_OC1A_OC1B_DISCONNECTED , NON_INVERTING , INVERTING }TIMER1_OC1A_pwm;

typedef struct {	timer1_clock clock;		short timer1_counter;	}timer1_configType_ovf;

typedef struct {	timer1_clock clock;		short timer1_counter;	TIMER1_OC1A oc1a;	}timer1_configType_comp;

typedef struct {	timer1_clock clock;		uint8 duty;		TIMER1_OC1A_pwm oc1a;} timer1_configType_pwm;

void timer1_init_ovf(const timer1_configType_ovf * Config_Ptr);

void timer1_init_compA(const timer1_configType_comp * Config_Ptr) ;

void timer1_init_compB(const timer1_configType_comp * Config_Ptr);

void tier1_init_pwmA (const timer1_configType_pwm * Config_Ptr);

void tier1_init_pwmB (const timer1_configType_pwm * Config_Ptr);

void timer1_deinit(void);

#endif /* TIMER1_H_ */
