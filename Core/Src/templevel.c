#include "templevel.h"
#include "tim.h"

void Add_Hot(float Init_value,float Detect_value)
{
	if(Detect_value<Init_value)
	{
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
		HAL_Delay(1000);
		HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	}
}

void Add_Hot_Timing(uint8_t cmd)
{
	switch(cmd)
	{
		case '6':
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
//		HAL_Delay(60*1000);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		break;
		
		case '7':
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
//		HAL_Delay(3*60*1000);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		break;
		
		case '8':
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
//		HAL_Delay(5*60*1000);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		break;
		
		case '9':
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		break;
		
		default:
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		break;
	}
}
