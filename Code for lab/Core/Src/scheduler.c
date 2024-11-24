#include "scheduler.h"

//sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t numTask = 0;

void SCH_Init(void){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete(i);
	}
	numTask = 0;
}
// modifing
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY,
						uint32_t PERIOD, uint8_t TaskID){
	if(numTask >= SCH_MAX_TASKS) return;
	uint8_t idAdd = 0;
	uint32_t remaining_delay = DELAY;

	for(int i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask){
			if(SCH_tasks_G[i].Delay <= remaining_delay){
				remaining_delay -= SCH_tasks_G[i].Delay;
			}
			else{
				idAdd = i;
				break;
			}
		}
		else{
			idAdd = i;
			break;
		}
	}

	if(idAdd >= SCH_MAX_TASKS) return;
	for(int i = SCH_MAX_TASKS - 1; i > idAdd; i--){
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
	}

	SCH_tasks_G[idAdd].pTask = pFunction;
    SCH_tasks_G[idAdd].Delay = remaining_delay;
    SCH_tasks_G[idAdd].Period = PERIOD;
    SCH_tasks_G[idAdd].RunMe = 0;
    SCH_tasks_G[idAdd].TaskID = TaskID;

    if (idAdd + 1 < SCH_MAX_TASKS && SCH_tasks_G[idAdd + 1].pTask) {
    	SCH_tasks_G[idAdd + 1].Delay -= remaining_delay;
    }
    numTask++;
}
void SCH_Update(void){
	if(numTask == 0) return;

	if(SCH_tasks_G[0].pTask) {
		if(SCH_tasks_G[0].Delay == 0){
			SCH_tasks_G[0].RunMe++;
			if(SCH_tasks_G[0].Period){
				SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
			}
		}
		else if(SCH_tasks_G[0].Delay > TICK){
			SCH_tasks_G[0].Delay -= TICK;
		}
		else SCH_tasks_G[0].Delay = 0;
	}
}
void SCH_Dispatch_Tasks(void){
	if(numTask == 0) return;

	if(SCH_tasks_G[0].pTask){
		if(SCH_tasks_G[0].RunMe > 0){
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();
			if(SCH_tasks_G[0].Period != 0){
				SCH_Add_Task(SCH_tasks_G[0].pTask, SCH_tasks_G[0].Period,
					         SCH_tasks_G[0].Period, SCH_tasks_G[0].TaskID);
			}
			SCH_Delete_Task(0);
		}
	}
}
void SCH_Delete(uint8_t TASK_INDEX){
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].TaskID = 0;
}
void SCH_Delete_Task(uint8_t TASK_INDEX){
	if(TASK_INDEX >= SCH_MAX_TASKS || numTask == 0){
		return;
	}
	uint8_t idFinal = 0;
	SCH_Delete(TASK_INDEX);
	for (uint8_t i = TASK_INDEX; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
		SCH_tasks_G[i].TaskID = SCH_tasks_G[i + 1].TaskID;
		if (SCH_tasks_G[i].pTask == 0x0000){
			idFinal = i;
			break;
		}
	}
	SCH_Delete(idFinal);
	numTask--;
}
void SCH_Go_To_Sleep(){

}
void SCH_Report_Status ( void ) {
# ifdef SCH_REPORT_ERRORS

	if( Error_code_G != Last_error_code_G ) {
		Error_port = 255 − Error_code_G ;
		Last_error_code_G = Error_code_G ;
		if( Error_code_G != 0) {
			Error_tick_count_G = 60000;
		}
		else {
			Error_tick_count_G = 0;
		}
	}
	else {
		if( Error_tick_count_G != 0) {
			if(--Error_tick_count_G == 0) {
				Error_code_G = 0; // Reset error code
			}
		}
	}
#endif
}


