/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include "dht.h"
#include "dht_params.h"
#include "tsl2561.h"
#include "periph_conf.h"
#include <xtimer.h>


#define TEST_DHT

#ifdef TEST_DHT
dht_t dev = {GPIO_PIN(PORT_B, 3), DHT22, GPIO_IN_PU};

int main(void)
{
    int16_t temp = 0, hum = 0;

    puts("Hello World!");

    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);

    if (dht_init(&dev, &dht_params[0]) == DHT_OK)
        printf("Init sensor\r\n");
    else
        printf("Failed to init the sensor\n");

    dht_read(&dev, &temp, &hum);
    printf("Temp : %d, hum : %d\r\n", temp, hum);
    xtimer_usleep(1000);
    return 0;
}
#endif





#ifdef TEST_LUM
static tsl2561_t dev;
int main(void)
{
    uint16_t lum;
    puts("Hello World!");

    printf("You are running RIOT on a(n) %s board.\r\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\r\n", RIOT_MCU);
    printf("test 1\r\n");

    switch(tsl2561_init(&dev, I2C_DEV(1), 0x39, 0x00, 0x01))
    {
        case TSL2561_NOI2C:
        printf("[Error] I2C not working: cannot initialize the sensor.\n");
        break;

        case TSL2561_BADDEV:
        printf("[Error] Not a TSL2561: cannot initialize the sensor.\n");
        break;

        case TSL2561_OK:
        printf("[Info] Initialization successful\n\n");
        break;
    }

    printf("Init done\n");
    lum = tsl2561_read_illuminance(&dev);
    printf("Lum : %d\r\n", lum);
    printf("Finished !\r\n");

    return 0;
}
#endif
