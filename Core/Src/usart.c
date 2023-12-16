/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"

/* USER CODE BEGIN 0 */

/*
typedef enum {
    WAITING_FOR_HEADER1,
    WAITING_FOR_HEADER2,
    READING_SIZE1,
    READING_SIZE2,
    READING_COMMAND,
    READING_MESSAGE,
    WAITING_FOR_NULL,
    WAITING_FOR_FOOTER1,
    WAITING_FOR_FOOTER2
} UART_State;

UART_State state = WAITING_FOR_HEADER1;
uint16_t message_size = 0;
uint16_t counter = 0;
uint8_t command = 0;

*/
/*
uint8_t message[] = "Merhaba LL Library!\n";

void USART2_Transmit(uint8_t* buffer, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        while(!LL_USART_IsActiveFlag_TXE(USART2));
        LL_USART_TransmitData8(USART2, buffer[i]);
    }
    while(!LL_USART_IsActiveFlag_TC(USART2));
}

void USART2_Transmit_Message()
{
    USART2_Transmit(message, sizeof(message)-1);
    Delay_ms(1000);
}*/



/* USER CODE END 0 */

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
	SysTick_Config(SystemCoreClock / 1000);
  /* USER CODE END USART2_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
  */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(USART2_IRQn);

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/* USER CODE BEGIN 1 */
void TRANSMIT_DATA(void) {
    if(LL_USART_IsActiveFlag_RXNE(USART2) && LL_USART_IsEnabledIT_RXNE(USART2)) {
        uint8_t tmp = LL_USART_ReceiveData8(USART2);
        MESSAGE_RECEIVE_SERVICE(tmp);
    }
}
/*
void MESSAGE_RECEIVE_SERVICE(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART2) && LL_USART_IsEnabledIT_RXNE(USART2))
    {
        uint8_t tmp = LL_USART_ReceiveData8(USART2);

        switch(state)
        {
            case WAITING_FOR_HEADER1:
                if(tmp == 0xFE) state = WAITING_FOR_HEADER2;
                break;

            case WAITING_FOR_HEADER2:
                if(tmp == 0xFD) state = READING_SIZE1;
                break;

            case READING_SIZE1:
                message_size = tmp << 8;
                state = READING_SIZE2;
                break;

            case READING_SIZE2:
                message_size |= tmp;
                state = READING_COMMAND;
                break;

            case READING_COMMAND:
                command = tmp;
                counter = 0;
                state = READING_MESSAGE;
                if(command == 0x01) LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5); // LED'i yak
                else if(command == 0x02) LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5); // LED'i söndür
                break;

            case READING_MESSAGE:
                if(++counter >= message_size) state = WAITING_FOR_NULL;
                break;

            case WAITING_FOR_NULL:
                if(tmp == 0x00) state = WAITING_FOR_FOOTER1;
                break;

            case WAITING_FOR_FOOTER1:
                if(tmp == 0xFD) state = WAITING_FOR_FOOTER2;
                break;

            case WAITING_FOR_FOOTER2:
                if(tmp == 0xFE) state = WAITING_FOR_HEADER1; // Mesaj tamamlandı
                break;
        }
    }
}
*/
/*
void TRANSMIT_MESSAGE(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART2) && LL_USART_IsEnabledIT_RXNE(USART2))
    {
        uint8_t tmp = LL_USART_ReceiveData8(USART2);

        if(tmp == 'l')
        {
            LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5); // LED'i yak
            uint8_t message[] = "LED ACILDI\n";
            USART2_Transmit(message, sizeof(message)-1);
        }

        else if (tmp == 'k')
        {
            LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5); // LED'i yak
            uint8_t message[] = "LED KAPANDI\n";
            USART2_Transmit(message, sizeof(message)-1);
        }
    }
} */


/* USER CODE END 1 */
