/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Serial GPS example
 *
 * @author      Antoine Faure <antoine@afaure.fr>
 *
 * @}
 */

#include <stdio.h>
#include <periph/uart.h>
#include <serial_gps.h>


int main(void)
{
    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);

    int8_t ret = serial_gps_init(UART_DEV(1), 9600);
    printf("ret = %d \n", ret);
    return 0;
}
