
/* BEGIN Header */
/**
  ******************************************************************************
  * @file    circular_buffer.h
  * @brief   This file contains the message service .
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MESSAGE_SERVICE_H
#define __MESSAGE_SERVICE_H

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint16_t HEADER;
    uint16_t SIZE;
    uint8_t  READING_TYPE;
    uint8_t  READING_MESSAGE[255];
    uint8_t  READING_STANDARD;
    uint8_t  LED_STATUS;           // LED'in durumunu belirtmek için
    uint8_t  BLINK_PARAMETER;      // LED'in yanıp sönme hızı
    uint8_t  PWM_PARAMETER;        // PWM duty_cycle degisim hızı
    uint16_t FOOTER;
} Message;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define MESSAGE_DATA_SIZE 64
#define MESSAGE_QUEUE_SIZE 16
/* Exported functions prototypes ---------------------------------------------*/

void MESSAGE_RECEIVE_SERVICE(uint8_t byte);
Message get_message(void);
uint8_t is_message_received(void);
void send_message(Message* msg);
void process_message(void);
void update_message_parameters(Message* msg, uint8_t led_status, uint16_t blink_param, uint16_t pwm_param);


#endif /* __MESSAGE_SERVICE_H */
