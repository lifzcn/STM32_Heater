#include "display.h"
#include "oled.h"

void Display_Init(float value)
{
	OLED_Init();//0.96寸OLED屏初始化
	OLED_Clear();//0.96寸OLED屏清空
	OLED_ShowChinese(16,0,0);/*"水",0*/
	OLED_ShowChinese(32,0,1);/*"温",1*/
	OLED_ShowChinese(48,0,2);/*"检",2*/
	OLED_ShowChinese(64,0,3);/*"测",3*/
	OLED_ShowChinese(80,0,4);/*"系",4*/
	OLED_ShowChinese(96,0,5);/*"统",5*/
	OLED_ShowChinese(0,2,6);/*"实",6*/
	OLED_ShowChinese(16,2,7);/*"时",7*/
	OLED_ShowChinese(32,2,8);/*"温",8*/
	OLED_ShowChinese(48,2,9);/*"度",9*/
	OLED_ShowChinese(64,2,21);/*"：",21*/
	OLED_ShowChinese(0,4,10);/*"预",10*/
	OLED_ShowChinese(16,4,11);/*"设",11*/
	OLED_ShowChinese(32,4,12);/*"温",12*/
	OLED_ShowChinese(48,4,13);/*"度",13*/
	OLED_ShowChinese(64,4,21);/*"：",21*/
	OLED_ShowNum(80,4,value,2,16);//显示预设温度
	OLED_ShowChar(96,4,'C',16);//显示摄氏温度符号‘C’
	OLED_ShowChinese(0,6,14);/*"水",14*/
	OLED_ShowChinese(16,6,15);/*"位",15*/
	OLED_ShowChinese(32,6,16);/*"档",16*/
	OLED_ShowChinese(48,6,17);/*"数",17*/
	OLED_ShowChinese(64,6,21);/*"：",21*/
}
