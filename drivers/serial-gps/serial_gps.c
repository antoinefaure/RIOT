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
/**
 * @brief Store all the data related to the GPS
 */
static struct serial_gps_t data_gps;

static uint8_t entry_not_finished(uint8_t *buff)
{
    if (NULL == buff)
        return 0;
    else if ('\0' == buff[0] || '\n' == buff[0])
        return 0;
    else
        return 1;
}


//static uint8_t next_field_exists(uint8_t *buf)
//{
//    if (!entry_not_finished(buf))
//        return 0;
//    else if (',' == buf[0] && !entry_not_finished(&buf[1]))
//        return 1;
//    else return 0;
//}


static uint8_t _next_field_as_int(uint8_t** index, int32_t *value)
{
    uint8_t buffer[64] = {0};
    // *index should point on the ',' at the beginning of the field
    if (',' == *index[0])
        *index++;
    if (',' == index[0])
        return 0; // The field is empty
    uint8_t *nextfield = (uint8_t*)strpbrk((char*)*index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - *index) > 64)
        return 0;

    memcpy(buffer, *index, (nextfield -1 - *index));
    *value = atoi((char*)buffer);
    *index = nextfield;
    return 1;
}

static uint8_t _next_field_as_double(uint8_t** index, double *value)
{
    uint8_t buffer[64] = {0};
    // *index should point on the ',' at the beginning of the field
    if (',' == *index[0])
        *index++;
    if (',' == index[0])
        return 0; // The field is empty
    uint8_t *nextfield = (uint8_t*)strpbrk((char*)*index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - *index) > 64)
        return 0;

    memcpy(buffer, *index, (nextfield -1 - *index));
    *value = atof((char*)buffer);
    *index = nextfield;
    return 1;
}

static uint8_t _next_field_as_time(uint8_t** index, uint8_t *h, uint8_t *m, uint8_t *s)
{
    uint8_t buffer[7] = {0}, tmp[3] = {0};
    // *index should point on the ',' at the beginning of the field
    if (',' == *index[0])
        *index++;
    if (',' == index[0])
        return 0; // The field is empty

    uint8_t *nextfield = (uint8_t*)strpbrk((char*)*index, ",");

    if (NULL == nextfield)
        return 0;
    if((nextfield - *index) > 6)
        return 0;

    memcpy(buffer, *index, (nextfield -1 - *index));
    memcpy(tmp, buffer, 2);
    *h = atoi((char*)tmp);
    memcpy(tmp, buffer+2, 2);
    *m = atoi((char*)tmp);
    memcpy(tmp, buffer+4, 2);
    *s = atoi((char*)tmp);
    *index = nextfield;
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
//static void _handle_mss(uint8_t idx_start)
//{
//}

/**
 * SiRF timing message
 */
//static void _handle_zda(uint8_t idx_start)
//{
//}

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

// @TODO verifier dans entry not finished que pas d'overflow ?
// @TODO dans les fonctions next_field_as verifier que field pas vide
// De meme quand lis directement (direction)


/**
 * Global positioning system fixed data
 */
static void _handle_gga(uint8_t *idx_start)
{
    uint8_t *index = idx_start;
    uint8_t hour = 0, minute = 0, second = 0;
    double latitude = 0, longitude = 0;
    uint8_t direction_latitude = 0, direction_longitude = 0;
    uint8_t ret = 0, fix_quality = 0;
    uint8_t nb_satellites = 0;

    ret = _next_field_as_time(&index, &hour, &minute, &second);
    if (!ret || !entry_not_finished(index))
        return;

    ret = _next_field_as_double(&index, &latitude);
    if (!ret || !entry_not_finished(index))
        return;

    direction_latitude = index[1];
    index += 2;
    if (!ret || !entry_not_finished(index))
        return;

    ret = _next_field_as_double(&index, &longitude);
    if (!entry_not_finished(index))
        return;

    direction_longitude = index[1];
    index += 2;
    if (!entry_not_finished(index))
        return;

    ret = next_field_as_int(&index, &fix_quality);
    if (!ret || fix_quality > 8 || fix_quality < 0 || !next_field_exists(index))
        return;

    ret = next_field_as_int(&index, &nb_satellites);
    if (!ret || !next_field_exists(index))
        return;

    double horizontal_dilution = 0;
    ret = next_field_as_double(&index, &horizontal_dilution);
    if (!ret || next_field_exists(index)
            return;
}

static void process_entry(void)
{
    uint8_t idx = 0;
    printf ("process entry : \n");
    printf("%s \n", data_entry);
    uint8_t buffer[64] = {0};

    // If the entry is correct, we want to copy the first field,
    // i.e. everything until the first ','
    while (idx < 64 && '\0' != data_entry[idx] && ',' != data_entry[idx] &&
            '\n' != data_entry[idx]) {
        buffer[idx] = data_entry[idx];
    }

    if (!(',' == data_entry[idx])) {
        // Wrong data
        return;
    }

    if (strcmp("$GPGGA", (char*)buffer) == 0)
        _handle_gga(&buffer[idx]);
    else if (strcmp("$GPGSA", (char*)buffer) == 0)
        _handle_gsa(idx);
    else if (strcmp("GPGSV", (char*)buffer) == 0)
        _handle_gsv(idx);
    else if (strcmp("GPGLL", (char*)buffer) == 0)
        _handle_gll(idx);
    else if (strcmp("GPRMC", (char*)buffer) == 0)
        _handle_rmc(idx);
    else if (strcmp("GPVTG", (char*)buffer) == 0)
        _handle_vtg(idx);
    else
        return; // Unknown record
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

