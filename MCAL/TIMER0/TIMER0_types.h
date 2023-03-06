/*
 * TIMER0_types.h
 *
 *  Created on: Feb 25, 2023
 *      Author: LENOVO
 */

#ifndef TIMER0_TIMER0_TYPES_H_
#define TIMER0_TIMER0_TYPES_H_

#include "STD_TYPES.h"



typedef enum
{
	NORMAL_MODE,
	CTC_MODE,
	FAST_PWM_MODE,
	PHASE_PWM_MODE
}TIMER0_MODE_TYPE;

typedef enum
{
	WG_NORMAL_PORT,
	WG_TOGGLE_OC0,
	WG_CLEAR_OC0,
	WG_SET_OC0,
	WG_INVERTING,
	WG_NON_INVERTING

}TIMER0_WG_TYPE;

typedef enum
{
	NO_CLK_SOURCE,
	CLK_1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024

}TIMER0_PRESCALLER_SELECT;

typedef enum
{
	COMPARE_MATCH,
	OVRER_FLOW

}TIMER0_INTERRUPT_TYPE;


#endif /* TIMER0_TIMER0_TYPES_H_*/