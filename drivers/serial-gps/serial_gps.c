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
#include <stdlib.h>
#include <string.h>
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

static uint8_t _next_field_as_int(uint8_t index, int32_t *value)
{
    uint8_t buffer[64] = {0};
    uint8_t *nextfield = strpbrk(data_entry+index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - index) > 64)
        return 0;

    memcpy(buffer, data_entry+index, (nextfield-index));
    *value = atoi(buffer);
    return 1;
}

static uint8_t _next_field_as_double(uint8_t index, double *value)
{
    uint8_t buffer[64] = {0};
    uint8_t *nextfield = strpbrk(data_entry+index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - index) > 64)
        return 0;

    memcpy(buffer, data_entry+index, (nextfield-index));
    *value = atof(buffer);
    return 1;
}

static uint8_t _next_field_as_time(uint8_t index, uint8_t *h, uint8_t *m, uint8_t *s)
{
    uint8_t buffer[7] = {0}, tmp[3] = {0};
    uint8_t *nextfield = strpbrk(data_entry+index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - index) > 6)
        return 0;

    memcpy(buffer, data_entry+index, (nextfield-index));
    memcpy(tmp, buffer, 2);
    *h = atoi(tmp);
    memcpy(tmp, buffer+2, 2);
    *m = atoi(tmp);
    memcpy(tmp, buffer+4, 2);
    *s = atoi(tmp);
    return 1;
}

//static int checksum(char *s) {
//    int c = 0;
//    while(*s)
//        c ^= *s++;
//    return c;
//}

/**
 * MSK Receiver Signal
 */
static void _handle_mss(uint8_t idx_start)
{
}

/**
 * SiRF timing message
 */
static void _handle-zda(uint8_t idx_start)
{
}

/**
 * GNSS DOP and active satellites
 */
static void _handle_gsa(uint8_t idx_start)
{
}

/**
 * GNSS satellites in view
 */
static void _handle_gsv(uint8_t idx_start)
{
}

/**
 * Geographic position - Latitude / Longitude
 */
static void _handle_gll(uint8_t idx_start)
{
}

/**
 * Recommended minimum specific GNSS data
 */
static void _handle_rmc(uint8_t idx_start)
{
}

/**
 * Course over ground and ground speed
 */
static void _handle_vtg(uint8_t idx_start)
{
}

/**
 * Global positioning system fixed data
 */
static void _handle_gga(uint8_t idx_start)
{
    uint8_t buffer[64] = {0};
    uint8_t index = idx_start, *next_index = NULL;
    uint8_t hour = 0, minute = 0, second = 0;
    double latitude = 0, longitude = 0;
    uint8_t direction_latitude = 0, direction_longitude = 0;

    next_index = _next_field_as_time(idx_start, &hour, &minute, &second);
    if (0 == next_index)
            return;
    next_index = _next_field_as_double(next_index, &latitude);
    if (0 == next_index)
            return;
    int tmp;
    _next_field_as_int(0, &tmp); //REMOVE
}

static void process_entry(void)
{
    printf ("process entry : \n");
    printf("%s \n", data_entry);
    uint8_t buffer[64] = {0};
    int idx = 0;

    while (idx < 64 && '\0' != data_entry[idx] && ',' != data_entry[idx] ||
            '\n' ==data_entry) {
        buffer[idx] = data_entry[idx];
    }

    if (!(',' == data_entry[idx])) {
        /* Wrong data */
        return;
    }

    if (strcmp("$GPGGA", buffer) == 0)
        _handle_gga(idx);
    else if (strcmp("$GPGSA", buffer) == 0)
        _handle_gsa(idx);
    else if (strcmp("GPGSV", buffer) == 0)
        _handle_gsv(idx);
    else if (strcmp("GPGLL", buffer) == 0)
        _handle_gll(idx);
    else if (strcmp("GPRMC", buffer) == 0)
        _handle_rmc(idx);
    else if (strcmp("GPVTG", buffer) == 0)
        _handle_vtg(idx);
    else
        return; // Unknown record
}

}


static void data_received (void *arg, const uint8_t data)
{
    printf("Called : %c = %d\n", data, data);
    if ('\n' == data) {
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

