/*
 * scheduler.h
 *
 *  Created on: 22 thg 11, 2024
 *      Author: PC
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include "global.h"

typedef struct{
	void (*pTask) (void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
}sTasks;

#define SCH_MAX_TASKS 10
#define NO_TASK_ID 0
sTasks SCH_tasks_G[SCH_MAX_TASKS];

// khoi tao mot mang task
void SCH_Init(void);

// them 1 task vao mang
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY,
						uint32_t PERIOD, uint8_t TaskID);

// cap nhat trang thai co het thoi gian delay chua, neu co RunMe++
void SCH_Update(void);

// kiem tra task da thuc thi chua
void SCH_Dispatch_Tasks(void);

// xoa task tai vi tri index
void SCH_Delete_Task(uint8_t TASK_INDEX);
void SCH_Delete(uint8_t TASK_INDEX);


#endif /* INC_SCHEDULER_H_ */
