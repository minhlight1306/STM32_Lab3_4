/*
 * fsm_automatic.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */

#include "fsm_automatic.h"
#include "global.h"

void counter(){
	if(isTimerExpired(2)){
		led_count[0]--;
		led_count[1]--;
		setTimer(2, 1000);
	}
}
void fsm_automatic_run(){
	switch(status){
		case INIT:
			status = AUTO_RED_GREEN;
			setTimer(0, 3000);//time automatic
			break;
		case AUTO_RED_GREEN:
			traffic_automatic();
			updateBuffer(led_count[1], led_count[0]);
			scan7led();
			counter();
			if(isButtonPressed(1)){
				status = MODE_2;
				clearAllLed();
				updateBuffer(MODE_2 - 11, count[0]);
				setTimer(1, 500);
				setTimer(2, 500);
			}
			if(isTimerExpired(0)){
				status = AUTO_RED_YELLOW;
				led_count[1] = count[1];
				setTimer(0, count[1] * 1000);
			}
			break;
		case AUTO_RED_YELLOW:
			traffic_automatic();
			updateBuffer(led_count[1], led_count[0]);
			scan7led();
			counter();
			if(isButtonPressed(1)){
				status = MODE_2;
				clearAllLed();
				updateBuffer(MODE_2 - 11, count[0]);
				setTimer(1, 500);
				setTimer(2, 500);
			}
			if(isTimerExpired(0)){
				status = AUTO_GREEN_RED;
				led_count[0] = count[2];
				led_count[1] = count[0];
				setTimer(0, count[2] * 1000);
			}
			break;
		case AUTO_GREEN_RED:
			traffic_automatic();
			updateBuffer(led_count[1], led_count[0]);
			scan7led();
			counter();
			if(isButtonPressed(1)){
				status = MODE_2;
				clearAllLed();
				updateBuffer(MODE_2 - 11, count[0]);
				setTimer(1, 500);
				setTimer(2, 500);
			}
			if(isTimerExpired(0)){
				status = AUTO_YELLOW_RED;
				led_count[0] = count[1];
				setTimer(0, count[1] * 1000);
			}
			break;
		case AUTO_YELLOW_RED:
			traffic_automatic();
			updateBuffer(led_count[1], led_count[0]);
			scan7led();
			counter();
			if(isButtonPressed(1)){
				status = MODE_2;
				clearAllLed();
				updateBuffer(MODE_2 - 11, count[0]);
				setTimer(1, 500);
				setTimer(2, 500);
			}
			if(isTimerExpired(0)){
				status = AUTO_RED_GREEN;
				led_count[0] = count[0];
				led_count[1] = count[2];
				setTimer(0, count[2] * 1000);
			}
			break;
		default:
			break;
		  }
}



