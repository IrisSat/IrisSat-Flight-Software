#ifndef OPERATION_H_
#define OPERATION_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  Main task and operations related functions.
//
// History
// 2020-04-10 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum{
    COMMISIONING_MODE,
    IDLE_MODE,
    SUN_POINTING_MODE,
    SCIENCE_MODE,
    LOW_POWER_MODE
} OperationsState_t;

void vOperations_MainTask(void * pvParameters);

void updateOperationsState();

void changeOperationsState(OperationsState_t new_state);

#endif
