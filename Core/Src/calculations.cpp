//
// Created by Dhairya Gupta on 4/14/24.
//

#include "calculations.h"
#include <cmath>

float calculations::getCurrentFromADC(float adc) {
    return ((adc-(3.3/2)) / 0.066);
}

float calculations::getTempFromLoop(float adc) {
    return (1.0f/25.0f) + ((1.0f/3977.0f) * log((3.3/adc)-1));
}

float calculations::getVoltageFromADC(float adc) {
    return adc * (112.0f/12.0f);
}
