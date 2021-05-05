//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Driver for communicating with the AD7928 ADC.
//
// History
// 2021-03-24 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef ADC_AD7928_H_
#define ADC_AD7928_H_

#include <stdint.h>

#define AD7928_WRITE_BIT    (1<<15)
#define AD7928_SEQ_BIT      (1<<14)
#define AD7928_ADD2         (1<<12)
#define AD7928_ADD1         (1<<11)
#define AD7928_ADD0         (1<<10)
#define AD7928_PM1          (1<<9)
#define AD7928_PM0          (1<<8)
#define AD7928_SHADOW       (1<<7)
#define AD7928_RANGE        (1<<5)
#define AD7928_CODING       (1<<4)

#define AD7928_RESOLUTION   4096

typedef struct{

    uint8_t channel;
    uint16_t value;

}AD7928_Measurement_t;

void readADC(AD7928_Measurement_t* measurement);

void initADC();

#endif /* ADC_AD7928_H_ */
