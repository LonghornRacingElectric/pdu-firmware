#ifndef PDU_FIRMWARE_TACH_H
#define PDU_FIRMWARE_TACH_H

#include <cstdint>

typedef struct TachData {
  int radiatorFansRPM; // Rotations per minute
  float flowRate; //Volumetric flow rate in L/min
} TachData;

void tach_init();
uint16_t readRadiatorFans(float deltaTime);
float readFlowRate(float deltaTime);
void tach_periodic(float deltaTime, TachData& data);

#endif //PDU_FIRMWARE_TACH_H

