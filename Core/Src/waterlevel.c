#include "waterlevel.h"
#include "oled.h"
#include "tim.h"

void Water_Level(float Init_value_low,float Init_value_high,float Detect_value)
{
	int Flag;
	if(Detect_value<Init_value_low)
	{
		Flag = 3;
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	}
	else if(Detect_value>=Init_value_low  && Detect_value<=Init_value_high) 
	{
		Flag = 2;
		HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	}
	else
	{
		Flag = 1;
		HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	}
	switch(Flag)
	{
		case 1:
			OLED_ShowChinese(80,6,18);/*"¸ß",18*/
		break;
			
		case 2:
			OLED_ShowChinese(80,6,19);/*"ÖÐ",19*/
		break;
			
		case 3:
			OLED_ShowChinese(80,6,20);/*"µÍ",20*/
		break;
			
		default:
			OLED_ShowChar(80,6,'-',16);
			OLED_ShowChar(88,6,'-',16);
		break;
	}
}
