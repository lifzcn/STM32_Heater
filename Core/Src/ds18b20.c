#include "ds18b20.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "oled.h"
#include "stdio.h"

/*******************************************************************************
* 函 数 名         : DS18B20_IO_IN
* 函数功能		     : DS18B20_IO输入配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin=DS18B20_Detect_Pin;//PB15
  GPIO_InitStructure.Mode=GPIO_MODE_INPUT;//输入
  GPIO_InitStructure.Pull=GPIO_PULLUP;//上拉
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//高速
  HAL_GPIO_Init(DS18B20_Detect_GPIO_Port,&GPIO_InitStructure);//初始化
}

/*******************************************************************************
* 函 数 名         : DS18B20_IO_OUT
* 函数功能		     : DS18B20_IO输出配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin=DS18B20_Detect_Pin;//PB5
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//推挽输出
  GPIO_InitStructure.Pull=GPIO_PULLUP;//上拉
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//高速
  HAL_GPIO_Init(DS18B20_Detect_GPIO_Port,&GPIO_InitStructure);//初始化
}

/*******************************************************************************
* 函 数 名         : DS18B20_Reset
* 函数功能		     : 复位DS18B20  
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DS18B20_Reset(void)	   
{                 
	DS18B20_IO_OUT();//SET PG11 OUTPUT
	DS18B20_DQ_OUT_LOW;//拉低DQ
	HAL_Delay_us(750);//拉低750us
	DS18B20_DQ_OUT_HIGH;//DQ=1 
	HAL_Delay_us(15);//延时15us
}

/*******************************************************************************
* 函 数 名         : DS18B20_Check
* 函数功能		     : 检测DS18B20是否存在
* 输    入         : 无
* 输    出         : 1:未检测到DS18B20的存在，0:存在
*******************************************************************************/
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN();	 
  while(DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		HAL_Delay_us(1);
	};	 
	if(retry>=200)
	{
		return 1;
	}
	else
	{
		retry=0;
	}
  while(!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		HAL_Delay_us(1);
	};
	if(retry>=240)
	{
		return 1;
	}		
	return 0;
}

/*******************************************************************************
* 函 数 名         : DS18B20_Read_Bit
* 函数功能		     : 从DS18B20读取一个位
* 输    入         : 无
* 输    出         : 1/0
*******************************************************************************/
uint8_t DS18B20_Read_Bit(void)
{
	uint8_t data;
	DS18B20_IO_OUT();//SET PG11 OUTPUT
	DS18B20_DQ_OUT_LOW; 
	HAL_Delay_us(2);
	DS18B20_DQ_OUT_HIGH; 
	DS18B20_IO_IN();//SET PG11 INPUT
	HAL_Delay_us(12);
	if(DS18B20_DQ_IN)
	{
		data=1;
	}
	else
	{
		data=0;
	}		
	HAL_Delay_us(50);           
	return data;
}

/*******************************************************************************
* 函 数 名         : DS18B20_Read_Byte
* 函数功能		     : 从DS18B20读取一个字节
* 输    入         : 无
* 输    出         : 一个字节数据
*******************************************************************************/
//返回值：读到的数据
uint8_t DS18B20_Read_Byte(void)
{        
  uint8_t i,j,dat;
  dat=0;
	for(i=1;i<=8;i++) 
	{
		j=DS18B20_Read_Bit();
    dat=(j<<7)|(dat>>1);
	}						    
	return dat;
}

/*******************************************************************************
* 函 数 名         : DS18B20_Write_Byte
* 函数功能		     : 写一个字节到DS18B20
* 输    入         : dat：要写入的字节
* 输    出         : 无
*******************************************************************************/
void DS18B20_Write_Byte(uint8_t dat)     
{             
	uint8_t j;
  uint8_t testb;
	DS18B20_IO_OUT();//SET PG11 OUTPUT;
  for (j=1;j<=8;j++) 
	{
		testb=dat&0x01;
    dat=dat>>1;
    if(testb) 
    {
			DS18B20_DQ_OUT_LOW;//Write 1
      HAL_Delay_us(2);                            
      DS18B20_DQ_OUT_HIGH;
      HAL_Delay_us(60);
		}
		else
		{
			DS18B20_DQ_OUT_LOW;//Write 0
      HAL_Delay_us(60);             
      DS18B20_DQ_OUT_HIGH;
      HAL_Delay_us(2);                          
		}
	}
}

/*******************************************************************************
* 函 数 名         : DS18B20_Start
* 函数功能		     : 开始温度转换
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DS18B20_Start(void)//ds1820 start convert
{   						               
	DS18B20_Reset();	   
	DS18B20_Check();	 
  DS18B20_Write_Byte(0xcc);//skip rom
  DS18B20_Write_Byte(0x44);//convert
} 

/*******************************************************************************
* 函 数 名         : DS18B20_Init
* 函数功能		     : 初始化DS18B20的IO口 DQ 同时检测DS的存在
* 输    入         : 无
* 输    出         : 1:不存在，0:存在
*******************************************************************************/   	 
uint8_t DS18B20_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure = {0};
	__HAL_RCC_GPIOG_CLK_ENABLE();//开启GPIOG时钟
	GPIO_InitStructure.Pin=GPIO_PIN_9;//PG9
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//推挽输出
  GPIO_InitStructure.Pull=GPIO_PULLUP;//上拉
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//高速
  HAL_GPIO_Init(GPIOG,&GPIO_InitStructure);//初始化
 	DS18B20_Reset();
	return DS18B20_Check();
}  

/*******************************************************************************
* 函 数 名         : DS18B20_GetTemperture
* 函数功能		     : 从ds18b20得到温度值
* 输    入         : 无
* 输    出         : 温度数据
*******************************************************************************/ 
float DS18B20_GetTemperture(void)
{
  uint16_t temp;
	uint8_t a,b;
	float value;
  DS18B20_Start();//ds1820 start convert
  DS18B20_Reset();
  DS18B20_Check();	 
  DS18B20_Write_Byte(0xcc);//skip rom
  DS18B20_Write_Byte(0xbe);//convert	    
  a=DS18B20_Read_Byte();//LSB   
  b=DS18B20_Read_Byte();//MSB   
	temp=b;
	temp=(temp<<8)+a;
  if((temp&0xf800)==0xf800)
	{
		temp=(~temp)+1;
		value=temp*(-0.0625);
	}
	else
	{
		value=temp*0.0625;	
	}  
	return value;
}

void DS18B20_Test(void)
{
	while(DS18B20_Init())
	{
		printf("DS18B20接入失败，请重试!\r\n");
		HAL_Delay(500);
	}
	printf("DS18B20接入成功!\r\n");
}
