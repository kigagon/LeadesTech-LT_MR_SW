/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Compile_Data.h"
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

IWDG_HandleTypeDef hiwdg;

UART_HandleTypeDef hlpuart2;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;

PCD_HandleTypeDef hpcd_USB_DRD_FS;

/* USER CODE BEGIN PV */

uint8_t UI_UART_TX_buf[UI_UART_buf_len] ;
uint8_t UI_UART_RX_buf[UI_UART_buf_len];
uint8_t UI_UART_Tx_buf_tmp[UI_UART_buf_len];
uint8_t UI_UART_RX_buf_tmp[UI_UART_buf_len];
uint8_t UI_UART_State ;					// Define reception start state
int UI_UART_buf_count;					// Save the length of received data after starting reception
int UI_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
uint8_t UI_UART_Receive_complete;		// Variable indicating that reception has been completed
int UI_UART_buf_count_Save;

uint8_t SUB_UART_TX_buf[SUB_UART_buf_len] ;
uint8_t SUB_UART_RX_buf[SUB_UART_buf_len];
uint8_t SUB_UART_Tx_buf_tmp[SUB_UART_buf_len];
uint8_t SUB_UART_RX_buf_tmp[SUB_UART_buf_len];
uint8_t SUB_UART_State ;					// Define reception start state
int SUB_UART_buf_count;					// Save the length of received data after starting reception
int SUB_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
uint8_t SUB_UART_Receive_complete;		// Variable indicating that reception has been completed
int SUB_UART_buf_count_Save;


uint8_t MENU_POPUP_SW, MENU_POPUP_SW_Save[Save_Num], MENU_POPUP_SW_Sum;
uint8_t MAIN_BELL_SW, MAIN_BELL_SW_Save[Save_Num], MAIN_BELL_SW_Sum;
uint8_t SUB_BELL_SW, SUB_BELL_SW_Save[Save_Num], SUB_BELL_SW_Sum;
uint8_t LOCAL_BELL_SW, LOCAL_BELL_SW_Save[Save_Num], LOCAL_BELL_SW_Sum;
uint8_t SIREN_SW, SIREN_SW_Save[Save_Num], SIREN_SW_Sum;
uint8_t EMERGENCY_SW, EMERGENCY_SW_Save[Save_Num], EMERGENCY_SW_Sum;
uint8_t SW1_SW, SW1_SW_Save[Save_Num], SW1_SW_Sum;
uint8_t SW2_SW, SW2_SW_Save[Save_Num], SW2_SW_Sum;
uint8_t SW3_SW, SW3_SW_Save[Save_Num], SW3_SW_Sum;
uint8_t SW4_SW, SW4_SW_Save[Save_Num], SW4_SW_Sum;
uint8_t SW5_SW, SW5_SW_Save[Save_Num], SW5_SW_Sum;
uint8_t SW6_SW, SW6_SW_Save[Save_Num], SW6_SW_Sum;

uint8_t Pre_MENU_POPUP_SW;
uint8_t Pre_MAIN_BELL_SW;
uint8_t Pre_SUB_BELL_SW;
uint8_t Pre_LOCAL_BELL_SW;
uint8_t Pre_SIREN_SW;
uint8_t Pre_EMERGENCY_SW;
uint8_t Pre_SW1_SW;
uint8_t Pre_SW2_SW;
uint8_t Pre_SW3_SW;
uint8_t Pre_SW4_SW;
uint8_t Pre_SW5_SW;
uint8_t Pre_SW6_SW;

uint8_t Local_phone_mode;
uint8_t phone_jack_mode;
uint8_t Local_phone_mode_Save[Phone_Reas_Num];
uint8_t phone_jack_mode_Save[Phone_Reas_Num];
uint8_t Local_phone_mode_Sum;
uint8_t phone_jack_mode_Sum;


uint8_t inf_LED;
uint8_t Pre_inf_SWI,inf_SWI;
uint8_t Pre_inf_Other, inf_Other;

uint8_t inf_LED_sub[8];
uint8_t inf_SWI_sub[8];
uint8_t inf_Other_sub[8];

uint8_t user_LED;
uint8_t Pre_user_SWI,user_SWI;

uint8_t user_LED_sub[8];
uint8_t user_SWI_sub[8];

uint8_t MENU_POPUP_LED_mode = LED_Off;
uint8_t MAIN_BELL_LED_mode = LED_Off;
uint8_t SUB_BELL_LED_mode = LED_Off;
uint8_t LOCAL_BELL_LED_mode = LED_Off;
uint8_t SIREN_LED_mode = LED_Off;
uint8_t EMERGENCY_LED_mode = LED_Off;

uint8_t FIRE_LED_mode = LED_Off;
uint8_t BALSIN_LED_mode = LED_Off;
uint8_t AC_LED_mode = LED_Off;
uint8_t BAT_ERR_mode = LED_Off;
uint8_t PHONE_LED_mode = LED_Off;

uint8_t SW1_SW_mode = LED_Off;
uint8_t SW2_SW_mode = LED_Off;
uint8_t SW3_SW_mode = LED_Off;
uint8_t SW4_SW_mode = LED_Off;
uint8_t SW5_SW_mode = LED_Off;
uint8_t SW6_SW_mode = LED_Off;

uint8_t RUN_LED_mode = LED_Off;
uint8_t ERR_LED_mode = LED_Off;

uint8_t Pre_Key_MENU_POPUP;
uint8_t Pre_Key_SUB_BELL_STOP;
uint8_t Pre_Key_SIREN_STOP;
uint8_t Pre_Key_MAIN_BELL_STOP;
uint8_t Pre_Key_LOCAL_BELL_STOP;
uint8_t Pre_Key_EMERGENCY_STOP;

uint8_t Ext_phpne_mode;
uint8_t Local_phone_mode;
uint8_t phone_jack_mode;
uint8_t Sub_buzzer4_mode;
uint8_t Sub_buzzer3_mode;
uint8_t Sub_buzzer2_mode;
uint8_t Sub_buzzer1_mode;
uint8_t Main_buzzer_mode;

uint8_t Sub_MCC_Set_Num  = 1;
uint8_t Sub_MCC_R_Data[Sub_MCC_Num][Sub_MCC_R_length] ;
uint8_t Sub_MCC_S_Data[Sub_MCC_Num][Sub_MCC_S_length] ;
uint8_t Sub_MCC_state[Sub_MCC_Num];

uint8_t MCC_LED_Set[Sub_MCC_Num][40];  // 모든 led 정보
uint8_t LED_Data_Set[Sub_MCC_Num][5];  // MCC_LED_Set을 통신용 데이타로  변경
uint8_t PUMP_AUTO_set[Sub_MCC_Num][6];
uint8_t PUMP_STOP_set[Sub_MCC_Num][6];
uint8_t PUMP_MANUAL_set[Sub_MCC_Num][6];
uint8_t PUMP_CHECK_set[Sub_MCC_Num][6];
uint8_t PUMP_PS_set[Sub_MCC_Num][6];
uint8_t MCC_HANJUN_state, MCC_BALJUN_State;
uint8_t MCC_HANJUN_set[Sub_MCC_Num];
uint8_t MCC_BALJUN_set[Sub_MCC_Num];
uint8_t MCC_SW_LOCK_ON_set[Sub_MCC_Num];
uint8_t MCC_SW_LOCK_OFF_set[Sub_MCC_Num];
uint8_t MCC_TERMINATION_set[Sub_MCC_Num];
uint8_t Auto_Dip_set[Sub_MCC_Num];
uint8_t Auto_Dip[Sub_MCC_Num][6];

uint8_t PUMP_PS_Pre_set[Sub_MCC_Num][6];
uint8_t PUMP_PS_set_Mode[Sub_MCC_Num][6];

uint8_t Sub_DO24_Set_Num = 1;
#define Sub_DO24_Num     5
uint8_t Sub_DO24_R_Data[Sub_DO24_Num][Sub_DO24_R_length] ;
uint8_t Sub_DO24_state[Sub_DO24_Num];

uint8_t Sub_Relay_Set_Num = 1;
#define Sub_Relay_Num 3
uint8_t Sub_Relay_R_Data[Sub_Relay_Num][Sub_Relay_R_length] ;
uint8_t Sub_Relay_S_Data[Sub_Relay_Num][Sub_Relay_S_length] ;
uint8_t Sub_Pre_Motor_Run_Mode[Sub_Relay_Num][6]; // 현재 모터 동작 상태 저장
uint8_t Sub_Motor_Run_Mode[Sub_Relay_Num][6]; // 현재 모터 동작 상태 저장
uint8_t Sub_Relay_state[Sub_Relay_Num];

uint8_t TB_UI_set = 0;
uint8_t Sub_TB_R_Data[Sub_TB_R_length] ;
uint8_t Sub_TB_S_Data[Sub_TB_S_length] ;
uint8_t Sub_TB_state;

uint8_t EB_UI_set = 0;
uint8_t Sub_EB_R_Data[Sub_EB_R_length] ;
uint8_t Sub_EB_S_Data[Sub_EB_S_length] ;
uint8_t Sub_EB_state;

int buzzer_cnt = 0, Main_buzzer_cnt = 0;
uint8_t LED_On_State;
int Err_Cnt[3];

uint8_t UI_Read_Complete = 0;

#define Err_Num		5
uint8_t MCC_Err_Cnt[Err_Num];
uint8_t MCC_Relay_Err_Cnt[Err_Num];
uint8_t TB_Err_Cnt[Err_Num];
uint8_t DO24_Err_Cnt[Err_Num];
uint8_t EBC_Err_Cnt[Err_Num];

uint8_t MCC_Err;
uint8_t MCC_Relay_Err;
uint8_t TB_Err;
uint8_t DO24_Err;
uint8_t EBC_Err;

int Sum_tmp = 0;

uint8_t Bat_state, AC_State, Balsin_State;

#define Version_SW		0
#define Version_MCC_1	1
#define Version_MCC_2	2
#define Version_MCC_3	3
#define Version_MCC_R_1	4
#define Version_MCC_R_2	5
#define Version_MCC_R_3	6
#define Version_TB		7
#define Version_DO_1	8
#define Version_DO_2	9
#define Version_DO_3	10
#define Version_DO_4	11
#define Version_DO_5	12
#define Version_EBC		13

uint8_t Version_Info[14][15];

uint8_t Pre_LED_Data_Set[Sub_MCC_Num][5];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_TIM1_Init(void);
static void MX_IWDG_Init(void);
static void MX_LPUART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM15_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

