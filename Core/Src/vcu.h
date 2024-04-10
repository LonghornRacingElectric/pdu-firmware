#ifndef PDU_FIRMWARE_VCU_H
#define PDU_FIRMWARE_VCU_H

#include "spi_adc.h"

void vcu_init();
void vcu_periodic(AdcVoltages& adcVoltages);

#endif //PDU_FIRMWARE_VCU_H
