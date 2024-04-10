#include "spi_adc.h"

#include "main.h"
#include "spi.h"

static uint8_t buffer[32];
static uint8_t dummyData[2] = {0xFF, 0xFF};

static void spiAdc_csLow() {
    HAL_GPIO_WritePin(SPI_CS_ADC_GPIO_Port, SPI_CS_ADC_Pin, GPIO_PIN_RESET);
}

static void spiAdc_csHigh() {
    HAL_GPIO_WritePin(SPI_CS_ADC_GPIO_Port, SPI_CS_ADC_Pin, GPIO_PIN_SET);
}

static void spiAdc_write(uint8_t *bufferAddr, uint16_t size) {
    spiAdc_csLow();
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi2, bufferAddr, size, SPI_TIMEOUT);
    if(status != HAL_OK)
        Error_Handler();
    spiAdc_csHigh();
}

static void spiAdc_read(uint8_t *bufferAddr, uint16_t size) {
    spiAdc_csLow();
    HAL_StatusTypeDef status = HAL_SPI_Receive(&hspi2, bufferAddr, size, SPI_TIMEOUT);
    if(status != HAL_OK)
        Error_Handler();
    spiAdc_csHigh();
}

static void spiAdc_writeDummyData() {
    spiAdc_csLow();
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi2, dummyData, 1, SPI_TIMEOUT);
    if(status != HAL_OK)
        Error_Handler();
    spiAdc_csHigh();
}

static float spiAdc_convert(uint8_t channel) {
    buffer[0] = 0b10000011 | (channel << 2);
    buffer[1] = 0b00010000;

    spiAdc_write(&buffer[0], 1);
    spiAdc_read(&buffer[channel*2], 1);

    uint16_t x = ((uint16_t)(buffer[channel*2]) << 8) & 0xFF00 | (uint16_t)(buffer[channel*2+1]);
    return static_cast<float>(x) / 4095.0f * 3.3f;
}

void spiAdc_init() {
    HAL_Delay(200);
    spiAdc_writeDummyData();
    spiAdc_writeDummyData();
}

void spiAdc_getVoltages(AdcVoltages& adcVoltages) {
    adcVoltages.radiatorFansCurrent = spiAdc_convert(0);
    adcVoltages.glvCurrent = spiAdc_convert(1);
    adcVoltages.brakeLightCurrent = spiAdc_convert(2);
    adcVoltages.batteryFansCurrent = spiAdc_convert(3);
    adcVoltages.accessoryCurrent = spiAdc_convert(4);
    adcVoltages.pumpCurrent = spiAdc_convert(5);
    adcVoltages.shutdownCurrent = spiAdc_convert(6);
    adcVoltages.dcBusCurrent = spiAdc_convert(7);
    adcVoltages.dcBusVoltage = spiAdc_convert(8);
    adcVoltages.extraAnalog2 = spiAdc_convert(9);
    adcVoltages.sus2 = spiAdc_convert(10);
    adcVoltages.extraAnalog1 = spiAdc_convert(11);
    adcVoltages.loopTemp1 = spiAdc_convert(12);
    adcVoltages.loopTemp2 = spiAdc_convert(13);
    adcVoltages.ambientTemp = spiAdc_convert(14);
    adcVoltages.sus1 = spiAdc_convert(15);
}