///////////////Start timer interrupt operation function///////////////////

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1)
  {
    HAL_GPIO_TogglePin(RUN_LED_GPIO_Port, RUN_LED_Pin);

    HAL_IWDG_Refresh(&hiwdg);

  }
  else if(htim->Instance == TIM2)
  {
	  Check_Sw();
  }
  else if(htim->Instance == TIM3)
  {
	  Buzzer_Controll();
  }
  else if(htim->Instance == TIM15)
  {
	  HAL_TIM_OC_Stop_IT(&htim15,TIM_CHANNEL_1);
	  HAL_GPIO_WritePin(BUZZER_3_GPIO_Port, BUZZER_3_Pin, GPIO_PIN_RESET);
  }
  else if(htim->Instance == TIM16)
  {
	if(LED_On_State >= 4){
		LED_On_State = 0;
	}
	else if((LED_On_State >= 2)&(LED_On_State < 4)){
		All_LED_ON();
		LED_On_State ++;
	}
	else if((LED_On_State >= 0)&(LED_On_State < 2)){
		All_LED_OFF();
		LED_On_State++;
	}
  }


}
////////////////Timer interrupt operation function ends ///////////////////

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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USB_PCD_Init();
  MX_TIM1_Init();
  MX_IWDG_Init();
  MX_LPUART2_UART_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  // Timer1: 1 second cycle
  // Timer2: 0.1 second cycle
  // Timer3: 1 second cycle
  HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim16,TIM_CHANNEL_1);

  Compile_Date();

  LED_Test();

  Read_Sub_Version();

  Sw_Buzzer_On();

  Sub_MCC_Set_Num = 1;
  Sub_Relay_Set_Num = 1;

  for(int i=0; i<Err_Num; i++ ){
	  MCC_Err_Cnt[i] = 0;
	  MCC_Relay_Err_Cnt[i] = 0;
	  TB_Err_Cnt[i] = 0;
	  DO24_Err_Cnt[i] = 0;
	  EBC_Err_Cnt[i] = 0;
  }


  /* hlpuart2 RX Interrupt  Enable */
  /* Process Unlocked */
  __HAL_UNLOCK(&hlpuart2);
  /* Enable the UART Parity Error Interrupt */
  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_PE);
  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_ERR);
  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_RXNE);

  /* huart1 RX Interrupt  Enable */
  /* Process Unlocked */
  __HAL_UNLOCK(&huart1);
  /* Enable the UART Parity Error Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_PE);
  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);

  Read_Sub_Version();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_ERR);
	  /* Enable the UART Data Register not empty Interrupt */
	  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_RXNE);

	  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
	  /* Enable the UART Data Register not empty Interrupt */
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);


	  Read_MCC();
	  Read_MCC_Relay();
	  Read_TB();
	  Read_DO24();
	  Read_EBC();

	  Set_Int_LED();
	  /*
	  for(int i=1; i<14;i++){
		  Read_Version_Status(i);
	  }
	  */

	  //Read_Sub_Version();

	  UI_Com_SW_r();

	  for(int i=0;i<300;i++){
		  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_ERR);
		  /* Enable the UART Data Register not empty Interrupt */
		  __HAL_UART_ENABLE_IT(&hlpuart2, UART_IT_RXNE);

	   UI_Check();
	   if(UI_Read_Complete == 1){
		   UI_Read_Complete = 0;
		   break;
	   }
	   HAL_Delay(1);
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 7;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_16;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  hiwdg.Init.EWI = 0;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief LPUART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART2_UART_Init(void)
{

  /* USER CODE BEGIN LPUART2_Init 0 */

  /* USER CODE END LPUART2_Init 0 */

  /* USER CODE BEGIN LPUART2_Init 1 */

  /* USER CODE END LPUART2_Init 1 */
  hlpuart2.Instance = LPUART2;
  hlpuart2.Init.BaudRate = 115200;
  hlpuart2.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart2.Init.StopBits = UART_STOPBITS_1;
  hlpuart2.Init.Parity = UART_PARITY_NONE;
  hlpuart2.Init.Mode = UART_MODE_TX_RX;
  hlpuart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart2.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART2_Init 2 */

  /* USER CODE END LPUART2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 5599;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 5599;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
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
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 5599;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 5599;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 1999;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */

  /* USER CODE END TIM15_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 5599;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 1999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim16, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hpcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hpcd_USB_DRD_FS.Init.speed = USBD_FS_SPEED;
  hpcd_USB_DRD_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_DRD_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BUZZER_1_Pin|BUZZER_2_Pin|BUZZER_3_Pin|SW_LED6_Pin
                          |LOCAL_BELL_LED_Pin|SUB_BELL_LED_Pin|FIRE_LED_Pin|RUN_LED_Pin
                          |ERR_LED_Pin|BAT_ERR_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EMERGENCY_LED_GPIO_Port, EMERGENCY_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SIREN_LED_Pin|SW_LED5_Pin|SW_LED4_Pin|SW_LED3_Pin
                          |BALSIN_LED_Pin|AC_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SW_LED2_Pin|MAIN_BELL_LED_Pin|SW_LED1_Pin|UART1_DE_Pin
                          |UART1_RE_Pin|MENU_POPUP_LED_Pin|RX_LED_Pin|TX_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PHONE_LED_GPIO_Port, PHONE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BUZZER_1_Pin BUZZER_2_Pin BUZZER_3_Pin SW_LED6_Pin
                           LOCAL_BELL_LED_Pin SUB_BELL_LED_Pin FIRE_LED_Pin RUN_LED_Pin
                           ERR_LED_Pin BAT_ERR_LED_Pin */
  GPIO_InitStruct.Pin = BUZZER_1_Pin|BUZZER_2_Pin|BUZZER_3_Pin|SW_LED6_Pin
                          |LOCAL_BELL_LED_Pin|SUB_BELL_LED_Pin|FIRE_LED_Pin|RUN_LED_Pin
                          |ERR_LED_Pin|BAT_ERR_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : EMERGENCY_STOP_Pin */
  GPIO_InitStruct.Pin = EMERGENCY_STOP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EMERGENCY_STOP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EMERGENCY_LED_Pin */
  GPIO_InitStruct.Pin = EMERGENCY_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EMERGENCY_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SW6_Pin LOCAL_BELL_STOP_Pin SUB_BELL_STOP_Pin MENU_POPUP_Pin */
  GPIO_InitStruct.Pin = SW6_Pin|LOCAL_BELL_STOP_Pin|SUB_BELL_STOP_Pin|MENU_POPUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SIREN_LED_Pin SW_LED5_Pin SW_LED4_Pin SW_LED3_Pin
                           BALSIN_LED_Pin AC_LED_Pin */
  GPIO_InitStruct.Pin = SIREN_LED_Pin|SW_LED5_Pin|SW_LED4_Pin|SW_LED3_Pin
                          |BALSIN_LED_Pin|AC_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SIREN_STOP_Pin SW5_Pin SW4_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SIREN_STOP_Pin|SW5_Pin|SW4_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_LED2_Pin MAIN_BELL_LED_Pin SW_LED1_Pin UART1_DE_Pin
                           UART1_RE_Pin MENU_POPUP_LED_Pin RX_LED_Pin TX_LED_Pin */
  GPIO_InitStruct.Pin = SW_LED2_Pin|MAIN_BELL_LED_Pin|SW_LED1_Pin|UART1_DE_Pin
                          |UART1_RE_Pin|MENU_POPUP_LED_Pin|RX_LED_Pin|TX_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin MAIN_BELL_STOP_Pin SW1_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|MAIN_BELL_STOP_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PHONE_JACK_Pin LOCAL_PHONE_Pin */
  GPIO_InitStruct.Pin = PHONE_JACK_Pin|LOCAL_PHONE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PHONE_LED_Pin */
  GPIO_InitStruct.Pin = PHONE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PHONE_LED_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */



void LED_Test(void){

  RX_LED(LED_Off);
  TX_LED(LED_Off);
  Err_LED(LED_Off);

  FIRE_LED(LED_Off);
  BALSIN_LED(LED_Off);
  AC_LED(LED_Off);
  BAT_ERR_LED(LED_Off);
  PHONE_LED(LED_Off);

  MENU_POPUP_LED(LED_Off);
  MAIN_BELL_LED(LED_Off);
  SUB_BELL_LED(LED_Off);
  LOCAL_BELL_LED(LED_Off);

  SIREN_LED(LED_Off);
  EMERGENCY_LED(LED_Off);
  SW_LED1(LED_Off);
  SW_LED2(LED_Off);
  SW_LED3(LED_Off);
  SW_LED4(LED_Off);
  SW_LED5(LED_Off);
  SW_LED6(LED_Off);

  HAL_Delay(300);

  RX_LED(LED_On);
  TX_LED(LED_On);
  Err_LED(LED_On);

  FIRE_LED(LED_On);
  BALSIN_LED(LED_On);
  AC_LED(LED_On);
  BAT_ERR_LED(LED_On);
  PHONE_LED(LED_On);

  MENU_POPUP_LED(LED_On);
  MAIN_BELL_LED(LED_On);
  SUB_BELL_LED(LED_On);
  LOCAL_BELL_LED(LED_On);

  SIREN_LED(LED_On);
  EMERGENCY_LED(LED_On);
  SW_LED1(LED_On);
  SW_LED2(LED_On);
  SW_LED3(LED_On);
  SW_LED4(LED_On);
  SW_LED5(LED_On);
  SW_LED6(LED_On);

  HAL_Delay(300);

  RX_LED(LED_Off);
  TX_LED(LED_Off);
  Err_LED(LED_Off);

  FIRE_LED(LED_Off);
  BALSIN_LED(LED_Off);
  AC_LED(LED_Off);
  BAT_ERR_LED(LED_Off);
  PHONE_LED(LED_Off);

  MENU_POPUP_LED(LED_Off);
  MAIN_BELL_LED(LED_Off);
  SUB_BELL_LED(LED_Off);
  LOCAL_BELL_LED(LED_Off);

  SIREN_LED(LED_Off);
  EMERGENCY_LED(LED_Off);
  SW_LED1(LED_Off);
  SW_LED2(LED_Off);
  SW_LED3(LED_Off);
  SW_LED4(LED_Off);
  SW_LED5(LED_Off);
  SW_LED6(LED_Off);
}
void Run_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(RUN_LED_GPIO_Port, RUN_LED_Pin, GPIO_PIN_RESET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(RUN_LED_GPIO_Port, RUN_LED_Pin, GPIO_PIN_SET);
	  }
}

void Err_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET);
	  }
}

void RX_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(RX_LED_GPIO_Port, RX_LED_Pin, GPIO_PIN_RESET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(RX_LED_GPIO_Port, RX_LED_Pin, GPIO_PIN_SET);
	  }
}

void TX_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(TX_LED_GPIO_Port, TX_LED_Pin, GPIO_PIN_RESET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(TX_LED_GPIO_Port, TX_LED_Pin, GPIO_PIN_SET);
	  }
}

void FIRE_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(FIRE_LED_GPIO_Port, FIRE_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(FIRE_LED_GPIO_Port, FIRE_LED_Pin, GPIO_PIN_RESET);
	  }
}

void BALSIN_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(BALSIN_LED_GPIO_Port, BALSIN_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(BALSIN_LED_GPIO_Port, BALSIN_LED_Pin, GPIO_PIN_RESET);
	  }
}

void AC_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(AC_LED_GPIO_Port, AC_LED_Pin, GPIO_PIN_RESET);
	  }
}

void BAT_ERR_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(BAT_ERR_LED_GPIO_Port, BAT_ERR_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(BAT_ERR_LED_GPIO_Port, BAT_ERR_LED_Pin, GPIO_PIN_RESET);
	  }
}

void PHONE_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(PHONE_LED_GPIO_Port, PHONE_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(PHONE_LED_GPIO_Port, PHONE_LED_Pin, GPIO_PIN_RESET);
	  }
}

void MENU_POPUP_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(MENU_POPUP_LED_GPIO_Port, MENU_POPUP_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(MENU_POPUP_LED_GPIO_Port, MENU_POPUP_LED_Pin, GPIO_PIN_RESET);
	  }
}


void MAIN_BELL_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(MAIN_BELL_LED_GPIO_Port, MAIN_BELL_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(MAIN_BELL_LED_GPIO_Port, MAIN_BELL_LED_Pin, GPIO_PIN_RESET);
	  }
}

void SUB_BELL_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SUB_BELL_LED_GPIO_Port, SUB_BELL_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SUB_BELL_LED_GPIO_Port, SUB_BELL_LED_Pin, GPIO_PIN_RESET);
	  }
}

void LOCAL_BELL_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(LOCAL_BELL_LED_GPIO_Port, LOCAL_BELL_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(LOCAL_BELL_LED_GPIO_Port, LOCAL_BELL_LED_Pin, GPIO_PIN_RESET);
	  }
}

void SIREN_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SIREN_LED_GPIO_Port, SIREN_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SIREN_LED_GPIO_Port, SIREN_LED_Pin, GPIO_PIN_RESET);
	  }
}

