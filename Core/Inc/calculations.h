//
// Created by Dhairya Gupta on 4/14/24.
//

#ifndef PDU_FIRMWARE_CALCULATIONS_H
#define PDU_FIRMWARE_CALCULATIONS_H


class calculations {
public:
    static float getCurrentFromADC(float adc);
    static float getTempFromLoop(float adc);
    static float getVoltageFromADC(float adc);
};


#endif //PDU_FIRMWARE_CALCULATIONS_H
