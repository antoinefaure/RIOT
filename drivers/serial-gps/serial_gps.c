/**
 * @ingroup     drivers_serial_gps
 * @{
 *
 * @file
 * @brief       Driver implementation of the serial gps and the NMEA standard.
 *
 * @author      Antoine Faure <antoine@afaure.fr>
 *
 * @}
 */

#include <stdint.h>
//#include <string.h>
#include <periph/uart.h>
#include "serial_gps.h"
//#include "log.h"
//#include "xtimer.h"

/**
 * @brief Maximum size of an entry (or line) send by a GPS
 */
#define SERIAL_GPS_MAXIMUM_SIZE_OF_ENTRY 100

/**
 * @brief Buffer to store an incomplete entry before processing it
 */
static uint8_t data_entry[SERIAL_GPS_MAXIMUM_SIZE_OF_ENTRY] = {};
/**
 * @brief Last element in the buffer
 */
static uint8_t buffer_index = 0;


int checksum(char *s) {
    int c = 0;
    while(*s)
        c ^= *s++;
    return c;
}


static void process_entry(void)
{
    printf("%s \n", data_entry);
    buffer_index = 0;
}


static void data_received (void *arg, const uint8_t data)
{
    if ('$' == data) {
        return;
    } else if ('\n' == data) {
        buffer_index++;
        if (buffer_index < SERIAL_GPS_MAXIMUM_SIZE_OF_ENTRY)
            data_entry[buffer_index] = '\0';
        process_entry();
    } else {
        buffer_index++;
        data_entry[buffer_index] = data;
    }
}


int8_t serial_gps_init(uart_t uart_link, uint32_t baudrate)
{
    return (int8_t)uart_init(uart_link, baudrate, data_received, NULL);
}