void EMERGENCY_LED(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(EMERGENCY_LED_GPIO_Port, EMERGENCY_LED_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(EMERGENCY_LED_GPIO_Port, EMERGENCY_LED_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED1(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED1_GPIO_Port, SW_LED1_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED1_GPIO_Port, SW_LED1_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED2(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED2_GPIO_Port, SW_LED2_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED2_GPIO_Port, SW_LED2_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED3(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED3_GPIO_Port, SW_LED3_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED3_GPIO_Port, SW_LED3_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED4(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED4_GPIO_Port, SW_LED4_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED4_GPIO_Port, SW_LED4_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED5(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED5_GPIO_Port, SW_LED5_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED5_GPIO_Port, SW_LED5_Pin, GPIO_PIN_RESET);
	  }
}

void SW_LED6(uint16_t Staus){
	if(Staus == LED_On){
	    HAL_GPIO_WritePin(SW_LED6_GPIO_Port, SW_LED6_Pin, GPIO_PIN_SET);
	  }
	  else if(Staus == LED_Off){
	    HAL_GPIO_WritePin(SW_LED6_GPIO_Port, SW_LED6_Pin, GPIO_PIN_RESET);
	  }
}

void All_LED_ON(void){

	FIRE_LED(FIRE_LED_mode);
	BALSIN_LED(BALSIN_LED_mode);
	AC_LED(AC_LED_mode);
	BAT_ERR_LED(BAT_ERR_mode);
	PHONE_LED(PHONE_LED_mode);

	MENU_POPUP_LED(MENU_POPUP_LED_mode);
	MAIN_BELL_LED(MAIN_BELL_LED_mode);
	SUB_BELL_LED(SUB_BELL_LED_mode);
	LOCAL_BELL_LED(LOCAL_BELL_LED_mode);
	SIREN_LED(SIREN_LED_mode);
	EMERGENCY_LED(EMERGENCY_LED_mode);

	SW_LED1(SW1_SW_mode);
	SW_LED2(SW2_SW_mode);
	SW_LED3(SW3_SW_mode);
	SW_LED4(SW4_SW_mode);
	SW_LED5(SW5_SW_mode);
	SW_LED6(SW6_SW_mode);

}

void All_LED_OFF(void){

	FIRE_LED(LED_Off);
	BALSIN_LED(LED_Off);
	AC_LED(LED_Off);
	BAT_ERR_LED(LED_Off);
	PHONE_LED(LED_Off);

	//MENU_POPUP_LED(LED_Off);
	MAIN_BELL_LED(LED_Off);
	SUB_BELL_LED(LED_Off);
	LOCAL_BELL_LED(LED_Off);
	SIREN_LED(LED_Off);
	EMERGENCY_LED(LED_Off);

	SW_LED1(LED_Off);
	SW_LED2(LED_Off);
	SW_LED3(LED_Off);
	SW_LED4(LED_Off);
	SW_LED5(LED_Off);
	SW_LED6(LED_Off);

}
void Read_Sw(void){

	if(HAL_GPIO_ReadPin(MENU_POPUP_GPIO_Port, MENU_POPUP_Pin) == GPIO_PIN_RESET){
		MENU_POPUP_SW_Save[Save_Num - 1] = 1;
	}
	else{
		MENU_POPUP_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(MAIN_BELL_STOP_GPIO_Port, MAIN_BELL_STOP_Pin) == GPIO_PIN_RESET){
		MAIN_BELL_SW_Save[Save_Num - 1] = 1;
	}
	else{
		MAIN_BELL_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SUB_BELL_STOP_GPIO_Port, SUB_BELL_STOP_Pin) == GPIO_PIN_RESET){
		SUB_BELL_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SUB_BELL_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(LOCAL_BELL_STOP_GPIO_Port, LOCAL_BELL_STOP_Pin) == GPIO_PIN_RESET){
		LOCAL_BELL_SW_Save[Save_Num - 1] = 1;
	}
	else{
		LOCAL_BELL_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SIREN_STOP_GPIO_Port, SIREN_STOP_Pin) == GPIO_PIN_RESET){
		SIREN_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SIREN_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(EMERGENCY_STOP_GPIO_Port, EMERGENCY_STOP_Pin) == GPIO_PIN_RESET){
		EMERGENCY_SW_Save[Save_Num - 1] = 1;
	}
	else{
		EMERGENCY_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == GPIO_PIN_RESET){
		SW1_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW1_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == GPIO_PIN_RESET){
		SW2_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW2_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET){
		SW3_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW3_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_RESET){
		SW4_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW4_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin) == GPIO_PIN_RESET){
		SW5_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW5_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(SW6_GPIO_Port, SW6_Pin) == GPIO_PIN_RESET){
		SW6_SW_Save[Save_Num - 1] = 1;
	}
	else{
		SW6_SW_Save[Save_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(LOCAL_PHONE_GPIO_Port, LOCAL_PHONE_Pin) == GPIO_PIN_RESET){
		Local_phone_mode_Save[Phone_Reas_Num - 1] = 1;
	}
	else{
		Local_phone_mode_Save[Phone_Reas_Num - 1] = 0;
	}

	if(HAL_GPIO_ReadPin(PHONE_JACK_GPIO_Port, PHONE_JACK_Pin) == GPIO_PIN_RESET){
		phone_jack_mode_Save[Phone_Reas_Num - 1] = 1;
	}
	else{
		phone_jack_mode_Save[Phone_Reas_Num - 1] = 0;
	}
}

void Set_Led_Data(int Address){

  PUMP_AUTO_set[Address-1][0] = (LED_Data_Set[Address-1][0] >> 7) & 0x01 ;//-> PUMP1_AUTO
  PUMP_STOP_set[Address-1][0] = (LED_Data_Set[Address-1][0] >> 6) & 0x01 ;//-> PUMP1_STOP
  PUMP_MANUAL_set[Address-1][0] = (LED_Data_Set[Address-1][0] >> 5) & 0x01 ;//-> PUMP1_MANUAL
  PUMP_CHECK_set[Address-1][0] = (LED_Data_Set[Address-1][0] >> 4) & 0x01 ;//-> PUMP1_CHECK
  PUMP_PS_set[Address-1][0] = (LED_Data_Set[Address-1][0] >> 3) & 0x01 ;//-> PUMP1_PS

  PUMP_AUTO_set[Address-1][1] = (LED_Data_Set[Address-1][0] >> 2) & 0x01 ;//-> PUMP2_AUTO
  PUMP_STOP_set[Address-1][1] = (LED_Data_Set[Address-1][0] >> 1) & 0x01 ;//-> PUMP2_STOP
  PUMP_MANUAL_set[Address-1][1] = (LED_Data_Set[Address-1][0] >> 0) & 0x01 ;//-> PUMP2_MANUAL
  PUMP_CHECK_set[Address-1][1] = (LED_Data_Set[Address-1][1] >> 7) & 0x01 ;//-> PUMP2_CHECK
  PUMP_PS_set[Address-1][1] = (LED_Data_Set[Address-1][1] >> 6) & 0x01 ;//-> PUMP2_PS

  PUMP_AUTO_set[Address-1][2] = (LED_Data_Set[Address-1][1] >> 5) & 0x01 ;//-> PUMP3_AUTO
  PUMP_STOP_set[Address-1][2] = (LED_Data_Set[Address-1][1] >> 4) & 0x01 ;//-> PUMP3_STOP
  PUMP_MANUAL_set[Address-1][2] = (LED_Data_Set[Address-1][1] >> 3) & 0x01 ;//-> PUMP3_MANUAL
  PUMP_CHECK_set[Address-1][2] = (LED_Data_Set[Address-1][1] >> 2) & 0x01 ;//-> PUMP3_CHECK
  PUMP_PS_set[Address-1][2] = (LED_Data_Set[Address-1][1] >> 1) & 0x01 ;//-> PUMP3_PS

  PUMP_AUTO_set[Address-1][3] = (LED_Data_Set[Address-1][1] >> 0) & 0x01 ;//-> PUMP4_AUTO
  PUMP_STOP_set[Address-1][3] = (LED_Data_Set[Address-1][2] >> 7) & 0x01 ;//-> PUMP4_STOP
  PUMP_MANUAL_set[Address-1][3] = (LED_Data_Set[Address-1][2] >> 6) & 0x01 ;//-> PUMP4_MANUAL
  PUMP_CHECK_set[Address-1][3] = (LED_Data_Set[Address-1][2] >> 5) & 0x01 ;//-> PUMP4_CHECK
  PUMP_PS_set[Address-1][3] = (LED_Data_Set[Address-1][2] >> 4) & 0x01 ;//-> PUMP4_PS

  PUMP_AUTO_set[Address-1][4] = (LED_Data_Set[Address-1][2] >> 3) & 0x01 ;//-> PUMP5_AUTO
  PUMP_STOP_set[Address-1][4] = (LED_Data_Set[Address-1][2] >> 2) & 0x01 ;//-> PUMP5_STOP
  PUMP_MANUAL_set[Address-1][4] = (LED_Data_Set[Address-1][2] >> 1) & 0x01 ;//-> PUMP5_MANUAL
  PUMP_CHECK_set[Address-1][4] = (LED_Data_Set[Address-1][2] >> 0) & 0x01 ;//-> PUMP5_CHECK
  PUMP_PS_set[Address-1][4] = (LED_Data_Set[Address-1][3] >> 7) & 0x01 ;//-> PUMP5_PS

  PUMP_AUTO_set[Address-1][5] = (LED_Data_Set[Address-1][3] >> 6) & 0x01 ;//-> PUMP6_AUTO
  PUMP_STOP_set[Address-1][5] = (LED_Data_Set[Address-1][3] >> 5) & 0x01 ;//-> PUMP6_STOP
  PUMP_MANUAL_set[Address-1][5] = (LED_Data_Set[Address-1][3] >> 4) & 0x01 ;//-> PUMP6_MANUAL
  PUMP_CHECK_set[Address-1][5] = (LED_Data_Set[Address-1][3] >> 3) & 0x01 ;//-> PUMP6_CHECK
  PUMP_PS_set[Address-1][5] = (LED_Data_Set[Address-1][3] >> 2) & 0x01 ;//-> PUMP6_PS

  //MCC_HANJUN_set[Address-1] = (LED_Data_Set[Address-1][3] >> 1) & 0x01 ;//-> HANJUN
  //MCC_BALJUN_set[Address-1] = (LED_Data_Set[Address-1][3] >> 0) & 0x01 ;//-> BALJUN
  MCC_HANJUN_set[Address-1] = MCC_HANJUN_state ;//-> HANJUN
  MCC_BALJUN_set[Address-1] = MCC_BALJUN_State ;//-> BALJUN
  MCC_SW_LOCK_ON_set[Address-1] = (LED_Data_Set[Address-1][4] >> 7) & 0x01 ;//-> SW_LOCK_ON
  MCC_SW_LOCK_OFF_set[Address-1] = (LED_Data_Set[Address-1][4] >> 6) & 0x01 ;//-> SW_LOCK_OFF
  //MCC_TERMINATION_set[Address] = (LED_Data_Set[Address-1][4] >> 5) & 0x01 ;//-> TERMINATION

  // 한전 발전 정보는 TB보드로 부터 읽어 MCC LED제어와 UI에 보고한다. UI로 부터 제어는 받지 않는다.
}

void Set_Pre_Led_Data(int Address){

  PUMP_AUTO_set[Address-1][0] = (Pre_LED_Data_Set[Address-1][0] >> 7) & 0x01 ;//-> PUMP1_AUTO
  PUMP_STOP_set[Address-1][0] = (Pre_LED_Data_Set[Address-1][0] >> 6) & 0x01 ;//-> PUMP1_STOP
  PUMP_MANUAL_set[Address-1][0] = (Pre_LED_Data_Set[Address-1][0] >> 5) & 0x01 ;//-> PUMP1_MANUAL
  PUMP_CHECK_set[Address-1][0] = (Pre_LED_Data_Set[Address-1][0] >> 4) & 0x01 ;//-> PUMP1_CHECK
  PUMP_PS_set[Address-1][0] = (Pre_LED_Data_Set[Address-1][0] >> 3) & 0x01 ;//-> PUMP1_PS

  PUMP_AUTO_set[Address-1][1] = (Pre_LED_Data_Set[Address-1][0] >> 2) & 0x01 ;//-> PUMP2_AUTO
  PUMP_STOP_set[Address-1][1] = (Pre_LED_Data_Set[Address-1][0] >> 1) & 0x01 ;//-> PUMP2_STOP
  PUMP_MANUAL_set[Address-1][1] = (Pre_LED_Data_Set[Address-1][0] >> 0) & 0x01 ;//-> PUMP2_MANUAL
  PUMP_CHECK_set[Address-1][1] = (Pre_LED_Data_Set[Address-1][1] >> 7) & 0x01 ;//-> PUMP2_CHECK
  PUMP_PS_set[Address-1][1] = (Pre_LED_Data_Set[Address-1][1] >> 6) & 0x01 ;//-> PUMP2_PS

  PUMP_AUTO_set[Address-1][2] = (Pre_LED_Data_Set[Address-1][1] >> 5) & 0x01 ;//-> PUMP3_AUTO
  PUMP_STOP_set[Address-1][2] = (Pre_LED_Data_Set[Address-1][1] >> 4) & 0x01 ;//-> PUMP3_STOP
  PUMP_MANUAL_set[Address-1][2] = (Pre_LED_Data_Set[Address-1][1] >> 3) & 0x01 ;//-> PUMP3_MANUAL
  PUMP_CHECK_set[Address-1][2] = (Pre_LED_Data_Set[Address-1][1] >> 2) & 0x01 ;//-> PUMP3_CHECK
  PUMP_PS_set[Address-1][2] = (Pre_LED_Data_Set[Address-1][1] >> 1) & 0x01 ;//-> PUMP3_PS

  PUMP_AUTO_set[Address-1][3] = (Pre_LED_Data_Set[Address-1][1] >> 0) & 0x01 ;//-> PUMP4_AUTO
  PUMP_STOP_set[Address-1][3] = (Pre_LED_Data_Set[Address-1][2] >> 7) & 0x01 ;//-> PUMP4_STOP
  PUMP_MANUAL_set[Address-1][3] = (Pre_LED_Data_Set[Address-1][2] >> 6) & 0x01 ;//-> PUMP4_MANUAL
  PUMP_CHECK_set[Address-1][3] = (Pre_LED_Data_Set[Address-1][2] >> 5) & 0x01 ;//-> PUMP4_CHECK
  PUMP_PS_set[Address-1][3] = (Pre_LED_Data_Set[Address-1][2] >> 4) & 0x01 ;//-> PUMP4_PS

  PUMP_AUTO_set[Address-1][4] = (Pre_LED_Data_Set[Address-1][2] >> 3) & 0x01 ;//-> PUMP5_AUTO
  PUMP_STOP_set[Address-1][4] = (Pre_LED_Data_Set[Address-1][2] >> 2) & 0x01 ;//-> PUMP5_STOP
  PUMP_MANUAL_set[Address-1][4] = (Pre_LED_Data_Set[Address-1][2] >> 1) & 0x01 ;//-> PUMP5_MANUAL
  PUMP_CHECK_set[Address-1][4] = (Pre_LED_Data_Set[Address-1][2] >> 0) & 0x01 ;//-> PUMP5_CHECK
  PUMP_PS_set[Address-1][4] = (Pre_LED_Data_Set[Address-1][3] >> 7) & 0x01 ;//-> PUMP5_PS

  PUMP_AUTO_set[Address-1][5] = (Pre_LED_Data_Set[Address-1][3] >> 6) & 0x01 ;//-> PUMP6_AUTO
  PUMP_STOP_set[Address-1][5] = (Pre_LED_Data_Set[Address-1][3] >> 5) & 0x01 ;//-> PUMP6_STOP
  PUMP_MANUAL_set[Address-1][5] = (Pre_LED_Data_Set[Address-1][3] >> 4) & 0x01 ;//-> PUMP6_MANUAL
  PUMP_CHECK_set[Address-1][5] = (Pre_LED_Data_Set[Address-1][3] >> 3) & 0x01 ;//-> PUMP6_CHECK
  PUMP_PS_set[Address-1][5] = (Pre_LED_Data_Set[Address-1][3] >> 2) & 0x01 ;//-> PUMP6_PS

  //MCC_HANJUN_set[Address-1] = (Pre_LED_Data_Set[Address-1][3] >> 1) & 0x01 ;//-> HANJUN
  //MCC_BALJUN_set[Address-1] = (Pre_LED_Data_Set[Address-1][3] >> 0) & 0x01 ;//-> BALJUN
  MCC_HANJUN_set[Address-1] = MCC_HANJUN_state ;//-> HANJUN
  MCC_BALJUN_set[Address-1] = MCC_BALJUN_State ;//-> BALJUN
  MCC_SW_LOCK_ON_set[Address-1] = (Pre_LED_Data_Set[Address-1][4] >> 7) & 0x01 ;//-> SW_LOCK_ON
  MCC_SW_LOCK_OFF_set[Address-1] = (Pre_LED_Data_Set[Address-1][4] >> 6) & 0x01 ;//-> SW_LOCK_OFF
  //MCC_TERMINATION_set[Address] = (Pre_LED_Data_Set[Address-1][4] >> 5) & 0x01 ;//-> TERMINATION

  // 한전 발전 정보는 TB보드로 부터 읽어 MCC LED제어와 UI에 보고한다. UI로 부터 제어는 받지 않는다.
}

void Check_Sw(void){

  Pre_MENU_POPUP_SW = MENU_POPUP_SW;
  Pre_MAIN_BELL_SW = MAIN_BELL_SW;
  Pre_SUB_BELL_SW = SUB_BELL_SW;
  Pre_LOCAL_BELL_SW = LOCAL_BELL_SW;
  Pre_SIREN_SW = SIREN_SW;
  Pre_EMERGENCY_SW = EMERGENCY_SW;
  Pre_SW1_SW = SW1_SW;
  Pre_SW2_SW = SW2_SW;
  Pre_SW3_SW = SW3_SW;
  Pre_SW4_SW = SW4_SW;
  Pre_SW5_SW = SW5_SW;
  Pre_SW6_SW = SW6_SW;

  Read_Sw();

  for(int i=0; i<(Save_Num-1); i++){
	  MENU_POPUP_SW_Save[i] = MENU_POPUP_SW_Save[i+1];
	  MAIN_BELL_SW_Save[i] = MAIN_BELL_SW_Save[i+1];
	  SUB_BELL_SW_Save[i] = SUB_BELL_SW_Save[i+1];
	  LOCAL_BELL_SW_Save[i] = LOCAL_BELL_SW_Save[i+1];
	  SIREN_SW_Save[i] = SIREN_SW_Save[i+1];
	  EMERGENCY_SW_Save[i] = EMERGENCY_SW_Save[i+1];
	  SW1_SW_Save[i] = SW1_SW_Save[i+1];
	  SW2_SW_Save[i] = SW2_SW_Save[i+1];
	  SW3_SW_Save[i] = SW3_SW_Save[i+1];
	  SW4_SW_Save[i] = SW4_SW_Save[i+1];
	  SW5_SW_Save[i] = SW5_SW_Save[i+1];
	  SW6_SW_Save[i] = SW6_SW_Save[i+1];
  }

  MENU_POPUP_SW_Sum = 0;
  MAIN_BELL_SW_Sum = 0;
  SUB_BELL_SW_Sum = 0;
  LOCAL_BELL_SW_Sum = 0;
  SIREN_SW_Sum = 0;
  EMERGENCY_SW_Sum = 0;
  SW1_SW_Sum = 0;
  SW2_SW_Sum = 0;
  SW3_SW_Sum = 0;
  SW4_SW_Sum = 0;
  SW5_SW_Sum = 0;
  SW6_SW_Sum = 0;

  for(int i=0; i<Save_Num; i++){
	  MENU_POPUP_SW_Sum += MENU_POPUP_SW_Save[i];
	  MAIN_BELL_SW_Sum += MAIN_BELL_SW_Save[i];
	  SUB_BELL_SW_Sum += SUB_BELL_SW_Save[i];
	  LOCAL_BELL_SW_Sum += LOCAL_BELL_SW_Save[i];
	  SIREN_SW_Sum += SIREN_SW_Save[i];
	  EMERGENCY_SW_Sum += EMERGENCY_SW_Save[i];
	  SW1_SW_Sum += SW1_SW_Save[i];
	  SW2_SW_Sum += SW2_SW_Save[i];
	  SW3_SW_Sum += SW3_SW_Save[i];
	  SW4_SW_Sum += SW4_SW_Save[i];
	  SW5_SW_Sum += SW5_SW_Save[i];
	  SW6_SW_Sum += SW6_SW_Save[i];
  }

  if(MENU_POPUP_SW_Sum > (Save_Num/2)){
	  MENU_POPUP_SW = 1;
  }
  else{
	  MENU_POPUP_SW = 0;
  }

  if(MAIN_BELL_SW_Sum > (Save_Num/2)){
	  MAIN_BELL_SW = 1;
  }
  else{
	  MAIN_BELL_SW = 0;
  }

  if(SUB_BELL_SW_Sum > (Save_Num/2)){
	  SUB_BELL_SW = 1;
  }
  else{
	  SUB_BELL_SW = 0;
  }

  if(LOCAL_BELL_SW_Sum > (Save_Num/2)){
	  LOCAL_BELL_SW = 1;
  }
  else{
	  LOCAL_BELL_SW = 0;
  }

  if(SIREN_SW_Sum > (Save_Num/2)){
	  SIREN_SW = 1;
  }
  else{
	  SIREN_SW = 0;
  }

  if(EMERGENCY_SW_Sum > (Save_Num/2)){
	  EMERGENCY_SW = 1;
  }
  else{
	  EMERGENCY_SW = 0;
  }

  if(SW1_SW_Sum > (Save_Num/2)){
	  SW1_SW = 1;
  }
  else{
	  SW1_SW = 0;
  }

  if(SW2_SW_Sum > (Save_Num/2)){
	  SW2_SW = 1;
  }
  else{
	  SW2_SW = 0;
  }

  if(SW3_SW_Sum > (Save_Num/2)){
	  SW3_SW = 1;
  }
  else{
	  SW3_SW = 0;
  }

  if(SW4_SW_Sum > (Save_Num/2)){
	  SW4_SW = 1;
  }
  else{
	  SW4_SW = 0;
  }

  if(SW5_SW_Sum > (Save_Num/2)){
	  SW5_SW = 1;
  }
  else{
	  SW5_SW = 0;
  }

  if(SW6_SW_Sum > (Save_Num/2)){
	  SW6_SW = 1;
  }
  else{
	  SW6_SW = 0;
  }

  if((Pre_MENU_POPUP_SW == 0)&(MENU_POPUP_SW == 1)){
	  inf_SWI_sub[5] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_MAIN_BELL_SW == 0)&(MAIN_BELL_SW == 1)){
	  inf_SWI_sub[4] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SUB_BELL_SW == 0)&(SUB_BELL_SW == 1)){
	  inf_SWI_sub[3] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_LOCAL_BELL_SW == 0)&(LOCAL_BELL_SW == 1)){
	  inf_SWI_sub[2] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SIREN_SW == 0)&(SIREN_SW == 1)){
	  inf_SWI_sub[1] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_EMERGENCY_SW == 0)&(EMERGENCY_SW == 1)){
	  inf_SWI_sub[0] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW1_SW == 0)&(SW1_SW == 1)){
	  user_SWI_sub[5] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW2_SW == 0)&(SW2_SW == 1)){
	  user_SWI_sub[4] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW3_SW == 0)&(SW3_SW == 1)){
	  user_SWI_sub[3] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW4_SW == 0)&(SW4_SW == 1)){
	  user_SWI_sub[2] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW5_SW == 0)&(SW5_SW == 1)){
	  user_SWI_sub[1] = 1;
	  Sw_Buzzer_On();
  }

  if((Pre_SW6_SW == 0)&(SW6_SW == 1)){
	  user_SWI_sub[0] = 1;
	  Sw_Buzzer_On();
  }


  for(int i=0; i<(Phone_Reas_Num-1); i++){
	  Local_phone_mode_Save[i] = Local_phone_mode_Save[i+1];
	  phone_jack_mode_Save[i] = phone_jack_mode_Save[i+1];
  }

  Local_phone_mode_Sum = 0;
  phone_jack_mode_Sum = 0;

  for(int i=0; i<Phone_Reas_Num; i++){
	  Local_phone_mode_Sum += Local_phone_mode_Save[i];
	  phone_jack_mode_Sum += phone_jack_mode_Save[i];
  }

  if(Local_phone_mode_Sum > (Phone_Reas_Num/2)){
	  Local_phone_mode = 1;
  }
  else{
	  Local_phone_mode = 0;
  }

  if(phone_jack_mode_Sum > (Phone_Reas_Num/2)){
	  phone_jack_mode = 1;
  }
  else{
	  phone_jack_mode = 0;
  }
}

