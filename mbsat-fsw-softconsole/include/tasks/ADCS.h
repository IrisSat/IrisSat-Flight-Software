#ifndef ADCS_H_
#define ADCS_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  ADCS tasks and functions
//
// History
// 2020-05-04 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

void vADCS_ControlTask(void * pvParameters);

uint8_t get_adcs_data();


#endif
