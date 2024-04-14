#include "pwm.h"
#include "tim.h"

void pwm_init() {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

void pwm_regulateRadiatorFans(float f) {
    TIM1->CCR4 = (int)(f * 10000);
}