void Buzzer_Controll(void){

  if( Main_buzzer_mode == 1){
	if(Main_buzzer_cnt  == 0){
	  HAL_GPIO_WritePin(BUZZER_1_GPIO_Port, BUZZER_1_Pin, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(BUZZER_1_GPIO_Port, BUZZER_1_Pin, GPIO_PIN_RESET);
	}

	if(Main_buzzer_cnt > (2 + 2)){
	  Main_buzzer_cnt = -1;
	}
  }
  else{
	HAL_GPIO_WritePin(BUZZER_1_GPIO_Port, BUZZER_1_Pin, GPIO_PIN_RESET);
  }


  if(Sub_buzzer1_mode == 1){
	if((buzzer_cnt == 0) | (buzzer_cnt == 2)){
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_RESET);
	}

	if(buzzer_cnt > (4 + 2) ){
	  buzzer_cnt = -1;
	}
  }
  else if(Sub_buzzer2_mode == 1){
	if((buzzer_cnt == 0) | (buzzer_cnt == 2) | (buzzer_cnt == 4)){
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_RESET);
	}

	if(buzzer_cnt > (6 + 2) ){
	  buzzer_cnt = -1;
	}
  }
  else if(Sub_buzzer3_mode == 1){
	HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_SET);

	if(buzzer_cnt > (10 + 2) ){
	  buzzer_cnt = -1;
	}
  }
  else if(Sub_buzzer4_mode == 1){
	if((buzzer_cnt == 0) | (buzzer_cnt == 2) | (buzzer_cnt == 4) | (buzzer_cnt == 6)){
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_RESET);
	}

	if(buzzer_cnt > (10 + 2) ){
	  buzzer_cnt = -1;
	}
  }
  else{
	HAL_GPIO_WritePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin, GPIO_PIN_RESET);
  }
  //HAL_GPIO_TogglePin(BUZZER_2_GPIO_Port, BUZZER_2_Pin);
  Main_buzzer_cnt++;
  buzzer_cnt++;

}

void Sw_Buzzer_On(void){
	HAL_TIM_OC_Start_IT(&htim15,TIM_CHANNEL_1);
	HAL_GPIO_WritePin(BUZZER_3_GPIO_Port, BUZZER_3_Pin, GPIO_PIN_SET);
}

void UI_Com_SW_r(void){

  uint8_t	UI_Uart_crc = 0;

  TX_LED(LED_On);

  UI_UART_TX_buf[0] = 0x53;    //S
  UI_UART_TX_buf[1] = 0x54;    //T
  UI_UART_TX_buf[2] = 0x53;    //S
  UI_UART_TX_buf[3] = 0x72;    //r
  UI_UART_TX_buf[4] = 0x00;

  for(int i = 0; i <UI_UART_R_Length - 5 ; i++){
	UI_Uart_crc = UI_Uart_crc ^ UI_UART_TX_buf[i+2];
  }

  UI_UART_TX_buf[5] = UI_Uart_crc;

  UI_UART_TX_buf[6] = 0x45;
  UI_UART_TX_buf[7] = 0x44;
  if(HAL_UART_Transmit(&hlpuart2, UI_UART_TX_buf, UI_UART_R_Length, 1000)!= HAL_OK)
  {
    Error_Handler();
  }

  TX_LED(LED_Off);

}

void UI_Com(void){

  // CRC 체크
  uint8_t UI_Uart_crc = 0;

  // 전송할 중계기 정보를 확인한다

  if((UI_UART_RX_buf[3] == 0x53)&(UI_UART_RX_buf[4] == 0x4D)){
	  TX_LED(LED_Off);
  }
  for(int i = 0; i <UI_UART_buf_count_Save - 5 ; i++){
	  UI_Uart_crc = UI_Uart_crc ^ UI_UART_RX_buf[i+2];
  }

  if(UI_Uart_crc == UI_UART_RX_buf[UI_UART_buf_count_Save - 3]){

    if(UI_UART_RX_buf[3] == 0x51){//0x51 , 'Q' , 정보 요청 (UI에서 설정한 값만)

      if(UI_UART_RX_buf[4] == 0x41){
       UI_Com_All_Q();		//0x41 , 'A' ,All board
      }
      else if(UI_UART_RX_buf[4] == 0x53){
         UI_Com_SW_Q();		//0x53 , 'S' Switch board 정보
      }
      else if(UI_UART_RX_buf[4] == 0x4D){
    	  for(int i=1;i<(Sub_MCC_Set_Num +1 );i++){	//0x4D , 'Q' MCC board 정보
			if(Sub_MCC_state[i - 1] == 1){

			}
			UI_Com_MCC_Q(i);
		  }
      }
      else if(UI_UART_RX_buf[4] == 0x52){
    	  UI_Com_Relay_Q(1);		//0x52 , 'R' MCC Relay board 정보
      }
      else if(UI_UART_RX_buf[4] == 0x44){
    	  UI_Com_DO24_Q(1);		//0x44 , 'D' DO24 board 정보
      }
      else if(UI_UART_RX_buf[4] == 0x54){
    	  UI_Com_TB_Q();		//0x54 , 'T' TB board 정보
      }
      else if(UI_UART_RX_buf[4] == 0x42){
    	  UI_Com_EB_Q();		//0x42 , 'B' EBC board 정보
      }
      else if(UI_UART_RX_buf[4] == 0x57){
    	  UI_Com_SW2_Q();		//0x57 , 'W' SW2 board 정보
      }

    }
    else if(UI_UART_RX_buf[3] == 0x53){ //0x53 , 'S' , 설정 요

        if(UI_UART_RX_buf[4] == 0x41){
         UI_Com_All_S();		//0x41 , 'A' ,All board
        }
        else if(UI_UART_RX_buf[4] == 0x53){
           UI_Com_SW_S();		//0x53 , 'S' Switch board 정보
        }
        else if(UI_UART_RX_buf[4] == 0x4D){
          //UI_Com_MCC_S(UI_UART_RX_buf[5]);		//0x4C , 'M' ,MCC board 정보
          //HAL_Delay(20);
          //UI_Com_MCC_S(UI_UART_RX_buf[5]);		//0x4C , 'M' ,MCC board 정보
          //HAL_Delay(20);
          //UI_Com_MCC_Q(UI_UART_RX_buf[5]);
        }
        else if(UI_UART_RX_buf[4] == 0x52){
          //UI_Com_Relay_S();	//0x52 , 'R' ,Relay board 설정
        }
        else if(UI_UART_RX_buf[4] == 0x44){

          UI_Com_DO24_S();		//0x44 , 'D' ,DO24 board 설정
           UI_Com_DO24_Q(UI_UART_RX_buf[5]);

        }
        else if(UI_UART_RX_buf[4] == 0x54){
          UI_Com_TB_S();	//0x54 , 'T' ,TB board 설정
        }
        else if(UI_UART_RX_buf[4] == 0x42){
          UI_Com_EB_S();	//0x42 , 'B' ,EB board 설정
        }
        else if(UI_UART_RX_buf[4] == 0x57){
		   UI_Com_SW2_S();		//0x57 , 'W' Switch2 board 설정
		}
    }
    else if(UI_UART_RX_buf[3] == 0x45){
    	UI_Read_Complete = 1;
    }
    else if(UI_UART_RX_buf[3] == 0x56){ //0x56 , V' ,버전 정보

    	UI_Com_V();
    	Read_Sub_Version();

    }
  }


  UI_UART_Receive_complete = 0;
  UI_UART_buf_count_Save = 0;

  for(int k=0;k<UI_UART_buf_len;k++){
	  UI_UART_RX_buf[k] = 0;
  }

}


