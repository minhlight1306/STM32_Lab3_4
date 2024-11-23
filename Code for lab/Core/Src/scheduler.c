#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
unsigned char current_index_task = 0;

IWDG_HandleTypeDef hiwdg ;
static uint32_t counter_for_watchdog = 0;

void SCH_Init(void){
	current_index_task = 0;
	for(unsigned char i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
}
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD){
	while((SCH_tasks_G[current_index_task].pTask != 0) && (current_index_task < SCH_MAX_TASKS))
		current_index_task++;
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		return current_index_task;
	}
	Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
	return SCH_MAX_TASKS;
}
void SCH_Update(void){
	unsigned char Index ;
	for ( Index = 0; Index < SCH_MAX_TASKS; Index++){
		if( SCH_tasks_G[ Index ] . pTask) {
			if( SCH_tasks_G[ Index ] . Delay == 0){
				SCH_tasks_G[ Index ].RunMe += 1;
				if( SCH_tasks_G[ Index ].Period ){
					SCH_tasks_G[ Index ].Delay = SCH_tasks_G[ Index ].Period;
				}
			}
			else{
				SCH_tasks_G[ Index ].Delay -= 1;
			}
		}
	}
}
void SCH_Dispatch_Tasks(void){
	for(current_index_task = 0; current_index_task < SCH_MAX_TASKS; current_index_task++){
		if(SCH_tasks_G[current_index_task].RunMe > 0){
			SCH_tasks_G[current_index_task].RunMe--;
			(*SCH_tasks_G[current_index_task].pTask)();
			if(SCH_tasks_G[current_index_task].Period == 0){
				SCH_Delete_Task(current_index_task);
			}
		}
	}
}
unsigned char SCH_Delete_Task(const tByte TASK_INDEX){
	unsigned char Return_code ;
	if( SCH_tasks_G[TASK_INDEX].pTask == 0){
	Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;

		Return_code = RETURN_ERROR;
	}
	else{
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code ;
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

void MX_IWDG_Init( void ) {
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	hiwdg.Init.Reload = 4095;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
		Error_Handler();
	}
}
void Watchdog_Refresh( void ) {
	HAL_IWDG_Refresh(&hiwdg) ;
}
unsigned char Is_Watchdog_Reset (void) {
	if( counter_for_watchdog > 3) {
		return 1;
	}
	return 0;
}
void Watchdog_Counting( void ) {
	counter_for_watchdog++;
}

void Reset_Watchdog_Counting( void ) {
	counter_for_watchdog = 0;
}

