/*
 * global.h
 *
 *  Created on: 28 thg 10, 2024
 *      Author: PC
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT		0
#define AUTO_RED_GREEN	1
#define AUTO_RED_YELLOW	2
#define AUTO_GREEN_RED	3
#define AUTO_YELLOW_RED	4

#define MODE_1 12
#define MODE_2	13
#define MODE_3 14
#define MODE_4 15


#include "led_traffic.h"
#include "software_timer.h"
#include "button.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "main.h"
#include "scan7led.h"

extern int status;
extern int count[3];
extern int temp_count[3];
extern int led_count[2];

extern const uint8_t MAX_LED;
extern uint8_t index_led;
extern int led_buffer[4];
extern int light1Mode;
extern int light2Mode;

extern int light1Time;
extern int light2Time;

#endif /* INC_GLOBAL_H_ */