void UI_Com_All_Q(void){}

void UI_Com_SW_Q(void){

  // CRC 체크
  uint8_t UI_Uart_crc = 0;

  TX_LED(LED_On);
  Read_Sw_LTD_Status();

  UI_UART_TX_buf[0] = 0x53;    //S
  UI_UART_TX_buf[1] = 0x54;    //T
  UI_UART_TX_buf[2] = 0x53;    //S
  UI_UART_TX_buf[3] = 0x71;    //q
  UI_UART_TX_buf[4] = 0x53;    //S
  UI_UART_TX_buf[5] = inf_LED;
  UI_UART_TX_buf[6] = inf_SWI;
  UI_UART_TX_buf[7] = inf_Other;

  for(int i = 0; i <UI_Com_SW_Q_Length - 5 ; i++){
	UI_Uart_crc = UI_Uart_crc ^ UI_UART_TX_buf[i+2];
  }

  UI_UART_TX_buf[8] = UI_Uart_crc;
  UI_UART_TX_buf[9] = 0x45;
  UI_UART_TX_buf[10] = 0x44;

  if(HAL_UART_Transmit(&hlpuart2, UI_UART_TX_buf, UI_Com_SW_Q_Length, 1000)!= HAL_OK)
  {
    Error_Handler();
  }

  for(int i=0;i<8;i++){
    inf_SWI_sub[i] = 0;
    inf_Other_sub[i]=0;
//    user_SWI_sub[i]=0;
  }

  TX_LED(LED_Off);
}

void UI_Com_SW2_Q(void){

  // CRC 체크
  uint8_t UI_Uart_crc = 0;

  TX_LED(LED_On);
  Read_Sw_LTD_Status();

  UI_UART_TX_buf[0] = 0x53;    //S
  UI_UART_TX_buf[1] = 0x54;    //T
  UI_UART_TX_buf[2] = 0x53;    //S
  UI_UART_TX_buf[3] = 0x71;    //q
  UI_UART_TX_buf[4] = 0x78;    //w
  UI_UART_TX_buf[5] = user_LED;
  UI_UART_TX_buf[6] = user_SWI;
  UI_UART_TX_buf[7] = 0;

  for(int i = 0; i <UI_Com_SW_Q_Length - 5 ; i++){
	UI_Uart_crc = UI_Uart_crc ^ UI_UART_TX_buf[i+2];
  }

  UI_UART_TX_buf[8] = UI_Uart_crc;
  UI_UART_TX_buf[9] = 0x45;
  UI_UART_TX_buf[10] = 0x44;

  if(HAL_UART_Transmit(&hlpuart2, UI_UART_TX_buf, UI_Com_SW_Q_Length, 1000)!= HAL_OK)
  {
    Error_Handler();
  }

  for(int i=0;i<8;i++){
    user_SWI_sub[i]=0;
  }

  TX_LED(LED_Off);
}

void UI_Com_Relay_Q(int Address){

#define  Uart1_length_Relay  16
int i;
uint8_t UART_TX_buf[Uart1_length_Relay] , UART_Crc;

TX_LED(GPIO_PIN_RESET);

for(i=0;i<Uart1_length_Relay;i++){
  UART_TX_buf[i] = 0;
}

Sub_Relay_R_Data[Address -1 ][Sub_Relay_R_length - 5] = Sub_Relay_state[Address -1 ];


UART_TX_buf[0] = 0x53;    //S
UART_TX_buf[1] = 0x54;    //T
UART_TX_buf[2] = 0x53;    //S
UART_TX_buf[3] = 0x71;    //q

UART_TX_buf[4] = 0x52;      //Relay board : '0x52'
UART_TX_buf[5] = Address;

for(i=6;i<Uart1_length_Relay;i++){
  UART_TX_buf[i] = Sub_Relay_R_Data[Address -1 ][i-1];
}

UART_TX_buf[Uart1_length_Relay - 4] = 0;

UART_Crc = 0;

for(i = 0; i <(Uart1_length_Relay - 5) ; i++){
  UART_Crc = UART_Crc^ UART_TX_buf[i + 2];
}

UART_TX_buf[Uart1_length_Relay - 3] = UART_Crc;

UART_TX_buf[Uart1_length_Relay - 2] = 0x45;
UART_TX_buf[Uart1_length_Relay - 1] = 0x44;

if(HAL_UART_Transmit(&hlpuart2, UART_TX_buf, sizeof(UART_TX_buf), 1000)!= HAL_OK)
{
  Error_Handler();
}
}

void UI_Com_DO24_Q(int Address){

#define  Uart1_length_DO24  15
int i;
uint8_t UART_TX_buf[Uart1_length_DO24] , UART_Crc;

TX_LED(GPIO_PIN_RESET);

for(i=0;i<Uart1_length_DO24;i++){
  UART_TX_buf[i] = 0;
}

UART_TX_buf[0] = 0x53;    //S
UART_TX_buf[1] = 0x54;    //T
UART_TX_buf[2] = 0x53;    //S
UART_TX_buf[3] = 0x71;    //q
UART_TX_buf[4] = 0x44;      //DO24 boaed : '0x44'
UART_TX_buf[5] = Address;



for(i=0;i<5;i++){
  UART_TX_buf[i+6] = Sub_DO24_R_Data[Address -1 ][i+5];
}

UART_TX_buf[10] = Sub_DO24_state[Address -1 ];

UART_Crc = 0;


for(i = 0; i <(Uart1_length_DO24 - 5) ; i++){
  UART_Crc = UART_Crc^ UART_TX_buf[i + 2];
}

UART_TX_buf[Uart1_length_DO24 - 3] = UART_Crc;

UART_TX_buf[Uart1_length_DO24 - 2] = 0x45;
UART_TX_buf[Uart1_length_DO24 - 1] = 0x44;

if(HAL_UART_Transmit(&hlpuart2, UART_TX_buf, sizeof(UART_TX_buf), 1000)!= HAL_OK)
{
  Error_Handler();
}

TX_LED(GPIO_PIN_SET);

}

void UI_Com_TB_Q(void){

	uint8_t UART_Crc,Uart_length;
	Uart_length = UI_Q_length_TB;

	TX_LED(GPIO_PIN_RESET);

	SUB_UART_RX_buf[0] = 0x53;    //S
	SUB_UART_RX_buf[1] = 0x54;    //T
	SUB_UART_RX_buf[2] = 0x53;    //S
	SUB_UART_RX_buf[3] = 0x71;    //q

	SUB_UART_RX_buf[4] = 0x54;      //TB board: '0x54'


	for(int i=0;i<(Uart_length - 7);i++){
		SUB_UART_RX_buf[i+5] = Sub_TB_R_Data[i+4];
	}

	SUB_UART_RX_buf[Uart_length - 5] = Sub_TB_state;
	//SUB_UART_RX_buf[14] = 0;

	SUB_UART_RX_buf[Uart_length - 4] = Sub_TB_R_Data[14];
	UART_Crc = 0;

	//UART_Crc = Uart1_tx_Header[2]^ Uart1_tx_Header[3];

	for(int i = 0; i <(Uart_length - 5) ; i++){
	  UART_Crc = UART_Crc^ SUB_UART_RX_buf[i + 2];
	}



	SUB_UART_RX_buf[Uart_length - 3] = UART_Crc;

	SUB_UART_RX_buf[Uart_length - 2] = 0x45;
	SUB_UART_RX_buf[Uart_length - 1] = 0x44;

	if(HAL_UART_Transmit(&hlpuart2, SUB_UART_RX_buf, Uart_length, 1000)!= HAL_OK)
	{
	  Error_Handler();
	}

	TX_LED(GPIO_PIN_SET);

}
void UI_Com_EB_Q(void){

#define  Uart1_length_EB  Sub_EB_R_length
int i;
uint8_t UI_UART_TX_buf[Uart1_length_EB] , UART_Crc;

TX_LED(GPIO_PIN_RESET);

UI_UART_TX_buf[0] = 0x53;    //S
UI_UART_TX_buf[1] = 0x54;    //T
UI_UART_TX_buf[2] = 0x53;    //S
UI_UART_TX_buf[3] = 0x71;    //q

UI_UART_TX_buf[4] = 0x42;      //EB board: '0x42'


for(i=0;i<(Uart1_length_EB - 7);i++){
  UI_UART_TX_buf[i+5] = Sub_EB_R_Data[i+4];
}

UI_UART_TX_buf[Uart1_length_EB - 5] = Sub_EB_state;
UI_UART_TX_buf[Uart1_length_EB - 4] = Sub_EB_R_Data[Uart1_length_EB - 4];

UART_Crc = 0;


for(i = 0; i <(Uart1_length_EB - 5) ; i++){
  UART_Crc = UART_Crc^ UI_UART_TX_buf[i + 2];
}


UI_UART_TX_buf[Uart1_length_EB - 3] = UART_Crc;

UI_UART_TX_buf[Uart1_length_EB - 2] = 0x45;
UI_UART_TX_buf[Uart1_length_EB - 1] = 0x44;

if(HAL_UART_Transmit(&hlpuart2, UI_UART_TX_buf, sizeof(UI_UART_TX_buf), 1000)!= HAL_OK)
{
  Error_Handler();
}

TX_LED(GPIO_PIN_SET);
}

void UI_Com_All_S(void){
	UI_Com_SW_S();

}
void UI_Com_SW_S(void){

  inf_LED  = UI_UART_RX_buf[5];
  inf_Other = UI_UART_RX_buf[7];

  for(int i=0;i<7;i++){
	inf_LED_sub[i] =  (inf_LED >> i) & 0x01;
	inf_Other_sub[i] =  (inf_Other >> i) & 0x01;
  }

  if(inf_LED_sub[6] == 1){
	  FIRE_LED_mode = LED_On;
  }
  else{
	  FIRE_LED_mode = LED_Off;
  }

  if(inf_LED_sub[5] == 1){
	  MENU_POPUP_LED_mode = LED_On;
  }
  else{
	  MENU_POPUP_LED_mode = LED_Off;
  }

  if(inf_LED_sub[4] == 1){
	  MAIN_BELL_LED_mode = LED_On;
  }
  else{
	  MAIN_BELL_LED_mode = LED_Off;
  }

  if(inf_LED_sub[3] == 1){
	  SUB_BELL_LED_mode = LED_On;
  }
  else{
	  SUB_BELL_LED_mode = LED_Off;
  }

  if(inf_LED_sub[2] == 1){
	  LOCAL_BELL_LED_mode = LED_On;
  }
  else{
	  LOCAL_BELL_LED_mode = LED_Off;
  }

  if(inf_LED_sub[1] == 1){
	  SIREN_LED_mode = LED_On;
  }
  else{
	  SIREN_LED_mode = LED_Off;
  }

  if(inf_LED_sub[0] == 1){
	  EMERGENCY_LED_mode = LED_On;
  }
  else{
	  EMERGENCY_LED_mode = LED_Off;
  }

  if(inf_Other_sub[4] == 1){
    Sub_buzzer4_mode = 1;
  }
  else{
    Sub_buzzer4_mode = 0;
  }

  if(inf_Other_sub[3] == 1){
    Sub_buzzer3_mode = 1;
  }
  else{
    Sub_buzzer3_mode = 0;
  }

  if(inf_Other_sub[2] == 1){
    Sub_buzzer2_mode = 1;
  }
  else{
    Sub_buzzer2_mode = 0;
  }

  if(inf_Other_sub[1] == 1){
    Sub_buzzer1_mode = 1;
  }
  else{
    Sub_buzzer1_mode = 0;
  }

  if(inf_Other_sub[0] == 1){
    Main_buzzer_mode = 1;
  }
  else{
    Main_buzzer_mode = 0;
  }

}

