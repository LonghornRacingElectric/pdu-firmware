#ifndef PDU_FIRMWARE_VCU_H
#define PDU_FIRMWARE_VCU_H

#include "spi_adc.h"

typedef struct VCUStatus {
    float brakeLightPercent;
    struct pduCooling {
        float radiatorFanRPM;
        float pumpPercent;
    } pduCooling;
    uint8_t buzzerType;
} VCUStatus ;

void vcu_init();
void vcu_periodic(AdcVoltages& adcVoltages, VCUStatus& stat);


#endif //PDU_FIRMWARE_VCU_H
