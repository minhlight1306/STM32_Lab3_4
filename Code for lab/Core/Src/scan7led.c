/*
 * scan7led.c
 *
 *  Created on: Oct 28, 2024
 *      Author: PC
 */
#include "scan7led.h"

void updateBuffer(int time1, int time2){
	led_buffer[0]=time1/10;
	led_buffer[1]=time1%10;
	led_buffer[2]=time2/10;
	led_buffer[3]=time2%10;
}
const uint8_t segDigits[10] = {
    0b01000000, // 0: Seg0, Seg1, Seg2, Seg3, Seg4, Seg5
    0b01111001, // 1: Seg1, Seg2
    0b00100100, // 2: Seg0, Seg1, Seg3, Seg4, Seg6
    0b00110000, // 3: Seg0, Seg1, Seg2, Seg3, Seg6
    0b00011001, // 4: Seg1, Seg2, Seg5, Seg6
    0b00010010, // 5: Seg0, Seg2, Seg3, Seg5, Seg6
    0b00000010, // 6: Seg0, Seg2, Seg3, Seg4, Seg5, Seg6
    0b01111000, // 7: Seg0, Seg1, Seg2
    0b00000000, // 8: Seg0, Seg1, Seg2, Seg3, Seg4, Seg5, Seg6
    0b00010000  // 9: Seg0, Seg1, Seg2, Seg3, Seg5, Seg6
};
// ham thuc hien led 7 doan
void displayDigit(uint8_t digit) {
    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, (segDigits[digit] & 0x01) ? 1 : 0);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, (segDigits[digit] & 0x02) ? 1 : 0);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, (segDigits[digit] & 0x04) ? 1 : 0);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, (segDigits[digit] & 0x08) ? 1 : 0);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, (segDigits[digit] & 0x10) ? 1 : 0);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, (segDigits[digit] & 0x20) ? 1 : 0);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, (segDigits[digit] & 0x40) ? 1 : 0);
}
void update7SEG(int index) {
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, 1);
	switch (index) {
		case 0:
			//Display the first 7SEG with led_buffer [0]
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0);
			displayDigit(led_buffer[0]);
			break;
		case 1:
			//Display the second 7SEG with led_buffer [1]
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
			displayDigit(led_buffer[1]);
			break;
		case 2:
			//Display the third 7SEG with led_buffer [2]
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
			displayDigit(led_buffer[2]);
			break;
		case 3:
			//Display the forth 7SEG with led_buffer [3]
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0);
			displayDigit(led_buffer[3]);
			break;
		default:
			break;
	}

	index_led++;
	if(index_led >= MAX_LED){
		index_led = 0;
	}
}
void scan7led(){
	if(isTimerExpired(1)){
		update7SEG(index_led);
		setTimer(1, 250);
	}
}