void UI_Com_SW2_S(void){

  user_LED  = UI_UART_RX_buf[5];

  for(int i=0;i<7;i++){
	user_LED_sub[i] =  (user_LED >> i) & 0x01;
  }

  if(user_LED_sub[5] == 1){
	  SW1_SW_mode = LED_On;
  }
  else{
	  SW1_SW_mode = LED_Off;
  }

  if(user_LED_sub[4] == 1){
	  SW2_SW_mode = LED_On;
  }
  else{
	  SW2_SW_mode = LED_Off;
  }

  if(user_LED_sub[3] == 1){
	  SW3_SW_mode = LED_On;
  }
  else{
	  SW3_SW_mode = LED_Off;
  }

  if(user_LED_sub[2] == 1){
	  SW4_SW_mode = LED_On;
  }
  else{
	  SW4_SW_mode = LED_Off;
  }

  if(user_LED_sub[1] == 1){
	  SW5_SW_mode = LED_On;
  }
  else{
	  SW5_SW_mode = LED_Off;
  }

  if(user_LED_sub[0] == 1){
	  SW6_SW_mode = LED_On;
  }
  else{
	  SW6_SW_mode = LED_Off;
  }

}

void UI_Com_MCC_S(int Address){

	// Set MCC
	uint8_t Uart_crc = 0;
	uint8_t Uart_length = Sub_MCC_S_length;

	SUB_UART_TX_buf[0] = 0x53;    //S
	SUB_UART_TX_buf[1] = 0x54;    //T
	SUB_UART_TX_buf[2] = 0x53;    //S
	SUB_UART_TX_buf[3] = 0x53;    //S
	SUB_UART_TX_buf[4] = 0x4D;    //M
	SUB_UART_TX_buf[5] = UI_UART_RX_buf[5];    //address
	SUB_UART_TX_buf[6] = UI_UART_RX_buf[6];    //LED정보 1 ~8
	SUB_UART_TX_buf[7] = UI_UART_RX_buf[7];    //LED정보 9 ~16
	SUB_UART_TX_buf[8] = UI_UART_RX_buf[8];    //LED정보 17 ~24
	SUB_UART_TX_buf[9] = UI_UART_RX_buf[9];    //LED정보 25 ~32
	SUB_UART_TX_buf[10] = UI_UART_RX_buf[10];   //LED정보 33 ~40
	SUB_UART_TX_buf[11] = 0x00;   //dummy1
	SUB_UART_TX_buf[12] = 0x00;   //dummy2
	SUB_UART_TX_buf[13] = 0x00;   //CRC
	SUB_UART_TX_buf[14] = 0x45;   //E
	SUB_UART_TX_buf[15] = 0x44;   //D

	if(UI_UART_RX_buf[12] == 0){
	Sub_MCC_Set_Num = 1;
	Sub_Relay_Set_Num = 1;
	}
	else{
	Sub_MCC_Set_Num = UI_UART_RX_buf[12];
	Sub_Relay_Set_Num = UI_UART_RX_buf[12];
	}

	for(int i = 0; i <Uart_length - 5 ; i++){
	Uart_crc = Uart_crc ^ SUB_UART_TX_buf[i+2];
	}
	SUB_UART_TX_buf[Uart_length - 3] = Uart_crc ;

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);

}
void SUB_MCC_S(int Address){

  int Uart_length;

  // Set MCC
  uint8_t Uart_crc = 0;
  Uart_length = Sub_MCC_S_length;

  SUB_UART_TX_buf[0] = 0x53;    //S
  SUB_UART_TX_buf[1] = 0x54;    //T
  SUB_UART_TX_buf[2] = 0x53;    //S
  SUB_UART_TX_buf[3] = 0x53;    //S
  SUB_UART_TX_buf[4] = 0x4D;    //M
  SUB_UART_TX_buf[5] = Address;    //address
  SUB_UART_TX_buf[6] = SUB_UART_RX_buf[6];    //LED정보 1 ~8
  SUB_UART_TX_buf[7] = SUB_UART_RX_buf[7];    //LED정보 9 ~16
  SUB_UART_TX_buf[8] = SUB_UART_RX_buf[8];    //LED정보 17 ~24
  SUB_UART_TX_buf[9] = SUB_UART_RX_buf[9];    //LED정보 25 ~32
  SUB_UART_TX_buf[10] = SUB_UART_RX_buf[10];   //LED정보 33 ~40
  SUB_UART_TX_buf[11] = 0x00;   //dummy1
  SUB_UART_TX_buf[12] = 0x00;   //dummy2
  SUB_UART_TX_buf[13] = 0x00;   //CRC
  SUB_UART_TX_buf[14] = 0x45;   //E
  SUB_UART_TX_buf[15] = 0x44;   //D

  MCC_LED_Set[Address-1][0]  = PUMP_AUTO_set[Address-1][0] ;
  MCC_LED_Set[Address-1][5]  = PUMP_AUTO_set[Address-1][1] ;
  MCC_LED_Set[Address-1][10]  = PUMP_AUTO_set[Address-1][2] ;
  MCC_LED_Set[Address-1][15]  = PUMP_AUTO_set[Address-1][3] ;
  MCC_LED_Set[Address-1][20]  = PUMP_AUTO_set[Address-1][4] ;
  MCC_LED_Set[Address-1][25]  = PUMP_AUTO_set[Address-1][5] ;

  MCC_LED_Set[Address-1][1]  = PUMP_STOP_set[Address-1][0] ;
  MCC_LED_Set[Address-1][6]  = PUMP_STOP_set[Address-1][1] ;
  MCC_LED_Set[Address-1][11]  = PUMP_STOP_set[Address-1][2] ;
  MCC_LED_Set[Address-1][16]  = PUMP_STOP_set[Address-1][3] ;
  MCC_LED_Set[Address-1][21]  = PUMP_STOP_set[Address-1][4] ;
  MCC_LED_Set[Address-1][26]  = PUMP_STOP_set[Address-1][5] ;

  MCC_LED_Set[Address-1][2]  = PUMP_MANUAL_set[Address-1][0] ;
  MCC_LED_Set[Address-1][7]  = PUMP_MANUAL_set[Address-1][1] ;
  MCC_LED_Set[Address-1][12]  = PUMP_MANUAL_set[Address-1][2] ;
  MCC_LED_Set[Address-1][17]  = PUMP_MANUAL_set[Address-1][3] ;
  MCC_LED_Set[Address-1][22]  = PUMP_MANUAL_set[Address-1][4] ;
  MCC_LED_Set[Address-1][27]  = PUMP_MANUAL_set[Address-1][5] ;

  MCC_LED_Set[Address-1][3]  = PUMP_CHECK_set[Address-1][0] ;
  MCC_LED_Set[Address-1][8]  = PUMP_CHECK_set[Address-1][1] ;
  MCC_LED_Set[Address-1][13]  = PUMP_CHECK_set[Address-1][2] ;
  MCC_LED_Set[Address-1][18]  = PUMP_CHECK_set[Address-1][3] ;
  MCC_LED_Set[Address-1][23]  = PUMP_CHECK_set[Address-1][4] ;
  MCC_LED_Set[Address-1][28]  = PUMP_CHECK_set[Address-1][5] ;

  MCC_LED_Set[Address-1][4]  = PUMP_PS_set[Address-1][0] ;
  MCC_LED_Set[Address-1][9]  = PUMP_PS_set[Address-1][1] ;
  MCC_LED_Set[Address-1][14]  = PUMP_PS_set[Address-1][2] ;
  MCC_LED_Set[Address-1][19]  = PUMP_PS_set[Address-1][3] ;
  MCC_LED_Set[Address-1][24]  = PUMP_PS_set[Address-1][4] ;
  MCC_LED_Set[Address-1][29]  = PUMP_PS_set[Address-1][5] ;

  MCC_LED_Set[Address-1][30] = MCC_HANJUN_set[Address-1];
  MCC_LED_Set[Address-1][31] = MCC_BALJUN_set[Address-1];
  MCC_LED_Set[Address-1][32] = MCC_SW_LOCK_ON_set[Address-1];
  MCC_LED_Set[Address-1][33] = MCC_SW_LOCK_OFF_set[Address-1];
  MCC_LED_Set[Address-1][34] = MCC_TERMINATION_set[Address-1];


  SUB_UART_TX_buf[6] = (MCC_LED_Set[Address-1][0] << 7)|(MCC_LED_Set[Address-1][1] << 6)|(MCC_LED_Set[Address-1][2] << 5)|(MCC_LED_Set[Address-1][3] << 4)|
		(MCC_LED_Set[Address-1][4] << 3)|(MCC_LED_Set[Address-1][5] << 2)|(MCC_LED_Set[Address-1][6] << 1)|(MCC_LED_Set[Address-1][7] << 0);
  SUB_UART_TX_buf[7] = (MCC_LED_Set[Address-1][8] << 7)|(MCC_LED_Set[Address-1][9] << 6)|(MCC_LED_Set[Address-1][10] << 5)|(MCC_LED_Set[Address-1][11] << 4)|
		  (MCC_LED_Set[Address-1][12] << 3)|(MCC_LED_Set[Address-1][13] << 2)|(MCC_LED_Set[Address-1][14] << 1)|(MCC_LED_Set[Address-1][15] << 0);
  SUB_UART_TX_buf[8] = (MCC_LED_Set[Address-1][16] << 7)|(MCC_LED_Set[Address-1][17] << 6)|(MCC_LED_Set[Address-1][18] << 5)|(MCC_LED_Set[Address-1][19] << 4)|
		  (MCC_LED_Set[Address-1][20] << 3)|(MCC_LED_Set[Address-1][21] << 2)|(MCC_LED_Set[Address-1][22] << 1)|(MCC_LED_Set[Address-1][23] << 0);
  SUB_UART_TX_buf[9] = (MCC_LED_Set[Address-1][24] << 7)|(MCC_LED_Set[Address-1][25] << 6)|(MCC_LED_Set[Address-1][26] << 5)|(MCC_LED_Set[Address-1][27] << 4)|
		  (MCC_LED_Set[Address-1][28] << 3)|(MCC_LED_Set[Address-1][29] << 2)|(MCC_LED_Set[Address-1][30] << 1)|(MCC_LED_Set[Address-1][31] << 0);
  SUB_UART_TX_buf[10] = (MCC_LED_Set[Address-1][32] << 7)|(MCC_LED_Set[Address-1][33] << 6)|(MCC_LED_Set[Address-1][34] << 5);

  for(int i = 0; i <Uart_length - 5 ; i++){
	Uart_crc = Uart_crc ^ SUB_UART_TX_buf[i+2];
  }
  SUB_UART_TX_buf[Uart_length - 3] = Uart_crc ;

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);


}

void SUB_MCC_Relay_S(int Address){

	int Uart_length;

	// Set MCC Relay
	uint8_t Uart_crc = 0;
	Uart_length = Sub_Relay_S_length;

	Check_Pump_Run(Address);

	SUB_UART_TX_buf[0] = 0x53;    //S
	SUB_UART_TX_buf[1] = 0x54;    //T
	SUB_UART_TX_buf[2] = 0x53;    //S
	SUB_UART_TX_buf[3] = 0x53;    //S
	SUB_UART_TX_buf[4] = 0x52;    //R
	SUB_UART_TX_buf[5] = Address;    //address
	SUB_UART_TX_buf[6] = 0x00;   //Relay 동작
	SUB_UART_TX_buf[7] = 0x00;   //dummy1
	SUB_UART_TX_buf[8] = 0x00;   //dummy2
	SUB_UART_TX_buf[9] = 0x00;   //CRC
	SUB_UART_TX_buf[10] = 0x45;   //E
	SUB_UART_TX_buf[11] = 0x44;   //D

	for(int i=0;i<6;i++){
		SUB_UART_TX_buf[6] = SUB_UART_TX_buf[6] | ( ( (Sub_Motor_Run_Mode[Address - 1][i] & 0x01) << (7-i) )) ;
	}

	Uart_crc = 0;
	for(int i = 0; i <Uart_length - 5 ; i++){
	Uart_crc = Uart_crc ^ SUB_UART_TX_buf[i+2];
	}
	SUB_UART_TX_buf[Uart_length - 3] = Uart_crc ;

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);

}

void Check_Pump_Run(int Address){
	for(int i=0 ; i< 6; i++){

		Sub_Pre_Motor_Run_Mode[Address-1][i] = Sub_Motor_Run_Mode[Address-1][i];

		if(PUMP_MANUAL_set[Address-1][i] == 1){
			Sub_Motor_Run_Mode[Address-1][i]  = 1;
		}
		else{
			if(PUMP_AUTO_set[Address-1][i]  == 1){
				if(PUMP_PS_set[Address-1][i] == 1){
					Sub_Motor_Run_Mode[Address-1][i]  = 1;
				}
				else{
					if(Sub_Pre_Motor_Run_Mode[Address-1][i] == 1 ){
						if(Auto_Dip[Address-1][i] == 1){
							Sub_Motor_Run_Mode[Address-1][i] = 1;
						}
						else{
							Sub_Motor_Run_Mode[Address-1][i]  = 0;
						}
					}
				}
			}
			else{
				Sub_Motor_Run_Mode[Address-1][i]  = 0;
			}
		}
	}
}

void UI_Com_Relay_S(void){}
void UI_Com_DO24_S(void){

	int Uart_length = Sub_DO24_S_length;

	for(int i=0;i<Uart_length;i++){
		SUB_UART_TX_buf[i] = UI_UART_RX_buf[i];
	}

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);
}

