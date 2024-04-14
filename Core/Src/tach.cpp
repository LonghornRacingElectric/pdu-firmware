#include "tach.h"
#include "lptim.h"

void tach_init() {
  HAL_LPTIM_Init(&hlptim1);
  HAL_LPTIM_Init(&hlptim2);
}

void readRadiatorFans(){
  HAL_LPTIM_Encoder_Start(&hlptim1, 0xFFFF);
}

void readFlowRate(){

}


