/*
 * setimer.c
 *
 *  Created on: Sep 21, 2024
 *      Author: phong
 */

#include "main.h"
int timer_count=0;

void setTimer(int time){
	timer_count=time/10;
}
void timer_run(){
	if(timer_count>0){
		timer_count--;
		}
	}

