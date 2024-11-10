/*
 * button.c
 *
 *  Created on: Nov 10, 2024
 *      Author: PC
 */

#include "button.h"

int KeyReg0[NUM_OF_BUTTON] = {NORMAL_STATE};
int KeyReg1[NUM_OF_BUTTON] = {NORMAL_STATE};
int KeyReg2[NUM_OF_BUTTON] = {NORMAL_STATE};
int KeyReg3[NUM_OF_BUTTON] = {NORMAL_STATE};
int Key[NUM_OF_BUTTON] = {NORMAL_STATE};

int TimeOutForKeyPress[NUM_OF_BUTTON] =  {500};
int button_pressed[NUM_OF_BUTTON] = {0};
int button_long_pressed[NUM_OF_BUTTON] = {0};
int button_flag[NUM_OF_BUTTON] = {0};

void readKey(){
	Key[1] = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);//mode
	Key[2] = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);//setting time
	Key[3] = HAL_GPIO_ReadPin(Button3_GPIO_Port, Button3_Pin);//enter
}
int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index){
	if(button_long_pressed[index] == 1){
		button_long_pressed[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	//TODO
	//HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	button_flag[index] = 1;
}

void getKeyInput(){
	readKey();
	for(int i = 0; i < NUM_OF_BUTTON; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		KeyReg0[i] = Key[i];

		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];

				if (KeyReg3[i] == PRESSED_STATE){
				TimeOutForKeyPress[i] = 500;
				subKeyProcess(i);
				}
			}
			else{
				TimeOutForKeyPress[i] --;
				if (TimeOutForKeyPress[i] == 0){
					TimeOutForKeyPress[i] = 500;
					if (KeyReg3[i] == PRESSED_STATE){
						subKeyProcess(i);
					}
				}
			}
		}
	}
}
