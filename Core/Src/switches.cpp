#include "switches.h"

#include "tim.h"

void switches_init() {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

void switches_setBrakeLight(float f) {
    TIM1->CCR3 = (int)(f * 10000);
}

void switches_setPump(float f) {
    TIM1->CCR1 = (int)(f * 10000);
}

void switches_setAccessory(float f) {
    TIM1->CCR2 = (int)(f * 10000);
}

void switches_setRadiatorFans(float f) {
    TIM1->CCR4 = (int)(f * 10000);
}

void switches_setBatteryFans(bool on) {
    HAL_GPIO_WritePin(SW_BattFan_GPIO_Port, SW_BattFan_Pin, (GPIO_PinState) on);
}

void switches_setGLV(bool on) {
    HAL_GPIO_WritePin(SW_GLV_GPIO_Port, SW_GLV_Pin, (GPIO_PinState) on);
}

void switches_setShutdown(bool on) {
    HAL_GPIO_WritePin(SW_SHDN_GPIO_Port, SW_SHDN_Pin, (GPIO_PinState) on);
}