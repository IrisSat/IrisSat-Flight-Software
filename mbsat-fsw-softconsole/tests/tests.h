#ifndef ALL_TESTS_H
#define ALL_TESTS_H
//-------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  This file contains all the tests for the MBSat flight software.
//
// History
// 2020-04-21 by Joseph Howarth 
// - Created.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//      Unit tests
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//      Onboard Tests
//-------------------------------------------------------------------------------------------------

//FreeRTOS Test task for CoreSPI
void vTestSPI(void *pvParameters);

//FreeRTOS Test task for CAN
void vTestCANTx(void *pvParameters);
void vTestCANRx(void *pvParameters);


//FreeRTOS Test task for Watchdog.
void vTestWD(void *pvParameters);

//FreeRTOS Test task for RTC.
void vTestRTC(void *pvParameters);

//FreeRTOS Test task for MRAM
void vTestMRAM(void *pvParameters);

//FreeRTOS Test task for external flash memory.
void vTestFlash(void *pvParameters);

//FreeRTOS Test task for ADCS driver.
void vTestAdcsDriver(void * pvParameters);

//FreeRTOS Test task for file system.
void vTestFS(void * pvParams);


#endif
