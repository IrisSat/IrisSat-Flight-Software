//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Driver for communicating with the analog to digital converter IC on Iris CDH.
//
// History
// 2021-03-24 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "drivers/device/adc/adc_common.h"
#include "drivers/device/adc/AD7928.h"
#include "math.h"

double getBoardTemp(){

    AD7928_Measurement_t m;

    readADC(&m);

    double voltage = ((double)m.value/AD7928_RESOLUTION - ADC_OFFSET)/ADC_GAIN;

    double resistance = ((30000-20000*voltage)/(30000+20000*voltage) )* 10000;

    double temp = 1/(9.02e-4 + 2.49e-4*log(resistance)+2.01e-7*pow(log(resistance),3)) - 273.15;

    return temp;
}
