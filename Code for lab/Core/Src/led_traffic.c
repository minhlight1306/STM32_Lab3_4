/*
 * led_traffic.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */

#include "led_traffic.h"


void clearAllLed(){
	HAL_GPIO_WritePin(GPIOB, LED1_Pin | LED2_Pin | LED3_Pin
			| LED4_Pin | LED5_Pin | LED6_Pin, 0);
}

//automatic
//red on top and bottom is 1
//red on left and right is 2
void red_on(int index){
	switch (index){
	case 1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);

		break;
	case 2:
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1);
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0);
		HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);

		break;
	default:
		break;
	}
}
//
void green_on(int index){
	switch (index){
	case 1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0);
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1);
		HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
		break;
	default:
		break;
	}
}
//
void yellow_on(int index){
	switch (index){
	case 1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0);
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0);
		HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 1);
		break;
	default:
		break;
	}
}
void traffic_automatic(){
	switch(status){
	case AUTO_RED_GREEN://led_red is horizontal, led_green is vertical
		red_on(1);
		green_on(2);
		break;
	case AUTO_RED_YELLOW:
		red_on(1);
		yellow_on(2);

		break;
	case AUTO_GREEN_RED:
		green_on(1);
		red_on(2);

		break;
	case AUTO_YELLOW_RED:
		yellow_on(1);
		red_on(2);

		break;
	default:
		break;
	}
}

