/*
 * setimer.c
 *
 *  Created on: Sep 21, 2024
 *      Author: phong
 */

#include "main.h"
int timer_count=0;
int timer_flag=0;
void setTimer(int time){
	timer_count=time/10;
	timer_flag=0;
}
void timer_run(){
	if(timer_count>0){
		timer_count--;
		if(timer_count<=0){
			timer_flag=1;
		}
	}
}
