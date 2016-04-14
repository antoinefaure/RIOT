/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup    boards_stm32f7discovery STM32F7Discovery
 * @ingroup     boards
 * @brief       Board specific files for the STM32F7Discovery board
 * @{
 *
 * @file
 * @brief       Board specific definitions for the STM32F7Discovery evaluation board
 *
 * @author      Antoine Faure <antoine@afaure.fr>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "cpu.h"
#include "periph_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name xtimer configuration
 * @{
 */
#define XTIMER              TIMER_0
#define XTIMER_CHAN         (0)
#define XTIMER_OVERHEAD     (6)
#define XTIMER_BACKOFF      (10)
/** @} */

/**
 * @name LED pin definitions
 * @{
 */
/** @} */

/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED1_PIN            GPIO_PIN(PORT_I, 2)

#define LED_PORT            GPIOI
#define LED1_MASK           (1 << 2)

#define LD1_ON              (LED_PORT->BSRR = LD1_PIN)
#define LD1_OFF             (LED_PORT->BSRR = ((uint32_t)LD1_PIN << 16))
#define LD1_TOGGLE          (LED_PORT->ODR ^= LD1_PIN)

/* for compatability to other boards - same LED as LED 1*/
#define LED_GREEN_ON        LD1_ON
#define LED_GREEN_OFF       LD1_OFF
#define LED_GREEN_TOGGLE    LD1_TOGGLE

/** @} */

/**
 * @brief User button
 */
#define BTN_B1_PIN          GPIO_PIN(PORT_A, 0)

/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
/** @} */
