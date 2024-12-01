#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
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

	if(numTask == 0){
		SCH_tasks_G[0].pTask = pFunction;
	    SCH_tasks_G[0].Delay = DELAY;
	    SCH_tasks_G[0].Period = PERIOD;
	    SCH_tasks_G[0].RunMe = 0;
	    SCH_tasks_G[0].TaskID = TaskID;
	    numTask++;
	    return;
	}
	uint8_t idAdd = 0;
	uint32_t remaining_delay = DELAY;
	uint32_t total = 0;

	for(int i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask){
			total += SCH_tasks_G[i].Delay;

			if (total > remaining_delay) {
				idAdd = i;
				remaining_delay -= (total - SCH_tasks_G[i].Delay);
				break;
			}
		}
		else{
			idAdd = i;
			break;
		}
	}

	for(int i = numTask; i > idAdd; i--){
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
	}

	SCH_tasks_G[idAdd].pTask = pFunction;
    SCH_tasks_G[idAdd].Delay = remaining_delay;
    SCH_tasks_G[idAdd].Period = PERIOD;
    SCH_tasks_G[idAdd].RunMe = 0;
    SCH_tasks_G[idAdd].TaskID = TaskID;

    if (idAdd + 1 < SCH_MAX_TASKS && SCH_tasks_G[idAdd + 1].pTask) {

            SCH_tasks_G[idAdd + 1].Delay -= remaining_delay; // Chỉ trừ remaining_delay
        }

    numTask++;
}
void SCH_Update(void){
	if(numTask == 0) return;
	if(SCH_tasks_G[0].pTask) {
		if(SCH_tasks_G[0].Delay == 0){
			SCH_tasks_G[0].RunMe++;
		}
		if(SCH_tasks_G[0].Delay > 0){
			if(SCH_tasks_G[0].Delay > TICK){
				SCH_tasks_G[0].Delay -= TICK;
			}
			else SCH_tasks_G[0].Delay = 0;
		}
	}
}
void SCH_Dispatch_Tasks(void){
	if(numTask == 0) return;
	if(SCH_tasks_G[0].pTask){
		if(SCH_tasks_G[0].RunMe > 0){
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();

			if(SCH_tasks_G[0].Period){
				sTasks tempTask = SCH_tasks_G[0];
				SCH_Delete_Task(SCH_tasks_G[0].TaskID);
				SCH_Add_Task(tempTask.pTask, tempTask.Period,
					         tempTask.Period, tempTask.TaskID);
			}
//			SCH_Delete_Task(SCH_tasks_G[0].TaskID);
		}
	}
}
void SCH_Delete(uint32_t TASK_INDEX){
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].TaskID = 0;
}
void SCH_Delete_Task(uint32_t id){
	if(numTask == 0){
		return;
	}
	uint32_t i = 0;
	uint8_t success = 0;
	for(; i < numTask; i++){
		if(id == SCH_tasks_G[i].TaskID){
			success = 1;
			if(SCH_tasks_G[i + 1].pTask){
			SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;

			}
			break;
		}
	}
	for (; i < numTask - 1; i++){
		SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
		SCH_tasks_G[i].TaskID = SCH_tasks_G[i + 1].TaskID;

	}
	if(success){
		SCH_Delete(numTask - 1);
		numTask--;
	}
}

