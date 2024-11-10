/*
 * fsm_manual.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */

#include "fsm_manual.h"

void ifButtonLongPressed(){
		status = AUTO_RED_GREEN;
		clearAllLed();
		while(temp_count[0] != temp_count[1] + temp_count[2]){
			if(temp_count[1] > temp_count[0] || temp_count[2] > temp_count[0]){
				temp_count[1] = 3;
				temp_count[0] = temp_count[1] + temp_count[2];
			}
			else if(temp_count[1] > temp_count[2]){
				temp_count[1] = 3;
				temp_count[2] = temp_count[0] - temp_count[1];
			}
			else {
				temp_count[2] = temp_count[0] - temp_count[1];
			}
		}
		count[0] = temp_count[0];
		count[1] = temp_count[1];
		count[2] = temp_count[2];
		led_count[0] = count[0];
		led_count[1] = count[2];
		//updateBuffer(led_count[1], led_count[0]);
		setTimer(0, count[2] * 1000);
}
void fsm_manual_run(){
	switch(status){
		case MODE_2:
			scan7led();
			if(isTimerExpired(2)){
				HAL_GPIO_TogglePin(GPIOB, LED1_Pin | LED4_Pin);
				setTimer(2, 500);
			}
			if(isButtonPressed(1)){
				status = MODE_3;
				clearAllLed();
				updateBuffer(MODE_3 - 11, temp_count[1]);
				setTimer(1, 500);
				setTimer(2, 500);
				//temp_count[0] = count[0];
			}
			else if(isButtonPressed(2)){
				temp_count[0]++;
				if(temp_count[0] > 99)
					temp_count[0] = 1;
				updateBuffer(MODE_2 - 11, temp_count[0]);
			}
			else if(isButtonPressed(3)){
				count[0] = temp_count[0];
			}
			else if(isButtonLongPressed(1))
				ifButtonLongPressed();
			break;
		case MODE_3:
			scan7led();
			if(isTimerExpired(2)){
				HAL_GPIO_TogglePin(GPIOB, LED3_Pin | LED6_Pin);
				setTimer(2, 500);
			}
			if(isButtonPressed(1)){
				status = MODE_4;
				clearAllLed();
				updateBuffer(MODE_4 - 11, temp_count[2]);
				setTimer(1, 500);
				setTimer(2, 500);
				//temp_count[1] = count[1];
			}
			else if(isButtonPressed(2)){
				temp_count[1]++;
				if(temp_count[1] > 99)
					temp_count[1] = 1;
				updateBuffer(MODE_3 - 11, temp_count[1]);
			}
			else if(isButtonPressed(3)){
				count[1] = temp_count[1];
			}
			else if(isButtonLongPressed(1))
				ifButtonLongPressed();
			break;
		case MODE_4:
			scan7led();
			if(isTimerExpired(2)){
				HAL_GPIO_TogglePin(GPIOB, LED2_Pin | LED5_Pin);
				setTimer(2, 500);
			}
			if(isButtonPressed(1) || isButtonLongPressed(1)){
				ifButtonLongPressed();
			}
			else if(isButtonPressed(2)){
				temp_count[2]++;
				if(temp_count[2] > 99)
					temp_count[2] = 1;
				updateBuffer(MODE_4 - 11, temp_count[2]);
			}
			else if(isButtonPressed(3)){
				count[2] = temp_count[2];
			}
			break;
		default:
			break;
	}
}



