/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int timer_count=0;
int timer_flag=0;
int TIME_CYCLE=10;
void setTimer(int duration)
{
	timer_count=duration/TIME_CYCLE;
	timer_flag=0;
}
void timer_run()
{
	if(timer_count>0)
		{
		timer_count--;
		if(timer_count==0)timer_flag=1;
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
  MX_GPIO_Init () ;
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  const int MAX_LED_MATRIX=8;
  int index_led_matrix = 0;
  uint8_t matrix_buffer [8] = {
		  	0b00111100,
		    0b01100110,
		    0b11000011,
		    0b11000011,
		    0b11111111,
		    0b11000011,
		    0b11000011,
		    0b00000000};
  uint16_t pins_to_set[] = {GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
  void displayLEDMatrix(void) {
  	if(timer_flag[4]){
      	setTimer(4, 1);
      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, 0xFC0C);
      	// Tắt tất cả các chân
      	col = (col + 1) % MAX_LED_MATRIX;
      }
  	// Bật cột (col) tương ứng bằng cách sử dụng ULN2803 với tín hiệu đầu vào bằng 0
  	HAL_GPIO_WritePin(GPIOA, pins_to_set[col], GPIO_PIN_RESET);
  	// Hiển thị dữ liệu của cột (matrix_buffer[col]) lên hàng (row) tương ứng
  	// Sử dụng GPIO_PIN_SET cho common cathode và GPIO_PIN_RESET cho common anode
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (matrix_buffer[col] & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (matrix_buffer[col] & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (matrix_buffer[col] & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (matrix_buffer[col] & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (matrix_buffer[col] & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (matrix_buffer[col] & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (matrix_buffer[col] & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (matrix_buffer[col] & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  }
  void updateLEDMatrix(int index) {
      switch (index) {
          case 0:
              // Example pattern: First row onix_buffer[0] = 0xFF; // All LEDs in the first row ON
              break;
          case 1:
              // Example pattern: Second row on
              matrix_buffer[1] = 0xFF; // All LEDs in the second row ON
              break;
          case 2:
              // Example pattern: Third row on
              matrix_buffer[2] = 0xFF; // All LEDs in the third row ON
              break;
          case 3:
              // Example pattern: Fourth row on
              matrix_buffer[3] = 0xFF; // All LEDs in the fourth row ON
              break;
          case 4:
              // Example pattern: Fifth row on
              matrix_buffer[4] = 0xFF; // All LEDs in the fifth row ON
              break;
          case 5:
              // Example pattern: Sixth row on
              matrix_buffer[5] = 0xFF; // All LEDs in the sixth row ON
              break;
          case 6:
              // Example pattern: Seventh row on
              matrix_buffer[6] = 0xFF; // All LEDs in the seventh row ON
              break;
          case 7:
              // Example pattern: Eighth row on
              matrix_buffer[7] = 0xFF; // All LEDs in the eighth row ON
              break;
          default:
              // Default case, clear the matrix
              for (int i = 0; i < MAX_LED_MATRIX; i++) {
                  matrix_buffer[i] = 0x00; // Clear all rows
              }
              break;
      }

  }
HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
void displayMatrix(uint8_t *pattern) {
    for (int row = 0; row < 8; row++) {
    	HAL_GPIO_WritePin(GPIOB, 0xFF, GPIO_PIN_RESET); // Reset previous row
    	HAL_GPIO_WritePin(GPIOB, (1 << row), GPIO_PIN_SET); // Set current row
    	        HAL_Delay(1000);

    }
}


setTimer(100);
  while (1)
  {
	  HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin ,SET); // Set current row
	  HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW2_Pin ,SET);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DOT_Pin|LED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG3_Pin|GPIO_PIN_11
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DOT_Pin LED_Pin EN0_Pin EN1_Pin
                           EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = DOT_Pin|LED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG1_Pin SEG2_Pin SEG3_Pin PB11
                           SEG4_Pin SEG5_Pin SEG6_Pin SEG7_Pin */
  GPIO_InitStruct.Pin = SEG1_Pin|SEG2_Pin|SEG3_Pin|GPIO_PIN_11
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


 void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	 timer_run();
	/*  if(second>=60)
	  {
		  minute++;
		  second=0;
	  }
	  if(minute>=60)
	  {
		  hour++;
		  minute=0;
	  }
	  if(hour>=24)
	  {
		  hour=0;
	  }

	  updateled(hour, minute);
	 if(counter>=0) {
		 if(0<counter&&counter<100&&counter%25==0)
		 {
			 if(index>3)index=0;
			 update7SEG(index++);
		 }
		 counter--;
	 }
	 else{
		 counter=100;
		 if(index>3)index=0;
		 update7SEG(index++);
		 second++;
	 }*/
 }


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
