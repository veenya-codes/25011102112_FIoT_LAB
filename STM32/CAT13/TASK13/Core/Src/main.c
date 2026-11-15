/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include <stdlib.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bme280.h"
#include <stdio.h> 
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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
	extern I2C_HandleTypeDef hi2c1; // Assumes I2C1 is configured via CubeMX
	struct bme280_dev dev;
	struct bme280_data comp_data;
	struct bme280_settings settings;
	int8_t rslt = BME280_OK;
	
	// Variables to store final calculated values
	float temperature=0.0f, pressure=0.0f, humidity=0.0f; 
	uint8_t rx_data[800];
	uint8_t rx_char;
	uint16_t array_index = 0;

	char ip_info[150];       
	char json_data[200];     
	char response[1024];   
	char cmd[64];
	char html_page[800];
	char sensor_text[900];

	uint8_t cmd1[] = "AT\r\n";
	uint8_t cmd2[] = "AT+CWMODE=1\r\n";
	uint8_t cmd3[] = "AT+CWJAP=\"<SSID>\",\"<PASSWORD>\"\r\n";
	uint8_t cmd4[] = "AT+CIFSR\r\n";
	uint8_t cmd5[] = "AT+CIPMUX=1\r\n";
	uint8_t cmd6[] = "AT+CIPSERVER=1,80\r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
	void SystemClock_Config(void);
	static void MX_GPIO_Init(void);
	static void MX_I2C1_Init(void);
	static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
		 uint8_t dev_addr = *(uint8_t*)intf_ptr;
		 if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, len,
		HAL_MAX_DELAY) == HAL_OK) {
				return BME280_OK;
		 }
		 return BME280_E_COMM_FAIL;
	}
	int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
		 uint8_t dev_addr = *(uint8_t*)intf_ptr;
		 if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT,
		(uint8_t*)reg_data, len, HAL_MAX_DELAY) == HAL_OK) {
				return BME280_OK;
		 }
		 return BME280_E_COMM_FAIL;
	}
	void user_delay_us(uint32_t period, void *intf_ptr) {
	 HAL_Delay((period / 1000) + 1);
	} 

	void clear_buffer(void)
	{
			memset(rx_data, 0, sizeof(rx_data));
			array_index = 0;
		}
	void receive_response(void) {
			while (1) {
					if (HAL_UART_Receive(&huart2, &rx_char, 1, 20000) == HAL_OK) {
							if (array_index < sizeof(rx_data) - 1) {
									rx_data[array_index++] = rx_char;
									rx_data[array_index] = '\0';
							}

							if (strstr((char *)rx_data, "OK\r\n") != NULL) {
									break;
							}
							if (strstr((char *)rx_data, "ERROR") != NULL ||
									strstr((char *)rx_data, "FAIL") != NULL) {
									break;
							}
					} else {
							break;
					}
			}
	}
	void send_http_response(const char *content, const char *content_type, int conn_id) {
			int content_len = strlen(content);
			int response_len = snprintf(response, sizeof(response),
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: %s\r\n"
					"Content-Length: %d\r\n"
					"Connection: close\r\n\r\n"
					"%s",
					content_type, content_len, content);

			snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d,%d\r\n", conn_id, response_len);

			clear_buffer();
			HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 1000);
			HAL_Delay(200); // Wait for '>' prompt from ESP8266

			HAL_UART_Transmit(&huart2, (uint8_t*)response, response_len, 1000);
			HAL_Delay(300); // Wait for SEND OK

			clear_buffer();
			snprintf(cmd, sizeof(cmd), "AT+CIPCLOSE=%d\r\n", conn_id);
			HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 1000);
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
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	static uint8_t dev_addr = BME280_I2C_ADDR_PRIM; // 0x76 (use BME280_I2C_ADDR_SEC if SDO is high)

 // Set up the API configuration function pointers
 dev.intf_ptr = &dev_addr;
 dev.intf = BME280_I2C_INTF;
 dev.read = user_i2c_read;
 dev.write = user_i2c_write;
 dev.delay_us = user_delay_us;
 // Initialize the BME280 sensor (This automatically extracts the compensation data)
 rslt = bme280_init(&dev);
 // Configure sensor settings
 settings.osr_h = BME280_OVERSAMPLING_1X;
 settings.osr_p = BME280_OVERSAMPLING_1X;
 settings.osr_t = BME280_OVERSAMPLING_1X;
 settings.filter = BME280_FILTER_COEFF_OFF;
 rslt = bme280_set_sensor_settings(BME280_SEL_OSR_PRESS | BME280_SEL_OSR_TEMP |BME280_SEL_OSR_HUM | BME280_SEL_FILTER,&settings ,&dev);

 // Set power mode to normal to enable continuous measurement cycles
 rslt = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev); 
  /* USER CODE END 2 */
	HAL_Delay(2000);
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd1, strlen((char *)cmd1), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd2, strlen((char *)cmd2), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd3, strlen((char *)cmd3), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
  HAL_UART_Transmit(&huart2, cmd4, strlen((char *)cmd4), HAL_MAX_DELAY);
  receive_response();
  strncpy(ip_info, (char *)rx_data, sizeof(ip_info) - 1); // Save IP for debugger inspection
  ip_info[sizeof(ip_info) - 1] = '\0';
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd5, strlen((char *)cmd5), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd6, strlen((char *)cmd6), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);

    if (rslt == BME280_OK)
    {
        temperature = comp_data.temperature;
        pressure = comp_data.pressure / 100.0f;
        humidity = comp_data.humidity;
    }

    if (HAL_UART_Receive(&huart2, &rx_char, 1, 10) == HAL_OK)
    {
        if (array_index < sizeof(rx_data) - 1)
        {
            rx_data[array_index++] = rx_char;
            rx_data[array_index] = '\0';
        }
        char *ipd_ptr = strstr((char *)rx_data, "+IPD,");
        if (ipd_ptr != NULL && strstr((char *)rx_data, "\r\n\r\n") != NULL)
        {
            int conn_id = ipd_ptr[5] - '0';
            if (conn_id < 0 || conn_id > 4)
            {
                conn_id = 0;
            }
            if (strstr((char *)rx_data, "GET /data") != NULL)
            {
                snprintf(sensor_text, sizeof(sensor_text),
                    "Temperature: %.2f C<br>"
                    "Pressure: %.2f hPa<br>"
                    "Humidity: %.2f %%",
                    temperature, pressure, humidity);

                send_http_response(sensor_text, "text/html", conn_id);
            }
            else if (strstr((char *)rx_data, "GET / ") != NULL)
            {
                snprintf(html_page, sizeof(html_page),
                    "<html><body>"
                    "<h1>Helloo!!</h1>"
                    "<h3 id='data'>Loading...</h3>"
                    "<script>"
                    "function update(){"
                    "fetch('/data').then(r=>r.text()).then(t=>"
                    "document.getElementById('data').innerHTML=t);"
                    "}"
                    "update();setInterval(update,1000);"
                    "</script></body></html>");

                send_http_response(html_page, "text/html", conn_id);
            }
						else
						{
								send_http_response("Not Found", "text/plain", conn_id);
						}


            clear_buffer();
        }
    }
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
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
#ifdef USE_FULL_ASSERT
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
