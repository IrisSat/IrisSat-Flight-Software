//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ManitobaSat-1
//
// License:
//  Available under MIT license.
//
// Repository:
//  Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  Driver for communicating with the ADCS controller.
//
// History
// 2020-01-02 by Joseph Howarth
// - Created.
//
//  Based on information from https://github.com/aminya/ManitobaSat-ADCS-Software/issues/2 and standard spi implementation.
//  * This does not currently implement communication as specified in SIGMA operations manual *
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef ADCS_DRIVER_H_
#define ADCS_DRIVER_H_

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "spi.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define ADCS_MAGNETORQUER_DATA_SIZE  6
#define ADCS_GYRO_DATA_SIZE  48
#define ADCS_SUN_SENSOR_DATA_SIZE   156
#define ADCS_TELEMERTY_TOTAL_SIZE   (ADCS_MAGNETORQUER_DATA_SIZE + ADCS_GYRO_DATA_SIZE + ADCS_SUN_SENSOR_DATA_SIZE)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMERATIONS AND ENUMERATION TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef enum {

        ADCS_DRIVER_NO_ERROR,
        ADCS_ERROR_BAD_ACK

} AdcsDriverError_t;

typedef enum{
    MAGNETORQUER_X,
    MAGNETORQUER_Y,
    MAGNETORQUER_Z

}MagnetorquerID_t;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Configures the SPI and GPIO configurations for the ADCS driver. Should be called once, prior to calling other functions.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_init_driver();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to turn on to the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_power_on();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to turn off to the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_power_off();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to initiate telemetry to the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_initiate_telemetry();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to get full telemetry data from the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_read_telemetry(
    uint8_t * databuffer    //The buffer where the telemetry data will be stored. The buffer must be at least ADCS_TELEMETRY_TOTAL_SIZE bytes.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to turn on one of the magnetorquers to the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_turn_on_magnetorquer(
    MagnetorquerID_t id     //Specifies which magnetorquer will be turned on.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to turn off one of the magnetorquers to the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_turn_off_magnetorquer(
    MagnetorquerID_t id     //Specifies which magnetorquer will be turned on.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to reset the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_reset();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to get magnetorquer data from the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_read_magnetorquer_data(
    uint8_t * databuffer    //The buffer where the data will be stored. The buffer must be at least ADCS_MAGNETORQUER_DATA_SIZE bytes.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to get gyroscope data from the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_read_gyro_data(
    uint8_t * databuffer    //The buffer where the data will be stored. The buffer must be at least ADCS_GYRO_DATA_SIZE bytes.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends the command to get sun sensor data from the ADCS controller.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
AdcsDriverError_t adcs_read_sunsensor_data(
    uint8_t* databuffer    //The buffer where the data will be stored. The buffer must be at least ADCS_SUN_SENSOR_DATA_SIZE bytes.
);




#endif //ADCS_DRIVER_H_