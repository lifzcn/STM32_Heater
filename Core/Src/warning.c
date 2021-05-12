#include "warning.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"

void Temprature_Warning(float Init_value_low,float Init_value_high,float Detect_value)
{
	if((int)Detect_value>Init_value_high || (int)Detect_value<Init_value_low)
	{
		HAL_GPIO_WritePin(Buzzer_Statement_GPIO_Port,Buzzer_Statement_Pin,GPIO_PIN_RESET);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(Buzzer_Statement_GPIO_Port,Buzzer_Statement_Pin);
		HAL_GPIO_WritePin(LED_1_GPIO_Port,LED_1_Pin,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LED_1_GPIO_Port,LED_1_Pin);
	}
}

void Waterlevel_Warning(float Init_value_low,float Init_value_high,float Detect_value)
{
	if(Detect_value>Init_value_high || Detect_value<Init_value_low)
	{
		HAL_GPIO_WritePin(Buzzer_Statement_GPIO_Port,Buzzer_Statement_Pin,GPIO_PIN_RESET);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(Buzzer_Statement_GPIO_Port,Buzzer_Statement_Pin);
		HAL_GPIO_WritePin(LED_2_GPIO_Port,LED_2_Pin,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LED_2_GPIO_Port,LED_2_Pin);
	}
}
