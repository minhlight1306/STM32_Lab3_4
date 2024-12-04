//#include "scheduling.h"
//
//// Timestamps
//uint32_t timestamps;
//
//// array of tasks
//sTask SCH_tasks_G[SCH_MAX_TASKS];
//uint8_t visited[SCH_MAX_TASKS] = {0};
//uint32_t numTask;
//
//// Initial the scheduler
//void SCH_Init()
//{
//    for (int i = 0; i < SCH_MAX_TASKS; i++)
//    {
//        visited[i] = 0;
//    }
//    numTask = 0;
//    timestamps = 0;
//}
//
//// Increase 1 time unit
//void SCH_Update()
//{
//    timestamps = timestamps + 1;
//    if (visited[0] != 0)
//    {
//    	if(SCH_tasks_G[0].Delay > TICK)
//    		SCH_tasks_G[0].Delay = SCH_tasks_G[0].Delay - TICK;
//    	else SCH_tasks_G[0].Delay = 0;
//        if (SCH_tasks_G[0].Delay == 0)
//        {
//            SCH_tasks_G[0].RunMe = 1;
//        }
//    }
//}
//
//// Add new task into array of task
//uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
//{
//    // Check array is full
//    if (numTask == SCH_MAX_TASKS)
//        return 0;
//
//    // Add new task
//    uint8_t success = 0;
//    uint32_t curTime = 0;
//    uint32_t task;
//    for (task = 0; task < numTask; task++)
//    {
//        curTime = curTime + SCH_tasks_G[task].Delay;
//
//        if (curTime > DELAY)
//        {
//            DELAY = DELAY - (curTime - SCH_tasks_G[task].Delay);
//            success = 1;
//            break;
//        }
//    }
//
//
//    if (!success)
//    {
//        DELAY = DELAY - curTime;
//        success = 1;
//    }
//
//    // Shift right the task 1 unit
//    sTask curTask = SCH_tasks_G[task];
//    curTask.Delay = curTask.Delay - DELAY;
//    for (uint32_t i = task; i < numTask; i++)
//    {
//        sTask tempTask = SCH_tasks_G[i + 1];
//        SCH_tasks_G[i + 1] = curTask;
//        SCH_tasks_G[i + 1].TaskID = SCH_tasks_G[i + 1].TaskID + 1; // update TaskID
//        curTask = tempTask;
//    }
//
//    // Add new task with new Delay into the list
//    SCH_tasks_G[task].pTask = pFunction;
//    SCH_tasks_G[task].Delay = DELAY;
//    SCH_tasks_G[task].Period = PERIOD;
//    SCH_tasks_G[task].RunMe = 0;
//    SCH_tasks_G[task].TaskID = task;
//
//    // Update status of the array of task
//    numTask = numTask + 1;
//    success = 1;
//    visited[numTask - 1] = 1;
//
//    return success;
//}
//
//// Delete task from array of task
//uint8_t SCH_Delete(uint32_t TaskID)
//{
//    uint8_t success = 0;
//    // Check TaskID is correct, array of task is empty
//    if (TaskID >= numTask || numTask == 0)
//        return 0;
//
//    // Calculate Delay for all tasks after that and shift left them
//    uint32_t Delay = SCH_tasks_G[TaskID].Delay;
//    for (uint32_t task = TaskID; task < numTask - 1; task++)
//    {
//        SCH_tasks_G[task] = SCH_tasks_G[task + 1];
//        SCH_tasks_G[task].TaskID = SCH_tasks_G[task].TaskID - 1;
//        SCH_tasks_G[task].Delay = SCH_tasks_G[task].Delay + Delay;
//    }
//    success = 1;
//    numTask = numTask - 1;
//    visited[numTask] = 0;
//
//    return success;
//}
//
//// Run the task in the array of task
//void SCH_Dispatch_Tasks()
//{
//	if (numTask == 0)
//		return;
//    while (SCH_tasks_G[0].RunMe == 1 || SCH_tasks_G[0].Delay == 0)
//    {
//        // Run the task
//        (*SCH_tasks_G[0].pTask)();
//        sTask tempTask = SCH_tasks_G[0];
//        SCH_Delete(SCH_tasks_G[0].TaskID);
//        if (tempTask.Period != 0)
//        {
//            // Add this task into array again
//            SCH_Add_Task(tempTask.pTask, tempTask.Period, tempTask.Period);
//        }
//    }
//}
//
//// Get timestamps
//uint32_t get_time()
//{
//	return timestamps;
//}
//
//
