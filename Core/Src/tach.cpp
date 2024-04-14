#include "tach.h"
#include "lptim.h"

#define COUNT_MAX 0xFFFF

void tach_init() {
  HAL_LPTIM_Init(&hlptim1);
  HAL_LPTIM_Init(&hlptim2);

  HAL_LPTIM_Counter_Start(&hlptim1, COUNT_MAX);
  HAL_LPTIM_Counter_Start(&hlptim2, COUNT_MAX);


}

static int prev_radiator_count = 0;
static int prev_flow_count = 0;

float readRadiatorFans(float deltaTime){
  uint32_t count = HAL_LPTIM_ReadCounter(&hlptim1);
  float freq = 0; // rotations per second
  if(count != prev_radiator_count){
    if(count < prev_radiator_count){ // Overflow
      freq = (COUNT_MAX - prev_radiator_count + count) / deltaTime;
    } else {
      freq = (count - prev_radiator_count) / deltaTime;
    }
    prev_radiator_count = count;
  }
  return freq * 60; // convert to rotations per minute
}

float readFlowRate(float deltaTime){
  uint32_t count = HAL_LPTIM_ReadCounter(&hlptim2);
  float freq = 0;
  if(count != prev_flow_count){
    if(count < prev_flow_count){ // Overflow
      freq = (COUNT_MAX - prev_flow_count + count) / deltaTime;
    } else {
      freq = (count - prev_flow_count) / deltaTime;
    }
    prev_flow_count = count;
  }
  return freq / 21;
}

void tach_periodic(float deltaTime, TachData& data){
  data.radiatorFansRPM = readRadiatorFans(deltaTime);
  data.flowRate = readFlowRate(deltaTime);
}


