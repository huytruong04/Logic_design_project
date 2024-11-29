/*
 * timer.h
 *
 *  Created on: Nov 20, 2024
 *      Author: pc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
#define TIMER_CYCLE 10
extern int timer0_counter;
extern int timer0_flag;
extern int timer1_counter;
extern int timer1_flag;
void setTimer0(int duration);
void setTimer1(int duration);
void timerRun();

#endif /* INC_TIMER_H_ */
