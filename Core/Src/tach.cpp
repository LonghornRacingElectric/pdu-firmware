#include "tach.h"
#include "lptim.h"

#define COUNT_MAX 0xFFFF

void tach_init() {
  HAL_LPTIM_Init(&hlptim1);
  HAL_LPTIM_Init(&hlptim2);

  volatile int error = HAL_LPTIM_Counter_Start(&hlptim1, COUNT_MAX);
  HAL_LPTIM_Counter_Start(&hlptim2, COUNT_MAX);
  error++;


}

static uint32_t countRadiatorFan = 0;
static float accumTime = 0;
static uint32_t countFlowRate = 0;

uint16_t readRadiatorFans(float deltaTime){
  uint32_t count = HAL_LPTIM_ReadCounter(&hlptim1);
  float freq = 0.0f; // rotations per second
  if(count != 0){
      freq = count / deltaTime;
      // hlptim1.Instance->CNT = 0;
  }
  return (uint16_t) (freq * 600); // convert to rotations per minute
}

float readFlowRate(float deltaTime){
  uint32_t count = HAL_LPTIM_ReadCounter(&hlptim2);
  float freq = 0;
  if(count != 0){
    freq = count / deltaTime;
    hlptim2.Instance->CNT = 0;
  }
  return freq / 2.1;
}

void tach_periodic(float deltaTime, TachData& data){
    accumTime += deltaTime;
    if(accumTime < 0.1f){
        return;
    }
  data.radiatorFansRPM = readRadiatorFans(accumTime);
  data.flowRate = readFlowRate(accumTime);
  accumTime = 0;
}


