/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint32_t adc_value;
uint16_t t=0,t1=0,t2=0,i=0;
uint16_t vao=0,ra=0;
uint16_t t3=0,ss_vao=0,ss_nut=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1
#define  out_pin4(x) HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, x);
//#define in_pin6 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
#define daott4 HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void sensor_init(void);
void sosanh();
void nutnhan();
void docnn();
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void sensor_init(void)
{
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)== 0 && t1==0) // if the pin is HIGH 
  { 
		 //HAL_Delay (20); 
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==0); //wait for pin to go low 
		{
  t2=1;
   //HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, 1); // LED OFF 
		//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		}
		}
	 else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)== 0 && t2==1) 
	 {
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==0); 
		 {
			 vao++;
			 ss_vao++;
			 HAL_Delay(5);
			 t2=0;t1=0;
		 }
	 }
	 
	 else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)== 0 && t2==0) 
	 {
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==0); 
		 {
			 t1=1;
		 }
	 }
	 else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)== 0 && t1==1) // if the pin is HIGH 
  { 
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==0); //wait for pin to go low 
		{
			ra++;
			HAL_Delay(5);
			t1=0;t2=0;
		}
	}
//	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)== 0 ) // if the pin is HIGH 
//  { 
//		HAL_Delay(5);
//		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==0); //wait for pin to go low 
//		{
//			vao=ra;
//			HAL_Delay(5);
//			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
//			//out_pin4(1);
//			
//		}
//	}
	
}
void nutnhan()
{
		  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0 ) 
  { 
		HAL_Delay(5);
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); 
		{
			HAL_Delay(5);
			t3=~t3;
			ss_nut++;
		}
	}
}
void sosanh()
{
if(vao>ra)
{
	if (ss_vao>ss_nut)
	{
		if(t3==65535)
		{
			out_pin4(0);
		}
		else
		{
		out_pin4(1);
		}
		ss_vao=ss_nut=0;
	}
	else 
	{
		if(t3==65535)
		{
			out_pin4(1);
		}
		else
		{
		out_pin4(0);
		}
		ss_vao=ss_nut=0;
	}
}
else
{
	if (t3==65535)
	{
		out_pin4(1);
	}
	else 
	{
		out_pin4(0);
	}
	ra=vao=0;
}
}

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
// kl();
// lcd_goto_XY(1,1);
// string_lcd("alo");
// HAL_ADC_Start_IT(&hadc1);
//HAL_ADC_Start_DMA(&hadc1,&adc_value,1);
  /* USER CODE END 2 */
t3=0;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		//nutnhan();
		
		sensor_init();
		sosanh();
		nutnhan();
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
