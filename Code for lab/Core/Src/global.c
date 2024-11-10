/*
 * global.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */
#include "global.h"

int status = INIT;
int count[3] = {5, 2, 3};
int temp_count[3] = {5, 2, 3};
int led_count[2] = {5, 3};
const uint8_t MAX_LED = 4;
uint8_t index_led = 0;
int led_buffer[4] = {3, 2, 5, 5};

int light1Mode=0;
int light2Mode=2;

int light1Time=8;
int light2Time=3;
