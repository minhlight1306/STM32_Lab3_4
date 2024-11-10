/*
 * button.h
 *
 *  Created on: Nov 10, 2024
 *      Author: PC
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_OF_BUTTON 3

extern int button_flag[NUM_OF_BUTTON];
extern int TimeOutForKeyPress[NUM_OF_BUTTON];
extern int button_pressed[NUM_OF_BUTTON];
extern int button_long_pressed[NUM_OF_BUTTON];
extern int button_flag[NUM_OF_BUTTON];

void getKeyInput();
int isButtonPressed(int index);
int isButtonLongPressed(int index);

#endif /* INC_BUTTON_H_ */
