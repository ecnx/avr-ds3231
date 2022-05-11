/* ------------------------------------------------------------------
 * DS3231 Library for AVR Devices
 * ------------------------------------------------------------------ */

#ifndef DS3231_H
#define DS3231_H

/**
 * Note: Bitfields order must be reversed.
 */

#include <stdint.h>
#include <i2c.h>

/**
 * DS3231 Misc Constants
 */
#define DS3231_I2C_SLAW_WRITE   0xD0
#define DS3231_I2C_SLAW_READ    0xD1
#define DS3231_EEPROM_CLOCK     0x00
#define DS3231_EEPROM_ALARM1    0x07
#define DS3231_EEPROM_ALARM2    0x0B
#define DS3231_EEPROM_CONTROL   0x0E

/**
 * DS3231 Raw Clock Data Structure
 */
struct ds3231_raw_clock_t
{
    /* Clock Seconds - 00h */
    uint8_t seconds:4;
    uint8_t seconds10:3;
    uint8_t unused1:1;

    /* Clock Minutes - 01h */
    uint8_t minutes:4;
    uint8_t minutes10:3;
    uint8_t unused2:1;

    /* Clock Hours - 02h */
    uint8_t hours:4;
    uint8_t hours10:2;
    uint8_t unused3:2;

    /* Clock Day - 03h */
    uint8_t day:3;
    uint8_t unused4:5;

    /* Clock Date - 04h */
    uint8_t date:4;
    uint8_t date10:2;
    uint8_t unused5:2;

    /* Clock Month - 05h */
    uint8_t month:4;
    uint8_t month10:1;
    uint8_t unused6:2;
    uint8_t century:1;

    /* Clock Year - 06h */
    uint8_t year:4;
    uint8_t year10:4;
} __attribute__( ( packed ) );

/**
 * DS3231 Clock Data Structure
 */
struct ds3231_clock_t
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t century;
    uint8_t month;
    uint8_t year;
};

/**
 * DS3231 Raw Alarm #1 Data Structure
 */
struct ds3231_raw_alarm1_t
{
    /* Alarm #1 Seconds - 07h */
    uint8_t seconds:4;
    uint8_t seconds10:3;
    uint8_t a1m1:1;

    /* Alarm #1 Minutes - 08h */
    uint8_t minutes:4;
    uint8_t minutes10:3;
    uint8_t a1m2:1;

    /* Alarm #1 Hours - 09h */
    uint8_t hours:4;
    uint8_t hours10:2;
    uint8_t a1m3:2;

    /* Alarm #1 Date - 0Ah */
    uint8_t date:4;
    uint8_t date10:2;
    uint8_t unused1:1;
    uint8_t a1m4:1;

} __attribute__( ( packed ) );

/**
 * DS3231 Raw Alarm #2 Data Structure
 */
struct ds3231_raw_alarm2_t
{
    /* Alarm #2 Minutes - 0Bh */
    uint8_t minutes:4;
    uint8_t minutes10:3;
    uint8_t a2m2:1;

    /* Alarm #2 Hours - 0Ch */
    uint8_t hours:4;
    uint8_t hours10:3;
    uint8_t a2m3:2;

    /* Alarm #2 Date - 0Dh */
    uint8_t date:4;
    uint8_t date10:2;
    uint8_t unused1:1;
    uint8_t a2m4:1;

} __attribute__( ( packed ) );

/**
 * DS3231 Alarm Data Structure
 */
struct ds3231_alarm_t
{
    uint8_t m1;
    uint8_t seconds;
    uint8_t m2;
    uint8_t minutes;
    uint8_t m3;
    uint8_t hours;
    uint8_t m4;
    uint8_t date;
};

/**
 * DS3231 Control Data Structure
 */
struct ds3231_control_t
{
    /* Control Register #1 - 0Eh */

    uint8_t a1ie:1;
    uint8_t a2ie:1;
    uint8_t intcn:1;
    uint8_t rs1:1;
    uint8_t rs2:1;
    uint8_t conv:1;
    uint8_t bbsqw:1;
    uint8_t neg_eosc:1;

    /* Control Register #2 - 0Fh */
    uint8_t a1f:1;
    uint8_t a2f:1;
    uint8_t bsy:1;
    uint8_t en32kHz:1;
    uint8_t unused:3;
    uint8_t osf:1;
} __attribute__( ( packed ) );

/**
 * Read RTC Clock Data
 */
int8_t ds3231_read_clock ( struct ds3231_clock_t *clock );

/**
 * Write RTC Clock Data
 */
int8_t ds3231_write_clock ( const struct ds3231_clock_t *clock );

/**
 * Read RTC Alarm #1 Data
 */
int8_t ds3231_read_alarm1 ( struct ds3231_alarm_t *alarm1 );

/**
 * Write RTC Alarm #1 Data
 */
int8_t ds3231_write_alarm1 ( const struct ds3231_alarm_t *alarm1 );

/**
 * Read RTC Alarm #2 Data
 */
int8_t ds3231_read_alarm2 ( struct ds3231_alarm_t *alarm2 );

/**
 * Write RTC Alarm #2 Data
 */
int8_t ds3231_write_alarm2 ( const struct ds3231_alarm_t *alarm2 );

/**
 * Read RTC Control Data
 */
int8_t ds3231_read_control ( struct ds3231_control_t *control );

/**
 * Write RTC Control Data
 */
int8_t ds3231_write_control ( const struct ds3231_control_t *control );

#endif
