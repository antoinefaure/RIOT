/**
 * @defgroup    drivers_serial_gps Family of GPS sensors sending data over UART
 *                                  in the NMEA standard.
 * @ingroup     drivers_sensors
 * @brief       Device driver for the serial GPS sensors
 *
 * @{
 *
 * @file
 * @brief       Device driver for the serial GPS sensors using the NMEA standard
 *
 * @author      Antoine Faure <antoine@afaure.fr>
 */

#ifndef SERIAL_GPS_H
#define SERIAL_GPS_H

#include <stdint.h>
#include <periph/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

struct serial_gps_time_record {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}

struct serial_gps_position {
    uint8_t longitude;
    uint8_t latitude;
    uint8_t direction longitude;
    uint8_t direction latitude;
    struct serial_gps_time_record;
    // Time last record ? Or time last record gll, etc... ?
};

struct serial_gps {
    struct serial_gps_position last_position;
};


/**
 * @brief Initialize a new GPS device
 *
 * @param[in]   uart_link   UART link the GPS is conencted to
 * @param[in]   baudrate    The baudrate to use to communicate with the GPS.
 *                          It is usually 4800 or 9600 bauds
 *
 * @return              0 on success
 * @return              -1 on error
 * @return              -2 on inapplicable baudrate
 * @return              -3 on other errors
 */
int8_t serial_gps_init(uart_t uart_link, uint32_t baudrate);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_GPS_H */
/** @} */
