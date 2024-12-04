/*
 * global.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */
#include "global.h"

int status = AUTO_RED_GREEN;
int count[3] = {5, 2, 3};
int temp_count[3] = {5, 2, 3};
int led_count[2] = {5, 3};
const uint8_t MAX_LED = 4;
uint8_t index_led = 0;
int led_buffer[4] = {3, 2, 5, 5};

void blinky(){
	  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
}
void blinkyled1(){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
void blinkyled2(){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
void blinkyled3(){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}
void blinkyled4(){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