void UI_Com_TB_S(void){

	int Uart_length = Sub_TB_S_length;

	for(int i=0;i<Uart_length;i++){
		SUB_UART_TX_buf[i] = UI_UART_RX_buf[i];
	}

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);
}
void UI_Com_EB_S(void){
	int Uart_length = Sub_EB_S_length;

	for(int i=0;i<Uart_length;i++){
		SUB_UART_TX_buf[i] = UI_UART_RX_buf[i];
	}

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Uart_length, 1000)!= HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);
}



void Read_Sw_LTD_Status(void){

  //Local_phone_mode = Read_Local_phone();
  //phone_jack_mode = Read_phone_jack();

  inf_Other_sub[7] = Ext_phpne_mode;
  inf_Other_sub[6] = Local_phone_mode;
  inf_Other_sub[5] = phone_jack_mode;
  inf_Other_sub[4] = Sub_buzzer4_mode;
  inf_Other_sub[3] = Sub_buzzer3_mode;
  inf_Other_sub[2] = Sub_buzzer2_mode;
  inf_Other_sub[1] = Sub_buzzer1_mode;
  inf_Other_sub[0] = Main_buzzer_mode;

  inf_SWI = 0;
  inf_SWI= ((inf_SWI_sub[5] & 0x01) << 5)|((inf_SWI_sub[4] & 0x01) << 4)|((inf_SWI_sub[3] & 0x01) << 3)|
          ((inf_SWI_sub[2] & 0x01) << 2)|((inf_SWI_sub[1] & 0x01) << 1)|((inf_SWI_sub[0] & 0x01) << 0);

  inf_Other = 0;
  inf_Other= ((inf_Other_sub[7] & 0x01) << 7)|((inf_Other_sub[6] & 0x01) << 6)|
              ((inf_Other_sub[5] & 0x01) << 5)|((inf_Other_sub[4] & 0x01) << 4)|((inf_Other_sub[3] & 0x01) << 3)|
              ((inf_Other_sub[2] & 0x01) << 2)|((inf_Other_sub[1] & 0x01) << 1)|((inf_Other_sub[0] & 0x01) << 0);


  user_SWI = 0;
  user_SWI= ((user_SWI_sub[5] & 0x01) << 5)|((user_SWI_sub[4] & 0x01) << 4)|((user_SWI_sub[3] & 0x01) << 3)|
          ((user_SWI_sub[2] & 0x01) << 2)|((user_SWI_sub[1] & 0x01) << 1)|((user_SWI_sub[0] & 0x01) << 0);

}

void UI_Com_MCC_Q(int Address){

  // CRC 체크 UI_Com_MCC_Q_Length
  uint8_t UI_Uart_crc = 0;

  TX_LED(LED_On);

  Sub_MCC_R_Data[Address -1 ][Sub_MCC_R_length - 5] = Sub_MCC_state[Address -1 ];

  UI_UART_TX_buf[0] = 0x53;    //S
  UI_UART_TX_buf[1] = 0x54;    //T
  UI_UART_TX_buf[2] = 0x53;    //S
  UI_UART_TX_buf[3] = 0x71;    //q
  UI_UART_TX_buf[4] = 0x4D;      //MCC board : '0x4D'
  UI_UART_TX_buf[5] = Address;

  for(int i=6;i<UI_Com_MCC_Q_Length;i++){
	  UI_UART_TX_buf[i] = Sub_MCC_R_Data[Address -1 ][i-1];
  }

  UI_UART_TX_buf[UI_Com_MCC_Q_Length - 4] = 0;

  for(int i = 0; i <(UI_Com_MCC_Q_Length - 5) ; i++){
	  UI_Uart_crc = UI_Uart_crc ^ UI_UART_TX_buf[i + 2];
  }

  UI_UART_TX_buf[UI_Com_MCC_Q_Length - 3] = UI_Uart_crc;

  UI_UART_TX_buf[UI_Com_MCC_Q_Length - 2] = 0x45;
  UI_UART_TX_buf[UI_Com_MCC_Q_Length - 1] = 0x44;

  if(HAL_UART_Transmit(&hlpuart2, UI_UART_TX_buf, UI_Com_MCC_Q_Length, 1000)!= HAL_OK)
  {
    Error_Handler();
  }


  TX_LED(LED_Off);
}

void Send_Sub_Requst(uint8_t Command, uint8_t Address){
	uint8_t Uart_crc = 0;
	SUB_UART_TX_buf[0] = 0x53;    //S
	SUB_UART_TX_buf[1] = 0x54;    //T
	SUB_UART_TX_buf[2] = 0x53;    //S
	SUB_UART_TX_buf[3] = 0x51;    //Q
	SUB_UART_TX_buf[4] = Command;    //Command
	SUB_UART_TX_buf[5] = Address;    //address
	SUB_UART_TX_buf[6] = 0x00;   //CRC
	SUB_UART_TX_buf[7] = 0x45;   //E
	SUB_UART_TX_buf[8] = 0x44;   //D

	for(int i = 0; i <Sub_Q_length - 5 ; i++){
		Uart_crc = Uart_crc ^ SUB_UART_TX_buf[i+2];
	}
	SUB_UART_TX_buf[6] = Uart_crc ;

	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);

	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Sub_Q_length, 1000)!= HAL_OK)
	  {
	    Error_Handler();
	  }

	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);
}

void UI_Check(void){
  if(UI_UART_Receive_complete == 1){
	  //HAL_Delay(10);
	 UI_Com();
   }
}

/*
void Read_MCC(void){
  for(int i=1;i<(Sub_MCC_Set_Num +1);i++){

	  for(int k=0; k<5;k++){
		Sub_MCC_state[i-1] = Read_MCC_Status(i);
		if(Sub_MCC_state[i-1]  == 1){
		  break;
		}
		else{
			// Enable the UART Error Interrupt: (Frame error, noise error, overrun error)
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
			// Enable the UART Data Register not empty Interrupt
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		}
		HAL_Delay(1);
	  }
	  Set_Led_Data(i);
	}

  if(Sub_MCC_state[0] == 0){
	  HAL_Delay(1);
  }
}
*/

void Read_MCC(void){

	for(int i=0; i<5 ; i++){
		for(int j=0; j<Sub_MCC_Num; j++){
			Pre_LED_Data_Set[j][i] = LED_Data_Set[j][i];
		}
	}

  for(int i=1;i<(Sub_MCC_Set_Num +1);i++){

	  for(int k=0; k<5;k++){
		Sub_MCC_state[i-1] = Read_MCC_Status(i);
		if(Sub_MCC_state[i-1]  == 1){
		  break;
		}
		else{
			// Enable the UART Error Interrupt: (Frame error, noise error, overrun error)
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
			// Enable the UART Data Register not empty Interrupt
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		}
		HAL_Delay(1);
	  }

	  if(Sub_MCC_state[i] == 0){
		  //HAL_Delay(1);
		  Set_Pre_Led_Data(i);
	  }
	  else{
		  Set_Led_Data(i);
	  }
	}



}

void Read_MCC_Relay(void){


    for(int i=1;i<Sub_Relay_Set_Num +1;i++){
    	for(int k=0; k<5;k++){
    		Sub_Relay_state[i-1] = Read_MCC_R_Status(i);
    		if(Sub_Relay_state[i-1]  == 1){
			  break;
			}
    		else{
    			/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
    			/* Enable the UART Data Register not empty Interrupt */
    			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    		}
    		HAL_Delay(1);
    	}
    	Sum_tmp = 0;
    	for(int i =0; i<6; i++){
    		Sum_tmp += PUMP_STOP_set[0][i] ;
    	}
    	if(Sum_tmp != 0){
    		HAL_Delay(1);
    	}
      SUB_MCC_S(i);
      HAL_Delay(1);
      SUB_MCC_Relay_S(i);    //펌프 설정
      HAL_Delay(1);
    }
}

void Read_TB(void){
	for(int k=0; k<5;k++){
		Sub_TB_state = Read_TB_Status();
		if(Sub_TB_state  == 1){
		  break;
		}
		else{
			/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
			/* Enable the UART Data Register not empty Interrupt */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		}
		HAL_Delay(1);
	}
}


void Read_DO24(void){
  for(int i=1;i<Sub_DO24_Set_Num +1;i++){

	  for(int k=0; k<5;k++){
		  Sub_DO24_state[i-1] = Read_DO24_Status(i);
		if(Sub_DO24_state[i-1]  == 1){
		  break;
		}
		else{
			/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
			/* Enable the UART Data Register not empty Interrupt */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		}
		HAL_Delay(1);
	  }
	}
}

void Read_EBC(void){
	Sub_EB_state = 1;
}

int Read_MCC_Status(int Address){

  int Resp_Suc = 0;
  SUB_UART_Receive_complete = 0;

  uint8_t Uart_crc = 0;

  Send_Sub_Requst(0x4D,  Address);

  for(int i=0;i<Sub_MCC_Wait_cnt;i++){
    if(SUB_UART_Receive_complete == 1){
      break;
    }
    HAL_Delay(1);
  }

  if(SUB_UART_Receive_complete == 1){
      if((SUB_UART_RX_buf[2] == 0x4D)&(SUB_UART_RX_buf[3] == 0x52)&(SUB_UART_RX_buf[4] == Address)){
    	  for(int i = 0; i <(Sub_MCC_R_length - 5) ; i++){
    		  Uart_crc = Uart_crc ^ SUB_UART_RX_buf[i + 2];
    	  }
    	  if(Uart_crc == SUB_UART_RX_buf[Sub_MCC_R_length-3]){
    	      Resp_Suc = 1;
    	      for(int i=0;i<Sub_MCC_R_length;i++){
    	        Sub_MCC_R_Data[Address-1][i] = SUB_UART_RX_buf[i];
    	      }
    	      for(int i=0;i<5;i++){
    	        LED_Data_Set[Address -1][i] = Sub_MCC_R_Data[Address-1][6+i];
    	      }
    	      Auto_Dip_set[Address -1] = Sub_MCC_R_Data[Address-1][11];
    	      for(int i=0;i<6;i++){
    	        Auto_Dip[Address -1][i] = (Auto_Dip_set[Address -1]>>i & 0x01);
    	      }
    	  }
    	  else{
    		  Resp_Suc = 0;
    	  }
      }
  }

  SUB_UART_Receive_complete = 0;
  return Resp_Suc;

}

int Read_MCC_R_Status(int Address){

	int Resp_Suc;
	SUB_UART_Receive_complete = 0;

	uint8_t Uart_length = Sub_Relay_R_length;

	uint8_t Uart_crc = 0;

	Send_Sub_Requst(0x52, Address);

	for(int j=0;j<Sub_MCC_R_Wait_cnt;j++){
		if(SUB_UART_Receive_complete == 1){
		  break;
		}
		HAL_Delay(1);
	}

	if(SUB_UART_Receive_complete == 1){
		if((SUB_UART_RX_buf[2] == 0x52)&(SUB_UART_RX_buf[3] == 0x52)&(SUB_UART_RX_buf[4] == Address)){
			for(int i = 0; i <(Sub_MCC_R_R_length - 5) ; i++){
				  Uart_crc = Uart_crc ^ SUB_UART_RX_buf[i + 2];
			  }

			if(Uart_crc == SUB_UART_RX_buf[Sub_MCC_R_R_length-3]){
				Resp_Suc = 1;
				for(int i=0;i<Uart_length;i++){
				  Sub_Relay_R_Data[Address-1][i] = SUB_UART_RX_buf[i];
				}
				SUB_UART_Receive_complete = 0;

				for(int i=0;i<8;i++){
				  PUMP_PS_Pre_set[Address-1][i] = PUMP_PS_set[Address-1][i]; //이전 압력 스위치 값 저장
				  PUMP_PS_set[Address-1][i] = (Sub_Relay_R_Data[Address-1][7] >> (7 - i)) & 0x01 ;
				  PUMP_CHECK_set[Address-1][i] = (Sub_Relay_R_Data[Address-1][8] >> (7 - i)) & 0x01 ;
				}
			}
		}
	}
	else{
		Resp_Suc = 0;
		SUB_UART_Receive_complete = 0;
	}

	for(int i=0;i<Uart_length;i++){
		SUB_UART_RX_buf[i] = 0;
	}
	return Resp_Suc;
}


int Read_TB_Status(void){

  int Sub_TB_state_r;
  uint8_t Uart_crc = 0;

  SUB_UART_Receive_complete = 0;

  Send_Sub_Requst(0x54, 1);

  for(int j=0;j<Sub_TB_Wait_cnt;j++){
    if(SUB_UART_Receive_complete == 1){
      break;
    }
    HAL_Delay(1);
  }

  if(SUB_UART_Receive_complete == 1){
	  if((SUB_UART_RX_buf[2] == 0x54)&(SUB_UART_RX_buf[3] == 0x52)){

		for(int i = 0; i <(Sub_TB_R_length - 5) ; i++){
		  Uart_crc = Uart_crc ^ SUB_UART_RX_buf[i + 2];
		}

		if(Uart_crc == SUB_UART_RX_buf[Sub_TB_R_length-3]){
			Sub_TB_state_r = 1;

			for(int i=0;i<Sub_TB_R_length;i++){
			  Sub_TB_R_Data[i] = SUB_UART_RX_buf[i];
			}
			SUB_UART_Receive_complete = 0;

			if(Sub_TB_R_Data[6] == 0){
				Balsin_State = 0;
			}
			else if(Sub_TB_R_Data[6] == 1){
				Balsin_State = 1;
			}

			if(Sub_TB_R_Data[8] == 0){
				AC_State = 1;
			}
			else if(Sub_TB_R_Data[8] == 1){
				AC_State = 0;
			}

			if(Sub_TB_R_Data[9] <= 100){
				Bat_state = 1;
			}
			else {
				Bat_state = 0;
			}


			if(Sub_TB_R_Data[7] == 0){
			  MCC_HANJUN_state = 0;
			  MCC_BALJUN_State = 0;
			}
			else if(Sub_TB_R_Data[7] == 1){
			  MCC_HANJUN_state = 1;
			  MCC_BALJUN_State = 0;
			}
			else if(Sub_TB_R_Data[7] == 2){
			  MCC_HANJUN_state = 0;
			  MCC_BALJUN_State = 1;
			}
		}
	  }
  }
  else{
	  Sub_TB_state_r = 0;
    SUB_UART_Receive_complete = 0;
  }

  return Sub_TB_state_r;
}

