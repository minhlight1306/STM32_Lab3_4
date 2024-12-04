#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t is_add[SCH_MAX_TASKS] = {0};
uint32_t numTask = 0;

void SCH_Init(void){ // checked
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete(i);
		is_add[i] = 0;
	}
	numTask = 0;
}
// modifing
void  SCH_Add_Task(void (*pFunction)(), uint32_t DELAY,
						uint32_t PERIOD, uint32_t TaskID){
	if(numTask >= SCH_MAX_TASKS) return;

    uint32_t total = 0;
    uint32_t i = 0;
    uint32_t newDelay = DELAY;

    // Kiểm tra vị trí để thêm tác vụ
    for(; i < numTask; i++){
        if(SCH_tasks_G[i].pTask){
        	total += SCH_tasks_G[i].Delay;
        	if(total > newDelay){
        		newDelay -= (total - SCH_tasks_G[i].Delay);
        		break;
        	}
        }
    }

    if (i == numTask) {
            newDelay -= total;
        }

    for(int j = numTask; j > i; j--){
        SCH_tasks_G[j] = SCH_tasks_G[j - 1];
    }
    SCH_tasks_G[i + 1].Delay -= newDelay;
    SCH_tasks_G[i].pTask = pFunction;
    SCH_tasks_G[i].Delay = newDelay;
    SCH_tasks_G[i].Period = PERIOD;
    SCH_tasks_G[i].RunMe = 0;
    SCH_tasks_G[i].TaskID = TaskID;

    numTask++;
    is_add[numTask - 1] = 1;
}
void SCH_Update(void){ //checked
	if(is_add[0]){
		if(SCH_tasks_G[0].Delay > TICK){
			SCH_tasks_G[0].Delay -= TICK;
		}
		else {
			SCH_tasks_G[0].Delay = 0;
			SCH_tasks_G[0].RunMe = 1;
		}
	}
}
void SCH_Dispatch_Tasks(void){ //checked
	if(numTask == 0) return;
		while(SCH_tasks_G[0].RunMe == 1 || SCH_tasks_G[0].Delay == 0){

			(*SCH_tasks_G[0].pTask)();

			sTasks tempTask = SCH_tasks_G[0];
			SCH_Delete_Task(SCH_tasks_G[0].TaskID);
			if(tempTask.Period != 0){
				SCH_Add_Task(tempTask.pTask, tempTask.Period,
					         tempTask.Period, tempTask.TaskID);
			}
		}
}
void SCH_Delete(uint32_t TASK_INDEX){
	SCH_tasks_G[TASK_INDEX].pTask = 0 ;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].TaskID = 0;
}
uint8_t SCH_Delete_Task(uint32_t id){ //checked
	if(numTask == 0){
		return 0;
	}
	uint8_t success = 0;
	uint32_t i;
	for(i = 0; i < numTask; i++){
		if(id == SCH_tasks_G[i].TaskID){

			break;
		}
	}
	uint32_t delay = SCH_tasks_G[i].Delay;
	for (uint32_t j = i; j < numTask - 1; j++){
		SCH_tasks_G[j] = SCH_tasks_G[j + 1];
		SCH_tasks_G[j].Delay = SCH_tasks_G[j].Delay + delay;
	}
	success = 1;
	is_add[numTask] = 0;
	numTask--;
	return success;
}

