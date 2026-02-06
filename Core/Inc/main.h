/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

#define LED_On  1
#define LED_Off 0

# define Sub_Q_length       9

# define Sub_MCC_R_length      17
# define Sub_MCC_S_length      16

# define Sub_Relay_R_length     15
# define Sub_Relay_S_length     12

# define Sub_DO24_R_length      14
# define Sub_DO24_S_length      14

# define Sub_TB_R_length        18
# define Sub_TB_S_length        12

# define Sub_EB_R_length        18
# define Sub_EB_S_length        18

# define Sub_V_length        15

#define Save_Num 5

#define Sub_TB_Wait_cnt 50
#define Sub_DO24_Wait_cnt 15
#define Sub_MCC_Wait_cnt 25
#define Sub_MCC_R_Wait_cnt 15
#define Sub_Version_Wait_cnt 15

#define  UI_Q_length_TB  19

extern uint8_t MENU_POPUP_SW, MENU_POPUP_SW_Save[Save_Num], MENU_POPUP_SW_Sum;
extern uint8_t MAIN_BELL_SW, MAIN_BELL_SW_Save[Save_Num], MAIN_BELL_SW_Sum;
extern uint8_t SUB_BELL_SW, SUB_BELL_SW_Save[Save_Num], SUB_BELL_SW_Sum;
extern uint8_t LOCAL_BELL_SW, LOCAL_BELL_SW_Save[Save_Num], LOCAL_BELL_SW_Sum;
extern uint8_t SIREN_SW, SIREN_SW_Save[Save_Num], SIREN_SW_Sum;
extern uint8_t EMERGENCY_SW, EMERGENCY_SW_Save[Save_Num], EMERGENCY_SW_Sum;
extern uint8_t SW1_SW, SW1_SW_Save[Save_Num], SW1_SW_Sum;
extern uint8_t SW2_SW, SW2_SW_Save[Save_Num], SW2_SW_Sum;
extern uint8_t SW3_SW, SW3_SW_Save[Save_Num], SW3_SW_Sum;
extern uint8_t SW4_SW, SW4_SW_Save[Save_Num], SW4_SW_Sum;
extern uint8_t SW5_SW, SW5_SW_Save[Save_Num], SW5_SW_Sum;
extern uint8_t SW6_SW, SW6_SW_Save[Save_Num], SW6_SW_Sum;

extern uint8_t Pre_MENU_POPUP_SW;
extern uint8_t Pre_MAIN_BELL_SW;
extern uint8_t Pre_SUB_BELL_SW;
extern uint8_t Pre_LOCAL_BELL_SW;
extern uint8_t Pre_SIREN_SW;
extern uint8_t Pre_EMERGENCY_SW;
extern uint8_t Pre_SW1_SW;
extern uint8_t Pre_SW2_SW;
extern uint8_t Pre_SW3_SW;
extern uint8_t Pre_SW4_SW;
extern uint8_t Pre_SW5_SW;
extern uint8_t Pre_SW6_SW;

#define Phone_Reas_Num 10
extern uint8_t Local_phone_mode;
extern uint8_t phone_jack_mode;
extern uint8_t Local_phone_mode_Save[Phone_Reas_Num];
extern uint8_t phone_jack_mode_Save[Phone_Reas_Num];
extern uint8_t Local_phone_mode_Sum;
extern uint8_t phone_jack_mode_Sum;

#define UI_UART_R_Length 8
#define UI_Com_SW_Q_Length 11
#define UI_Com_MCC_Q_Length  18

#define Sub_MCC_Num 1
#define Sub_MCC_R_length      17
#define Sub_MCC_S_length      16
extern uint8_t Sub_MCC_R_Data[Sub_MCC_Num][Sub_MCC_R_length] ;
extern uint8_t Sub_MCC_S_Data[Sub_MCC_Num][Sub_MCC_S_length] ;

#define Sub_MCC_R_R_length      15

#define UI_UART_buf_len 256
extern uint8_t UI_UART_TX_buf[UI_UART_buf_len] ;
extern uint8_t UI_UART_RX_buf[UI_UART_buf_len];
extern uint8_t UI_UART_Tx_buf_tmp[UI_UART_buf_len];
extern uint8_t UI_UART_RX_buf_tmp[UI_UART_buf_len];
extern uint8_t UI_UART_State ;					// Define reception start state
extern int UI_UART_buf_count;					// Save the length of received data after starting reception
extern int UI_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
extern uint8_t UI_UART_Receive_complete;		// Variable indicating that reception has been completed
extern int UI_UART_buf_count_Save;

