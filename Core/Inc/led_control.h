
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
#ifndef __LED_CONTROL_H
#define __LED_CONTROL_H

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>
#include "message_service.h"
/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint8_t  flag_LED_STATE_CONTROL:1;
    uint8_t  flag_BLINK_CONTROL:1;
    uint8_t  flag_PWM_CONTROL:1;

    uint8_t  flag_LED_PARAMETER;
    uint8_t  flag_BLINK_PARAMETER;
    uint8_t  flag_PWM_PARAMETER;
} LedControl;

extern Message message_queue[];
/* Exported constants --------------------------------------------------------*/
void process_led_control(void);
extern uint16_t blinkms;
/* Exported macro ------------------------------------------------------------*/
#define MESSAGE_QUEUE_SIZE 16
/* Exported functions prototypes ---------------------------------------------*/




#endif /* __LED_CONTROL_H */
