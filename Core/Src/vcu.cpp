#include "vcu.h"
#include "angel_can.h"
#include "angel_can_ids.h"
#include "imu.h"
#include "clock.h"

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

void vcu_periodic(AdcVoltages& adcVoltages, VCUStatus &stat) {
    can_writeFloat(uint16_t, &pduCurrents1, 0, adcVoltages.dcBusCurrent, 0.01f);
    can_writeFloat(uint16_t, &pduCurrents1, 2, adcVoltages.radiatorFansCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents1, 4, adcVoltages.batteryFansCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents1, 6, adcVoltages.pumpCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 0, adcVoltages.accessoryCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 2, adcVoltages.glvCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 4, adcVoltages.shutdownCurrent, 1.0f);
    can_writeFloat(uint16_t, &pduCurrents2, 6, adcVoltages.brakeLightCurrent, 1.0f);

    can_writeFloat(int16_t, &imuAccel, 0, accelData.x, 0.01f);
    can_writeFloat(int16_t, &imuAccel, 2, accelData.y, 0.01f);
    can_writeFloat(int16_t, &imuAccel, 4, accelData.z, 0.01f);

    can_writeFloat(int16_t, &imuGyro, 0, gyroData.x, 0.01f);
    can_writeFloat(int16_t, &imuGyro, 2, gyroData.y, 0.01f);
    can_writeFloat(int16_t, &imuGyro, 4, gyroData.z, 0.01f);

    // Thermals, LV Battery
    // TODO implement
    can_writeFloat(uint8_t, &pduThermals, 0, 0, 0);


    // Check VCU->PDU Inboxes
    // TODO implement
    if(pduBrakeLight.isRecent) {
        stat.brakeLightPercent = can_readFloat(uint8_t, &pduBrakeLight, 0, 0.01f);
//        stat.brakeLightPercent = ((float) ((int) clock_getTime() % 5)) / 5;
        pduBrakeLight.isRecent = false;
    }

    if(pduCooling.isRecent) {
        stat.pduCooling.radiatorFanPercent = can_readFloat(uint8_t, &pduCooling, 0, 0.01f);
        stat.pduCooling.pumpPercent = can_readFloat(uint8_t, &pduCooling, 1, 0.01f);

        pduCooling.isRecent = false;
    }

    if(pduBuzzer.isRecent) {
        stat.buzzerType = can_readInt(uint8_t, &pduBuzzer, 0);
        pduBuzzer.isRecent = false;
    }

    cycles++;
}