#define SUB_UART_buf_len 256
extern uint8_t SUB_UART_TX_buf[SUB_UART_buf_len] ;
extern uint8_t SUB_UART_RX_buf[SUB_UART_buf_len];
extern uint8_t SUB_UART_Tx_buf_tmp[SUB_UART_buf_len];
extern uint8_t SUB_UART_RX_buf_tmp[SUB_UART_buf_len];
extern uint8_t SUB_UART_State ;					// Define reception start state
extern int SUB_UART_buf_count;					// Save the length of received data after starting reception
extern int SUB_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
extern uint8_t SUB_UART_Receive_complete;		// Variable indicating that reception has been completed
extern int SUB_UART_buf_count_Save;

extern uint8_t inf_LED;
extern uint8_t Pre_inf_SWI,inf_SWI;
extern uint8_t Pre_inf_Other, inf_Other;

extern uint8_t user_LED;
extern uint8_t Pre_user_SWI,user_SWI;

extern uint8_t inf_LED_sub[8];
extern uint8_t inf_SWI_sub[8];
extern uint8_t inf_Other_sub[8];

extern uint8_t user_LED_sub[8];
extern uint8_t user_SWI_sub[8];

extern uint8_t MENU_POPUP_LED_mode;
extern uint8_t MAIN_BELL_LED_mode;
extern uint8_t SUB_BELL_LED_mode;
extern uint8_t LOCAL_BELL_LED_mode;
extern uint8_t SIREN_LED_mode;
extern uint8_t EMERGENCY_LED_mode;
extern uint8_t FIRE_LED_mode;
extern uint8_t RUN_LED_mode;
extern uint8_t ERR_LED_mode;

extern uint8_t Pre_Key_MENU_POPUP;
extern uint8_t Pre_Key_SUB_BELL_STOP;
extern uint8_t Pre_Key_SIREN_STOP;
extern uint8_t Pre_Key_MAIN_BELL_STOP;
extern uint8_t Pre_Key_LOCAL_BELL_STOP;
extern uint8_t Pre_Key_EMERGENCY_STOP;

extern uint8_t Ext_phpne_mode;
extern uint8_t Local_phone_mode;
extern uint8_t phone_jack_mode;
extern uint8_t Sub_buzzer4_mode;
extern uint8_t Sub_buzzer3_mode;
extern uint8_t Sub_buzzer2_mode;
extern uint8_t Sub_buzzer1_mode;
extern uint8_t Main_buzzer_mode;

extern uint8_t Pre_LED_Data_Set[Sub_MCC_Num][5];

void Compile_Date(void);
void LED_Test(void);
void Check_Sw(void);
void Sw_Buzzer_On(void);
void Buzzer_Controll(void);

void Err_LED(uint16_t Staus);
void RX_LED(uint16_t Staus);
void TX_LED(uint16_t Staus);

void FIRE_LED(uint16_t Staus);
void BALSIN_LED(uint16_t Staus);
void AC_LED(uint16_t Staus);
void BAT_ERR_LED(uint16_t Staus);
void PHONE_LED(uint16_t Staus);

void MENU_POPUP_LED(uint16_t Staus);
void MAIN_BELL_LED(uint16_t Staus);
void SUB_BELL_LED(uint16_t Staus);
void LOCAL_BELL_LED(uint16_t Staus);
void SIREN_LED(uint16_t Staus);
void EMERGENCY_LED(uint16_t Staus);

void SW_LED1(uint16_t Staus);
void SW_LED2(uint16_t Staus);
void SW_LED3(uint16_t Staus);
void SW_LED4(uint16_t Staus);
void SW_LED5(uint16_t Staus);
void SW_LED6(uint16_t Staus);

void All_LED_ON(void);
void All_LED_OFF(void);

void Read_Sw(void);
void UI_Com_SW_r(void);

void UI_Com(void);
void UI_Check(void);

void UI_Com_All_Q(void);
void UI_Com_SW_Q(void);
void UI_Com_MCC_Q(int Address);
void UI_Com_Relay_Q(int Address);
void UI_Com_DO24_Q(int Address);
void UI_Com_TB_Q(void);
void UI_Com_EB_Q(void);

void UI_Com_All_S(void);
void UI_Com_SW_S(void);
void UI_Com_MCC_S(int Address);
void UI_Com_Relay_S(void);
void UI_Com_DO24_S(void);
void UI_Com_TB_S(void);
void UI_Com_EB_S(void);

void SUB_MCC_S(int Address);
void SUB_MCC_Relay_S(int Address);
void Check_Pump_Run(int Address);

void Read_Sw_LTD_Status(void);

void Send_Sub_Requst(uint8_t Command, uint8_t Address);
int Read_MCC_Status(int Address);
int Read_MCC_R_Status(int Address);
int Read_TB_Status(void);
int Read_DO24_Status(int Address);

void Read_MCC(void);
void Read_MCC_Relay(void);
void Read_TB(void);
void Read_DO24(void);
void Read_EBC(void);

void Set_Led_Data(int Address);

