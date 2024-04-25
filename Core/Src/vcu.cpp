#include "vcu.h"
#include "angel_can.h"
#include "angel_can_ids.h"
#include "imu.h"
#include "clock.h"
#include "calculations.h"

static CanInbox pduParams;
static CanInbox pduBrakeLight;
static CanInbox pduBuzzer;
static CanInbox pduCooling;
static CanOutbox pduThermals;
static CanOutbox imuAccel;
static CanOutbox imuGyro;
static CanOutbox lvBattery;
static CanOutbox pduCurrents1;
static CanOutbox pduCurrents2;
static CanOutbox pduStatus;

int cycles = 0;

//#define LOOP_TEMP(adc) (1.0f/25.0f) + (1.0f/3977.0f) * log((3.3/adc)-1)
//#define CURRENT(adcCurrent) ((adcCurrent-(3.3/2)) / 0.066)
//#define VOLTAGE(adcVoltage) adcVoltage * (112.0f/12.0f)

void vcu_init() {
    can_addInbox(VCU_PDU_PARAMS, &pduParams);
    can_addInbox(VCU_PDU_BRAKELIGHT, &pduBrakeLight);
    can_addInbox(VCU_PDU_BUZZER, &pduBuzzer);
    can_addInbox(VCU_PDU_COOLING, &pduCooling);

    can_addOutbox(PDU_VCU_THERMAL, 0.1f, &pduThermals);
    can_addOutbox(PDU_VCU_IMU_ACCEL, 0.003f, &imuAccel);
    can_addOutbox(PDU_VCU_IMU_GYRO, 0.003f, &imuGyro);
    can_addOutbox(PDU_VCU_LVBAT, 0.1f, &lvBattery);
    can_addOutbox(PDU_VCU_LV_CURRENTS_1, 0.1f, &pduCurrents1);
    can_addOutbox(PDU_VCU_LV_CURRENTS_2, 0.1f, &pduCurrents2);
    can_addOutbox(PDU_VCU_STATUS, 0.1f, &pduStatus);
}

void vcu_periodic(AdcVoltages& adcVoltages, VCUStatus &stat, TachData& tachData) {
    can_writeFloat(uint16_t, &pduCurrents1, 0, adcVoltages.dcBusCurrent, 0.01f);
    can_writeFloat(uint16_t, &pduCurrents1, 2, adcVoltages.radiatorFansCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents1, 4, adcVoltages.batteryFansCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents1, 6, adcVoltages.pumpCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 0, adcVoltages.accessoryCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 2, adcVoltages.glvCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 4, adcVoltages.shutdownCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 6, adcVoltages.brakeLightCurrent, 1.0f);
    pduCurrents1.dlc = 8;
    pduCurrents2.dlc = 8;

    can_writeFloat(int16_t, &imuAccel, 0, accelData.x, 0.01f);
    can_writeFloat(int16_t, &imuAccel, 2, accelData.y, 0.01f);
    can_writeFloat(int16_t, &imuAccel, 4, accelData.z, 0.01f);
    imuAccel.dlc = 6;

    can_writeFloat(int16_t, &imuGyro, 0, gyroData.x, 0.01f);
    can_writeFloat(int16_t, &imuGyro, 2, gyroData.y, 0.01f);
    can_writeFloat(int16_t, &imuGyro, 4, gyroData.z, 0.01f);
    imuGyro.dlc = 6;

    // Thermals, LV Battery
    // TODO: LV Battery
    can_writeFloat(uint8_t, &pduThermals, 0, tachData.flowRate, 0.1f);

    float loopTemp1 = calculations::getTempFromLoop(adcVoltages.loopTemp1);
    float loopTemp2 = calculations::getTempFromLoop(adcVoltages.loopTemp2);

    can_writeInt(int8_t, &pduThermals, 1, adcVoltages.ambientTemp); // TODO: THERMISTOR VOLTAGE TO TEMP
    can_writeInt(int8_t, &pduThermals, 2, loopTemp1);
    can_writeInt(int8_t, &pduThermals, 3, loopTemp2);
    can_writeInt(uint16_t, &pduThermals, 4, tachData.radiatorFansRPM);
    pduThermals.dlc = 6;

    can_writeFloat(int16_t , &lvBattery, 0, calculations::getVoltageFromADC(adcVoltages.dcBusVoltage), 0.01f);
    can_writeFloat(int16_t , &lvBattery, 2, 0, 0.01f);

    float current = calculations::getCurrentFromADC(adcVoltages.glvCurrent);
    can_writeFloat(int16_t, &lvBattery, 4, current, 0.01f);
    lvBattery.dlc = 6;


    // Check VCU->PDU Inboxes
    // TODO implement
    if(pduBrakeLight.isRecent) {
        stat.brakeLightPercent = can_readFloat(uint8_t, &pduBrakeLight, 0, 0.01f);

        // pulsating
//        stat.brakeLightPercent = ((float) ((int) clock_getTime() % 5)) / 5;
        pduBrakeLight.isRecent = false;
    }

    if(pduCooling.isRecent) {
        stat.pduCooling.radiatorFanPercent = can_readFloat(uint8_t, &pduCooling, 0, 0.01f);
        stat.pduCooling.pumpPercent = can_readFloat(uint8_t, &pduCooling, 1, 0.01f);

//        stat.pduCooling.radiatorFanPercent = ((float) (((int) clock_getTime()) % 10)) / 10;

        pduCooling.isRecent = false;
    }

    if(pduBuzzer.isRecent) {
        stat.buzzerType = can_readInt(uint8_t, &pduBuzzer, 0);

        pduBuzzer.isRecent = false;
    }

    cycles++;
}