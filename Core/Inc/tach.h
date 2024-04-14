#ifndef PDU_FIRMWARE_TACH_H
#define PDU_FIRMWARE_TACH_H

#endif //PDU_FIRMWARE_TACH_H

typedef struct {
  float radiatorFansRPM; // Rotations per minute
  float flowRate; //Volumetric flow rate in L/min
} TachData;

void tach_init();
float readRadiatorFans(float deltaTime);
float readFlowRate(float deltaTime);
void tach_periodic(float deltaTime, TachData& data);

