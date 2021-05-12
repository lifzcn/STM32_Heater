/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "oled.h"
#include "ds18b20.h"
#include "warning.h"
#include "display.h"
#include "waterlevel.h"
#include "templevel.h"
#include "gp2y0a21.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	int i = 0;
	int value;
	float TempInit_Value = 30;
	float Temp_Value;
	float TempInit_Value_Low = 0;
	float TempInit_Value_High = 65;
	float WaterlevelInit_Value_Low = 20;
	float WaterlevelInit_Value_High = 40;
	float Waterlevel_Value;
	float Vol_value;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	Display_Init(TempInit_Value);
	DS18B20_Test();  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		i += 1;
		
		uint8_t Chr_cmd = HAL_UART_ReceiveData(USART1);//接收APP发送的指令
		
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		value = HAL_ADC_GetValue(&hadc1);
		Vol_value = value*(3.3/4096);
		
		if(i%2 == 0)
		{
			Temp_Value = DS18B20_GetTemperture();	
			OLED_ShowNum(80,2,Temp_Value,2,16);//显示实时温度
			OLED_ShowChar(96,2,'C',16);//显示摄氏温度符号‘C’
			printf("==================\r\n");
			printf("实时温度：%.1f C\r\n",Temp_Value);
		}
		
		if(i%2 == 0)
		{
			Waterlevel_Value =50 - GP2Y0A21_GetDistance(Vol_value);
			printf("实时水位：%.1f cm\r\n",Waterlevel_Value);
			printf("==================\r\n");
		}
		
		if(HAL_GPIO_ReadPin(Key_Up_GPIO_Port,Key_Up_Pin)==GPIO_PIN_RESET)//若按键KEY1按下
		{
			HAL_Delay(200);//延时200ms消抖
			TempInit_Value += 1;//预设温度上调2度
			OLED_ShowNum(80,4,TempInit_Value,2,16);
		}
		else if(HAL_GPIO_ReadPin(Key_Down_GPIO_Port,Key_Down_Pin)==GPIO_PIN_RESET)//若按键KEY2按下
		{
			HAL_Delay(200);//延时200ms消抖
			TempInit_Value -= 1;//预设温度下调2度
			OLED_ShowNum(80,4,TempInit_Value,2,16);
		}
			
		switch(Chr_cmd)
		{
			case '1':
				TempInit_Value += 1;
				OLED_ShowNum(80,4,TempInit_Value,2,16);
			break;
			
			case '2':
				TempInit_Value -= 1;
				OLED_ShowNum(80,4,TempInit_Value,2,16);
			break;
			
			case '3':
				HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;
			
			case '4':
				HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
			break;
			
			case '5':
				Add_Hot_Timing(Chr_cmd);
			break;
			
			default:
				TempInit_Value += 0;
				OLED_ShowNum(80,4,TempInit_Value,2,16);
			break;
		}
		
		Add_Hot(TempInit_Value,Temp_Value);
		Temprature_Warning(TempInit_Value_Low,TempInit_Value_High,Temp_Value);
		
		Water_Level(WaterlevelInit_Value_Low,WaterlevelInit_Value_High,Waterlevel_Value);	
		Waterlevel_Warning(WaterlevelInit_Value_Low,WaterlevelInit_Value_High,Waterlevel_Value);
		
		Chr_cmd = '0';
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
