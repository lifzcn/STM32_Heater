#include "display.h"
#include "oled.h"

void Display_Init(float value)
{
	OLED_Init();//0.96��OLED����ʼ��
	OLED_Clear();//0.96��OLED�����
	OLED_ShowChinese(16,0,0);/*"ˮ",0*/
	OLED_ShowChinese(32,0,1);/*"��",1*/
	OLED_ShowChinese(48,0,2);/*"��",2*/
	OLED_ShowChinese(64,0,3);/*"��",3*/
	OLED_ShowChinese(80,0,4);/*"ϵ",4*/
	OLED_ShowChinese(96,0,5);/*"ͳ",5*/
	OLED_ShowChinese(0,2,6);/*"ʵ",6*/
	OLED_ShowChinese(16,2,7);/*"ʱ",7*/
	OLED_ShowChinese(32,2,8);/*"��",8*/
	OLED_ShowChinese(48,2,9);/*"��",9*/
	OLED_ShowChinese(64,2,21);/*"��",21*/
	OLED_ShowChinese(0,4,10);/*"Ԥ",10*/
	OLED_ShowChinese(16,4,11);/*"��",11*/
	OLED_ShowChinese(32,4,12);/*"��",12*/
	OLED_ShowChinese(48,4,13);/*"��",13*/
	OLED_ShowChinese(64,4,21);/*"��",21*/
	OLED_ShowNum(80,4,value,2,16);//��ʾԤ���¶�
	OLED_ShowChar(96,4,'C',16);//��ʾ�����¶ȷ��š�C��
	OLED_ShowChinese(0,6,14);/*"ˮ",14*/
	OLED_ShowChinese(16,6,15);/*"λ",15*/
	OLED_ShowChinese(32,6,16);/*"��",16*/
	OLED_ShowChinese(48,6,17);/*"��",17*/
	OLED_ShowChinese(64,6,21);/*"��",21*/
}
