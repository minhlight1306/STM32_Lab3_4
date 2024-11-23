#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void){
	current_index_task = 0;
	for(unsigned char i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}


}
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
	}
}
void SCH_Update(void){
	for(unsigned char i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}
		else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}
void SCH_Dispatch_Tasks(void){
	for(unsigned char i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete_Task(i);
			}
		}
	}
}
uint8_t SCH_Delete_Task(uint32_t taskID){
	unsigned char Return_code ;
	if( SCH_tasks_G[taskID ].pTask == 0){
//	Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;

		Return_code = RETURN_ERROR;
	}
	else{
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[taskID ] . pTask = 0x0000 ;
	SCH_tasks_G[taskID ] . Delay = 0;
	SCH_tasks_G[taskID ] . Period = 0;
	SCH_tasks_G[taskID ] .RunMe = 0;
	return Return_code ;
}

