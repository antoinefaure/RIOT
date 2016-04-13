/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup        cpu_stm32f7 STM32F7
 * @ingroup         cpu
 * @brief           CPU specific implementations for the STM32F7
 * @{
 *
 * @file
 * @brief           Implementation specific CPU configuration options
 *
 * @author          Antoine Faure <antoine.faure@openwide.fr>
 */

#ifndef __CPU_CONF_H
#define __CPU_CONF_H

#include "cpu_conf_common.h"

#if defined(CPU_MODEL_STM32F746NG)
#include "stm32f746xx.h"
#endif
/**
 * \todo : include the others headers for the others MCUs
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   ARM Cortex-M specific CPU configuration
 * @{
 */
#define CPU_DEFAULT_IRQ_PRIO            (1U)
#define CPU_IRQ_NUMOF                   (82U)
#define CPU_FLASH_BASE                  FLASH_BASE
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __CPU_CONF_H */
/** @} */
