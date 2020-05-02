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

#include "adcs_driver.h"
#include "board_definitions.h"

#define ADCS_ACK_PREFIX 0x01

typedef enum{

    ADCS_POWER_OFF  = 0x0800,
    ADCS_POWER_ON = 0x0900,
    ADSC_INITIATE_TELEMETRY = 0x1000,
    ADCS_READ_TELEMETRY = 0x1100,
    ADCS_TURN_ON_MAGNETORQUER_1 = 0x2A00,
    ADCS_TURN_ON_MAGNETORQUER_2 = 0x2B00,
    ADCS_TURN_ON_MAGNETORQUER_3 = 0x2C00,
    ADCS_TURN_OFF_MAGNETORQUER_1 = 0x3A00,
    ADCS_TURN_OFF_MAGNETORQUER_2 = 0x3B00,
    ADCS_TURN_OFF_MAGNETORQUER_3 = 0x3C00,
    ADCS_RESET = 0xAA00,
    ADCS_READ_MAGNETORQUERS = 0x1A,
    ADCS_READ_GYRO = 0x1B,
    ADCS_READ_SUN_SENSOR = 0x1C

} AdcsCmdBytes_t;


AdcsDriverError_t adcs_init_driver(){

	AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

	//spi_configure_slave(ADCS_SPI_CORE, ADCS_SLAVE_CORE, SPI_MODE_MASTER, SPI_MODE3, PCLK_DIV_32);
	spi_configure_gpio_ss(ADCS_SS_PIN);

}

AdcsDriverError_t adcs_power_on(){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2] = {(ADCS_POWER_ON>>8)&0xFF,ADCS_POWER_ON&0xFF};
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX || (ack[1]<<8+ack[2]) != ADCS_POWER_ON){

        status = ADCS_ERROR_BAD_ACK;

    }

    return status;
}

AdcsDriverError_t adcs_power_off(){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2] = {(ADCS_POWER_OFF>>8)&0xFF,ADCS_POWER_OFF&0xFF};
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX || (ack[1]<<8+ack[2]) != ADCS_POWER_OFF){

        status = ADCS_ERROR_BAD_ACK;
        
    }

    return status;

}

AdcsDriverError_t adcs_initiate_telemetry(){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2] = {(ADSC_INITIATE_TELEMETRY>>8)&0xFF,ADSC_INITIATE_TELEMETRY&0xFF};
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX || (ack[1]<<8+ack[2]) != ADSC_INITIATE_TELEMETRY){

        status = ADCS_ERROR_BAD_ACK;
        
    }

    return status;

}

AdcsDriverError_t adcs_read_telemetry(uint8_t * databuffer){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2] = {(ADCS_READ_TELEMETRY>>8)&0xFF,ADCS_READ_TELEMETRY&0xFF};
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX || (ack[1]<<8+ack[2]) != ADCS_READ_TELEMETRY){

        status = ADCS_ERROR_BAD_ACK; 
    }
    else{

        spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,NULL,0,databuffer,ADCS_TELEMETRY_TOTAL_SIZE);
    }

    return status;


}

AdcsDriverError_t adcs_turn_on_magnetorquer(MagnetorquerID_t id, uint8_t pwm_duty_cycle){


    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2];
     
    switch(id){

        case MAGNETORQUER_X:

            cmd[0] = (ADCS_TURN_ON_MAGNETORQUER_1 >> 8) & 0xFF;
            cmd[1] = pwm_duty_cycle;
        break;

        case MAGNETORQUER_Y:

            cmd[0] = (ADCS_TURN_ON_MAGNETORQUER_2 >> 8) & 0xFF;
            cmd[1] = pwm_duty_cycle;
        break;

        case MAGNETORQUER_Z:

            cmd[0] = (ADCS_TURN_ON_MAGNETORQUER_3 >> 8) & 0xFF;
            cmd[1] = pwm_duty_cycle;
        break;
        
        default:
            status = ADCS_ERROR_BAD_ID;
            return status;
    }
    
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if( (ack[0] != ADCS_ACK_PREFIX) || (ack[1] != cmd[1]) || (ack[2] != ack[2]) ){

        status = ADCS_ERROR_BAD_ACK;
        
    }

    return status;

}

AdcsDriverError_t adcs_turn_off_magnetorquer(MagnetorquerID_t id){

AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2];
     
    switch(id){

        case MAGNETORQUER_X:

            cmd[0] = (ADCS_TURN_OFF_MAGNETORQUER_1 >> 8) & 0xFF;
            cmd[1] = ADCS_TURN_OFF_MAGNETORQUER_1 & 0xFF;
        break;

        case MAGNETORQUER_Y:

            cmd[0] = (ADCS_TURN_OFF_MAGNETORQUER_2 >> 8) & 0xFF;
            cmd[1] = ADCS_TURN_OFF_MAGNETORQUER_2 & 0xFF;
        break;

        case MAGNETORQUER_Z:

            cmd[0] = (ADCS_TURN_OFF_MAGNETORQUER_3 >> 8) & 0xFF;
            cmd[1] = ADCS_TURN_OFF_MAGNETORQUER_3 & 0xFF;
        break;
        
        default:
            status = ADCS_ERROR_BAD_ID;
            return status;
    }
    
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if( (ack[0] != ADCS_ACK_PREFIX) || (ack[1] != cmd[1]) || (ack[2] != ack[2]) ){

        status = ADCS_ERROR_BAD_ACK;
        
    }

    return status;

}

AdcsDriverError_t adcs_reset(){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd[2] = {(ADCS_RESET>>8)&0xFF,ADCS_RESET&0xFF};
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX || (ack[1]<<8+ack[2]) != ADCS_RESET){

        status = ADCS_ERROR_BAD_ACK;
        
    }

    return status;

}

AdcsDriverError_t adcs_read_magnetorquer_data(uint8_t * databuffer){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd= ADCS_READ_MAGNETORQUERS;
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,&cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX ||(ack[1] != ADCS_READ_MAGNETORQUERS)){

        status = ADCS_ERROR_BAD_ACK; 
    }
    else{

        spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,NULL,0,databuffer,ADCS_MAGNETORQUER_DATA_SIZE);
    }

    return status;

}

AdcsDriverError_t adcs_read_gyro_data(uint8_t * databuffer){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd= ADCS_READ_GYRO;
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,&cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX ||(ack[1] != ADCS_READ_GYRO)){

        status = ADCS_ERROR_BAD_ACK; 
    }
    else{

        spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,NULL,0,databuffer,ADCS_GYRO_DATA_SIZE);
    }

    return status;

}

AdcsDriverError_t adcs_read_sunsensor_data(uint8_t* databuffer){

    AdcsDriverError_t status = ADCS_DRIVER_NO_ERROR;

    uint8_t cmd= ADCS_READ_SUN_SENSOR;
    uint8_t ack [1+sizeof(cmd)] = {0}; // The acknowledge consists of 0x01 followed by the command echoed back.

    spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,&cmd,sizeof(cmd),ack,sizeof(ack));

    if(ack[0] != ADCS_ACK_PREFIX ||(ack[1] != ADCS_READ_SUN_SENSOR)){

        status = ADCS_ERROR_BAD_ACK; 
    }
    else{

        spi_transaction_block_read_without_toggle(ADCS_SPI_CORE,ADCS_SLAVE_CORE,ADCS_SS_PIN,NULL,0,databuffer,ADCS_SUN_SENSOR_DATA_SIZE);
    }

    return status;

}
