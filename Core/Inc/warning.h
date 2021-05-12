#ifndef __WARNING_H__
#define __WARNING_H__

#include "stm32f1xx_hal.h"

void Temprature_Warning(float Init_value_low,float Init_value_high,float Detect_value);
void Waterlevel_Warning(float Init_value_low,float Init_value_high,float Detect_value);

#endif
