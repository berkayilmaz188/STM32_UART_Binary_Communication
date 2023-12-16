/* BEGIN Header */
/**
  ******************************************************************************
  * @file    message_service.c
  * @brief   Message Service operations.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Tubitak BILGEM.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* END Header */

/* Includes ------------------------------------------------------------------*/
#include "message_service.h"
#include "usart.h"
#include <stdbool.h>
#include <string.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
 Message message_queue[MESSAGE_QUEUE_SIZE];
static uint8_t queue_head = 0;
static uint8_t message_queue_head = 0;
static uint8_t queue_tail = 0;
static Message current_message;
static uint8_t message_index = 0;
static uint8_t footer_byte_count = 0;
typedef enum {
    WAITING_FOR_HEADER1,
    WAITING_FOR_HEADER2,
    READING_SIZE1,
    READING_SIZE2,
    READING_TYPE,
    READING_MESSAGE,
    READING_STANDARD,
    READING_FOOTER // Bu durumu eklemeniz gerekir
} State;
static State state = WAITING_FOR_HEADER1;
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           					 Queue Functions	  				          */
/******************************************************************************/



/**
  * @brief This function initialize Message Receive Service.
  */
void MESSAGE_RECEIVE_SERVICE(uint8_t byte) {
    switch (state) {
		case WAITING_FOR_HEADER1:
			if (byte == 0xFE) {
				state = WAITING_FOR_HEADER2;
				current_message.HEADER = byte << 8; // ilk byte'ı kaydet
			}
			break;
		case WAITING_FOR_HEADER2:
			current_message.HEADER |= byte; // ikinci byte'ı ekle
			if (current_message.HEADER == 0xFEFD) {
				state = READING_SIZE1;
			}
			break;
		case READING_SIZE1:
			current_message.SIZE = byte << 8; // ilk boyut byte'ı
			state = READING_SIZE2;
			break;
		case READING_SIZE2:
			current_message.SIZE |= byte; // ikinci boyut byte'ı
			state = READING_TYPE;
			break;
        case READING_TYPE:
            current_message.READING_TYPE = byte;
            state = READING_MESSAGE;
            break;
        case READING_MESSAGE:
            current_message.READING_MESSAGE[message_index++] = byte;
            if (message_index >= current_message.SIZE) {
                message_index = 0;
                state = READING_STANDARD;
            }
            break;
        case READING_STANDARD:
            if (byte == 0x00) {
                current_message.READING_STANDARD = byte;
                state = READING_FOOTER;
            } else {
                memset(&current_message, 0, sizeof(current_message));
                message_index = 0;
                footer_byte_count = 0;
                state = WAITING_FOR_HEADER1;
            }
            break;
        case READING_FOOTER:
            current_message.FOOTER = (current_message.FOOTER << 8) | byte;
            if (++footer_byte_count == 2) {
                footer_byte_count = 0;
                if (current_message.FOOTER == 0xFDFE) {
                    message_queue[queue_head++] = current_message;
                    queue_head %= MESSAGE_QUEUE_SIZE;
                    memset(&current_message, 0, sizeof(current_message));
                    state = WAITING_FOR_HEADER1;
                }
            }
            break;
    }
}
/**
  * @brief This function initialize Queue service.
  */
void process_message(void) {
    Message* message = &message_queue[message_queue_head++]; // İlk sıradaki mesajı işleyin

    uint8_t led_status = message->READING_MESSAGE[0];
    uint16_t blink_param = (message->READING_MESSAGE[1] << 8) | message->READING_MESSAGE[2];
    uint16_t pwm_param = (message->READING_MESSAGE[3] << 8) | message->READING_MESSAGE[4];

    update_message_parameters(message, led_status, blink_param, pwm_param);
    message_queue_head %= MESSAGE_QUEUE_SIZE;
}
/**
  * @brief This function initialize Queue service.
  */
void update_message_parameters(Message* msg, uint8_t led_status, uint16_t blink_param, uint16_t pwm_param) {
    msg->LED_STATUS = led_status;
    msg->BLINK_PARAMETER = blink_param;
    msg->PWM_PARAMETER = pwm_param;
}


/**
  * @brief This function initialize Queue service.
  */
Message get_message(void) {
    Message msg = message_queue[queue_tail++];
    queue_tail %= MESSAGE_QUEUE_SIZE;
    return msg;
}
/**
  * @brief This function initialize Queue service.
  */
uint8_t is_message_received(void) {
    return (queue_head != queue_tail);
}

void send_message(Message* msg) {
    uint8_t data[10 + msg->SIZE]; // 10, diğeR ALANLAR TOPAM BOYUT
    data[0] = (msg->HEADER >> 8) & 0xFF;
    data[1] = msg->HEADER & 0xFF;
    data[2] = (msg->SIZE >> 8) & 0xFF;
    data[3] = msg->SIZE & 0xFF;
    data[4] = msg->READING_TYPE;
    memcpy(&data[5], msg->READING_MESSAGE, msg->SIZE);
    data[5 + msg->SIZE] = msg->READING_STANDARD;
    data[6 + msg->SIZE] = (msg->FOOTER >> 8) & 0xFF;
    data[7 + msg->SIZE] = msg->FOOTER & 0xFF;


    for(int i = 0; i < 10 + msg->SIZE; i++) {

        while(!LL_USART_IsActiveFlag_TXE(USART2));
        LL_USART_TransmitData8(USART2, data[i]);
    }
}




