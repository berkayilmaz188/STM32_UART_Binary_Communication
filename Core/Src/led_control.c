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
#include "led_control.h"
#include "usart.h"
#include <stdbool.h>
#include <string.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint8_t led_queue_head = 0;
uint16_t blinkms = 0;
uint16_t dutyms = 0;
uint8_t led = 0;
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           					 Queue Functions	  				          */
/******************************************************************************/



/**
  * @brief This function initialize Message Receive Service.
  */
void process_led_control(void) {
    LedControl ledControl = {0};

    Message* message = &message_queue[led_queue_head++];

    switch (message->READING_TYPE) {
        case 0x01:
            ledControl.flag_LED_STATE_CONTROL = 1;
            ledControl.flag_BLINK_CONTROL = RESET;
            ledControl.flag_PWM_CONTROL = RESET;

            ledControl.flag_LED_PARAMETER = message->LED_STATUS;
            break;
        case 0x02:
            ledControl.flag_LED_STATE_CONTROL = RESET;
            ledControl.flag_BLINK_CONTROL = 1;
            ledControl.flag_PWM_CONTROL = RESET;

            blinkms = message->BLINK_PARAMETER;
            break;
        case 0x03:
            ledControl.flag_LED_STATE_CONTROL = RESET;
            ledControl.flag_BLINK_CONTROL = RESET;
            ledControl.flag_PWM_CONTROL = 1;

            dutyms = message->PWM_PARAMETER;
            break;
    }
    led_queue_head %= MESSAGE_QUEUE_SIZE;
}
/**
  * @brief This function initialize Queue service.
  */
/*void controls_led(void) {

	if ( ledControl.flag_LED_STATE_CONTROL = 1;)
}*/

/**
  * @brief This function initialize Queue service.
  */



/**
  * @brief This function initialize Queue service.
  */

/**
  * @brief This function initialize Queue service.
  */