int Read_DO24_Status(int Address){

	int Resp_Suc;
	uint8_t Uart_crc = 0;

	SUB_UART_Receive_complete = 0;

	Send_Sub_Requst(0x44, 1);

	for(int j=0;j<Sub_DO24_Wait_cnt;j++){
		if(SUB_UART_Receive_complete == 1){
		  break;
		}
		HAL_Delay(1);
	}

	if(SUB_UART_Receive_complete == 1){
	//if(SUB_UART_RX_buf[4] == Address){
		if((SUB_UART_RX_buf[2] == 0x44)&(SUB_UART_RX_buf[3] == 0x52)&(SUB_UART_RX_buf[4] == Address)){
			for(int i = 0; i <(Sub_DO24_R_length - 5) ; i++){
			  Uart_crc = Uart_crc ^ SUB_UART_RX_buf[i + 2];
			}

			if(Uart_crc == SUB_UART_RX_buf[Sub_DO24_R_length-3]){
			  for(int i=0;i<Sub_DO24_R_length;i++){
				Sub_DO24_R_Data[Address - 1][i] = SUB_UART_RX_buf[i];
			  }
			  Resp_Suc = 1;
			}
		}
		else{
		Resp_Suc = 0;
		}
	}
	SUB_UART_Receive_complete = 0;
	return Resp_Suc;
}

int Read_Version_Status(int Board_Name){

	int Resp_Suc;
	uint8_t Uart_crc = 0;

	SUB_UART_Receive_complete = 0;

	Send_Sub_Version_Requst(Board_Name);

	for(int j=0;j<5;j++){
		if(SUB_UART_Receive_complete == 1){
		  break;
		}
		else{
			/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
			/* Enable the UART Data Register not empty Interrupt */
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		}
		HAL_Delay(1);
	}

	if(SUB_UART_Receive_complete == 1){
		if((SUB_UART_RX_buf[2] == 0x53)&(SUB_UART_RX_buf[3] == 0x76)){
			for(int i = 0; i <(Sub_V_length - 5) ; i++){
			  Uart_crc = Uart_crc ^ SUB_UART_RX_buf[i + 2];
			}

			if(Uart_crc == SUB_UART_RX_buf[Sub_V_length-3]){
			  for(int i=0;i<Sub_V_length;i++){
				  Version_Info[Board_Name][Sub_V_length] = SUB_UART_RX_buf[i];
			  }
			  Resp_Suc = 1;
			}
		}
		else{
		Resp_Suc = 0;
		}
	}
	SUB_UART_Receive_complete = 0;
	return Resp_Suc;
}

void Send_Sub_Version_Requst(uint8_t Board_Name){

	uint8_t Uart_crc = 0;

	SUB_UART_TX_buf[0] = 0x53;    //S
	SUB_UART_TX_buf[1] = 0x54;    //T
	SUB_UART_TX_buf[2] = 0x53;    //S
	SUB_UART_TX_buf[3] = 0x56;    //V
	SUB_UART_TX_buf[4] = 0;    //Board_Name
	SUB_UART_TX_buf[5] = 0;    //address
	SUB_UART_TX_buf[6] = 0x00;   //CRC
	SUB_UART_TX_buf[7] = 0x45;   //E
	SUB_UART_TX_buf[8] = 0x44;   //D

	if(Board_Name == Version_SW){
		SUB_UART_TX_buf[4] = 0x53;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}
	else if(Board_Name == Version_MCC_1){
		SUB_UART_TX_buf[4] = 0x4D;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}
	else if(Board_Name == Version_MCC_2){
		SUB_UART_TX_buf[4] = 0x4D;    //Board_Name
		SUB_UART_TX_buf[5] = 2;    //address
	}
	else if(Board_Name == Version_MCC_3){
		SUB_UART_TX_buf[4] = 0x4D;    //Board_Name
		SUB_UART_TX_buf[5] = 3;    //address
	}
	else if(Board_Name == Version_MCC_R_1){
		SUB_UART_TX_buf[4] = 0x52;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}
	else if(Board_Name == Version_MCC_R_2){
		SUB_UART_TX_buf[4] = 0x52;    //Board_Name
		SUB_UART_TX_buf[5] = 2;    //address
	}
	else if(Board_Name == Version_MCC_R_3){
		SUB_UART_TX_buf[4] = 0x52;    //Board_Name
		SUB_UART_TX_buf[5] = 3;    //address
	}
	else if(Board_Name == Version_TB){
		SUB_UART_TX_buf[4] = 0x54;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}
	else if(Board_Name == Version_DO_1){
		SUB_UART_TX_buf[4] = 0x44;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}
	else if(Board_Name == Version_DO_2){
		SUB_UART_TX_buf[4] = 0x44;    //Board_Name
		SUB_UART_TX_buf[5] = 2;    //address
	}
	else if(Board_Name == Version_DO_3){
		SUB_UART_TX_buf[4] = 0x44;    //Board_Name
		SUB_UART_TX_buf[5] = 3;    //address
	}
	else if(Board_Name == Version_DO_4){
		SUB_UART_TX_buf[4] = 0x44;    //Board_Name
		SUB_UART_TX_buf[5] = 4;    //address
	}
	else if(Board_Name == Version_DO_5){
		SUB_UART_TX_buf[4] = 0x44;    //Board_Name
		SUB_UART_TX_buf[5] = 5;    //address
	}
	else if(Board_Name == Version_EBC){
		SUB_UART_TX_buf[4] = 0x42;    //Board_Name
		SUB_UART_TX_buf[5] = 1;    //address
	}

	for(int i = 0; i <Sub_Q_length - 5 ; i++){
		Uart_crc = Uart_crc ^ SUB_UART_TX_buf[i+2];
	}
	SUB_UART_TX_buf[6] = Uart_crc ;

	for(int i=0; i<SUB_UART_buf_len; i++){
		SUB_UART_RX_buf[i] = 0;
		}


	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	SUB_UART_Receive_complete = 0;
	if(HAL_UART_Transmit(&huart1, SUB_UART_TX_buf, Sub_Q_length, 1000)!= HAL_OK)
	  {
	    Error_Handler();
	  }

	HAL_Delay(1);
	HAL_GPIO_WritePin(UART1_DE_GPIO_Port , UART1_DE_Pin , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(UART1_RE_GPIO_Port , UART1_RE_Pin , GPIO_PIN_RESET);

	for(int j=0;j<Sub_Version_Wait_cnt;j++){
		if(SUB_UART_Receive_complete == 1){
		  break;
		}
		HAL_Delay(1);
	}

	if(SUB_UART_Receive_complete == 1){
		for(int i=0; i<15; i++){
			Version_Info[Board_Name][i] = SUB_UART_RX_buf[i];
		}
	}
	else{
		Version_Info[Board_Name][0] = SUB_UART_TX_buf[0];    //S
		Version_Info[Board_Name][1] = SUB_UART_TX_buf[1];    //T
		Version_Info[Board_Name][2] = SUB_UART_TX_buf[2];    //S
		Version_Info[Board_Name][3] = 0x76;    //v
		Version_Info[Board_Name][4] = SUB_UART_TX_buf[4];    //Board_Name
		Version_Info[Board_Name][5] = SUB_UART_TX_buf[5];    //address
		Version_Info[Board_Name][6] = 0;    //F_Version_Year
		Version_Info[Board_Name][7] = 0;    //F_Version_Month
		Version_Info[Board_Name][8] = 0;    //F_Version_Day
		Version_Info[Board_Name][9] = 0;    //F_Version_Hour
		Version_Info[Board_Name][10] = 0;    //F_Version_Min
		Version_Info[Board_Name][11] = 0;    //F_Version_Sec
		Version_Info[Board_Name][12] = 0x00;   //CRC
		Version_Info[Board_Name][13] = 0x45;   //E
		Version_Info[Board_Name][14] = 0x44;   //D

		for(int i = 0; i <15 - 5 ; i++){
			Uart_crc = Uart_crc ^ Version_Info[Board_Name][i+2];
		}

		Version_Info[Board_Name][12] = Uart_crc ;
	}

	SUB_UART_Receive_complete = 0;

}

void Read_Sub_Version(void){

	uint8_t Uart_crc = 0;

	Version_Info[0][0] = 0x53;    //S
	Version_Info[0][1] = 0x54;    //T
	Version_Info[0][2] = 0x53;    //S
	Version_Info[0][3] = 0x76;    //v
	Version_Info[0][4] = 0x53;     //SW Board
	Version_Info[0][5] = 0x01;   //ADDRESS
	Version_Info[0][6] = F_Version_Year;
	Version_Info[0][7] = F_Version_Month;
	Version_Info[0][8] = F_Version_Day;
	Version_Info[0][9] = F_Version_Hour;
	Version_Info[0][10] = F_Version_Min;
	Version_Info[0][11] = F_Version_Sec;
	Version_Info[0][12] = 0x00;   //CRC
	Version_Info[0][13] = 0x45;   //E
	Version_Info[0][14] = 0x44;   //D

	for(int i = 0; i <Sub_V_length - 5 ; i++){
		Uart_crc = Uart_crc ^ Version_Info[0][i+2];
	}
	Version_Info[0][12] = Uart_crc ;
/*
	for(int i=1 ; i<14 ; i++){
		Send_Sub_Version_Requst(i);
	}
	*/
	Send_Sub_Version_Requst(1);	//Version_MCC_1
	Send_Sub_Version_Requst(4);	//Version_MCC_R_1
	Send_Sub_Version_Requst(7);	//Version_TB
//	Send_Sub_Version_Requst(8);	//Version_DO_1
//	Send_Sub_Version_Requst(13);	//Version_EBC
}

void UI_Com_V(void){

	if(UI_UART_RX_buf[4] == 0x53){ // Switch board : 'S' '0x53'
		Send_Version_UI_TX(Version_SW);
	}
	else if(UI_UART_RX_buf[4] == 0x4D){ // MCC board : 'M' '0x4D'
		if(UI_UART_RX_buf[5] == 0x01){
			Send_Version_UI_TX(Version_MCC_1);
		}
		else if(UI_UART_RX_buf[5] == 0x02){
			Send_Version_UI_TX(Version_MCC_2);
		}
		else if(UI_UART_RX_buf[5] == 0x03){
			Send_Version_UI_TX(Version_MCC_3);
		}
	}
	else if(UI_UART_RX_buf[4] == 0x52){ // Relay board : 'R' '0x52'
		if(UI_UART_RX_buf[5] == 0x01){
			Send_Version_UI_TX(Version_MCC_R_1);
		}
		else if(UI_UART_RX_buf[5] == 0x02){
			Send_Version_UI_TX(Version_MCC_R_2);
		}
		else if(UI_UART_RX_buf[5] == 0x03){
			Send_Version_UI_TX(Version_MCC_R_3);
		}
	}
	else if(UI_UART_RX_buf[4] == 0x44){ // DO24 boaed : '0x44' '0x44'
		if(UI_UART_RX_buf[5] == 0x01){
			Send_Version_UI_TX(Version_DO_1);
		}
		else if(UI_UART_RX_buf[5] == 0x02){
			Send_Version_UI_TX(Version_DO_2);
		}
		else if(UI_UART_RX_buf[5] == 0x03){
			Send_Version_UI_TX(Version_DO_3);
		}
		else if(UI_UART_RX_buf[5] == 0x04){
			Send_Version_UI_TX(Version_DO_4);
		}
		else if(UI_UART_RX_buf[5] == 0x05){
			Send_Version_UI_TX(Version_DO_5);
		}
	}
	else if(UI_UART_RX_buf[4] == 0x54){ // TB board: '0x54' '0x54'
		Send_Version_UI_TX(Version_TB);
	}
	else if(UI_UART_RX_buf[4] == 0x42){ // EBC board : 'B' '0x42'
		Send_Version_UI_TX(Version_EBC);
	}
}

void Send_Version_UI_TX(uint8_t Board_Name){

	if(HAL_UART_Transmit(&hlpuart2, Version_Info[Board_Name], 15, 1000)!= HAL_OK)
	  {
		Error_Handler();
	  }

}

void Set_Int_LED(void){

  if(phone_jack_mode == 1){
	  PHONE_LED_mode = LED_On;
  }
  else{
	  PHONE_LED_mode = LED_Off;
  }

  if(Bat_state == 1){
	  BAT_ERR_mode = LED_On;
  }
  else{
	  BAT_ERR_mode = LED_Off;
  }

  if(AC_State == 1){
	  AC_LED_mode = LED_On;
  }
  else{
	  AC_LED_mode = LED_Off;
  }

  if(Balsin_State == 1){
	  BALSIN_LED_mode = LED_On;
  }
  else{
	  BALSIN_LED_mode = LED_Off;
  }


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