int Read_Version_Status(int Board_Name);
void Send_Sub_Version_Requst(uint8_t Board_Name);
void Read_Sub_Version(void);

void UI_Com_V(void);
void Send_Version_UI_TX(uint8_t Board_Name);

void Set_Pre_Led_Data(int Address);

void Set_Int_LED(void);

void UI_Com_SW2_Q(void);
void UI_Com_SW2_S(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_1_Pin GPIO_PIN_13
#define BUZZER_1_GPIO_Port GPIOC
#define BUZZER_2_Pin GPIO_PIN_14
#define BUZZER_2_GPIO_Port GPIOC
#define BUZZER_3_Pin GPIO_PIN_15
#define BUZZER_3_GPIO_Port GPIOC
#define EMERGENCY_STOP_Pin GPIO_PIN_0
#define EMERGENCY_STOP_GPIO_Port GPIOF
#define EMERGENCY_LED_Pin GPIO_PIN_1
#define EMERGENCY_LED_GPIO_Port GPIOF
#define SW_LED6_Pin GPIO_PIN_0
#define SW_LED6_GPIO_Port GPIOC
#define SW6_Pin GPIO_PIN_1
#define SW6_GPIO_Port GPIOC
#define LOCAL_BELL_LED_Pin GPIO_PIN_2
#define LOCAL_BELL_LED_GPIO_Port GPIOC
#define LOCAL_BELL_STOP_Pin GPIO_PIN_3
#define LOCAL_BELL_STOP_GPIO_Port GPIOC
#define SIREN_LED_Pin GPIO_PIN_0
#define SIREN_LED_GPIO_Port GPIOA
#define SIREN_STOP_Pin GPIO_PIN_1
#define SIREN_STOP_GPIO_Port GPIOA
#define SW_LED5_Pin GPIO_PIN_2
#define SW_LED5_GPIO_Port GPIOA
#define SW5_Pin GPIO_PIN_3
#define SW5_GPIO_Port GPIOA
#define SW_LED4_Pin GPIO_PIN_4
#define SW_LED4_GPIO_Port GPIOA
#define SW4_Pin GPIO_PIN_5
#define SW4_GPIO_Port GPIOA
#define SW_LED3_Pin GPIO_PIN_6
#define SW_LED3_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_7
#define SW3_GPIO_Port GPIOA
#define SUB_BELL_LED_Pin GPIO_PIN_4
#define SUB_BELL_LED_GPIO_Port GPIOC
#define SUB_BELL_STOP_Pin GPIO_PIN_5
#define SUB_BELL_STOP_GPIO_Port GPIOC
#define SW_LED2_Pin GPIO_PIN_0
#define SW_LED2_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOB
#define MAIN_BELL_LED_Pin GPIO_PIN_2
#define MAIN_BELL_LED_GPIO_Port GPIOB
#define MAIN_BELL_STOP_Pin GPIO_PIN_10
#define MAIN_BELL_STOP_GPIO_Port GPIOB
#define SW_LED1_Pin GPIO_PIN_11
#define SW_LED1_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOB
#define UART1_DE_Pin GPIO_PIN_13
#define UART1_DE_GPIO_Port GPIOB
#define UART1_RE_Pin GPIO_PIN_14
#define UART1_RE_GPIO_Port GPIOB
#define MENU_POPUP_LED_Pin GPIO_PIN_15
#define MENU_POPUP_LED_GPIO_Port GPIOB
#define MENU_POPUP_Pin GPIO_PIN_6
#define MENU_POPUP_GPIO_Port GPIOC
#define PHONE_JACK_Pin GPIO_PIN_7
#define PHONE_JACK_GPIO_Port GPIOC
#define LOCAL_PHONE_Pin GPIO_PIN_8
#define LOCAL_PHONE_GPIO_Port GPIOC
#define FIRE_LED_Pin GPIO_PIN_9
#define FIRE_LED_GPIO_Port GPIOC
#define BALSIN_LED_Pin GPIO_PIN_8
#define BALSIN_LED_GPIO_Port GPIOA
#define AC_LED_Pin GPIO_PIN_15
#define AC_LED_GPIO_Port GPIOA
#define RUN_LED_Pin GPIO_PIN_10
#define RUN_LED_GPIO_Port GPIOC
#define ERR_LED_Pin GPIO_PIN_11
#define ERR_LED_GPIO_Port GPIOC
#define BAT_ERR_LED_Pin GPIO_PIN_12
#define BAT_ERR_LED_GPIO_Port GPIOC
#define PHONE_LED_Pin GPIO_PIN_2
#define PHONE_LED_GPIO_Port GPIOD
#define RX_LED_Pin GPIO_PIN_4
#define RX_LED_GPIO_Port GPIOB
#define TX_LED_Pin GPIO_PIN_5
#define TX_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
