/* ------------------------------------------------------------------
 * DS3231 Library for AVR Devices
 * ------------------------------------------------------------------ */

#include "ds3231.h"

/**
 * Read RTC EEPROM Data
 */
static int8_t ds3231_read_eeprom ( uint8_t addr, void *data, size_t len )
{
    return i2c_start (  ) ||
        i2c_addr ( DS3231_I2C_SLAW_WRITE ) ||
        i2c_tx_byte ( addr ) ||
        i2c_restart (  ) ||
        i2c_addr ( DS3231_I2C_SLAW_READ ) ||
        i2c_rx_data ( ( uint8_t * ) data, len ) || i2c_stop (  );
}

/**
 * Write RTC EEPROM Data
 */
static int8_t ds3231_write_eeprom ( uint8_t addr, const void *data, size_t len )
{
    return i2c_start (  ) ||
        i2c_addr ( DS3231_I2C_SLAW_WRITE ) ||
        i2c_tx_byte ( addr ) || i2c_tx_data ( ( const uint8_t * ) data, len ) || i2c_stop (  );
}

/**
 * Read RTC Clock Data
 */
int8_t ds3231_read_clock ( struct ds3231_clock_t *clock )
{
    struct ds3231_raw_clock_t raw;

    if ( ds3231_read_eeprom ( DS3231_EEPROM_CLOCK, &raw, sizeof ( raw ) ) )
    {
        return 1;
    }

    clock->seconds = raw.seconds10 * 10 + raw.seconds;
    clock->minutes = raw.minutes10 * 10 + raw.minutes;
    clock->hours = raw.hours10 * 10 + raw.hours;
    clock->day = raw.hours10 * 10 + raw.day;
    clock->date = raw.date10 * 10 + raw.date;
    clock->century = raw.century;
    clock->month = raw.month10 * 10 + raw.month;
    clock->year = raw.year10 * 10 + raw.year;

    return 0;
}

/**
 * Write RTC Clock Data
 */
int8_t ds3231_write_clock ( const struct ds3231_clock_t *clock )
{
    struct ds3231_raw_clock_t raw = { 0 };

    raw.seconds10 = clock->seconds / 10;
    raw.seconds = clock->seconds % 10;
    raw.minutes10 = clock->minutes / 10;
    raw.minutes = clock->minutes % 10;
    raw.hours10 = clock->hours / 10;
    raw.hours = clock->hours % 10;
    raw.day = clock->day;
    raw.date10 = clock->date / 10;
    raw.date = clock->date % 10;
    raw.century = clock->century;
    raw.month10 = clock->month / 10;
    raw.month = clock->month % 10;
    raw.year10 = clock->year / 10;
    raw.year = clock->year % 10;

    return ds3231_write_eeprom ( DS3231_EEPROM_CLOCK, &raw, sizeof ( raw ) );
}

/**
 * Read RTC Alarm #1 Data
 */
int8_t ds3231_read_alarm1 ( struct ds3231_alarm_t *alarm )
{
    struct ds3231_raw_alarm1_t raw;

    if ( ds3231_read_eeprom ( DS3231_EEPROM_ALARM1, &raw, sizeof ( raw ) ) )
    {
        return 1;
    }

    alarm->m1 = raw.a1m1;
    alarm->seconds = raw.seconds10 * 10 + raw.seconds;
    alarm->m2 = raw.a1m2;
    alarm->minutes = raw.minutes10 * 10 + raw.minutes;
    alarm->m3 = raw.a1m3;
    alarm->hours = raw.hours10 * 10 + raw.hours;
    alarm->m4 = raw.a1m4;
    alarm->date = raw.date10 * 10 + raw.date;

    return 0;
}

/**
 * Write RTC Alarm #1 Data
 */
int8_t ds3231_write_alarm1 ( const struct ds3231_alarm_t *alarm )
{
    struct ds3231_raw_alarm1_t raw = { 0 };

    raw.a1m1 = alarm->m1;
    raw.seconds10 = alarm->seconds / 10;
    raw.seconds = alarm->seconds % 10;
    raw.a1m2 = alarm->m2;
    raw.minutes10 = alarm->minutes / 10;
    raw.minutes = alarm->minutes % 10;
    raw.a1m3 = alarm->m3;
    raw.hours10 = alarm->hours / 10;
    raw.hours = alarm->hours % 10;
    raw.a1m4 = alarm->m4;
    raw.date10 = alarm->date / 10;
    raw.date = alarm->date % 10;

    return ds3231_write_eeprom ( DS3231_EEPROM_ALARM1, &raw, sizeof ( raw ) );
}

/**
 * Read RTC Alarm #2 Data
 */
int8_t ds3231_read_alarm2 ( struct ds3231_alarm_t *alarm )
{
    struct ds3231_raw_alarm2_t raw;

    if ( ds3231_read_eeprom ( DS3231_EEPROM_ALARM2, &raw, sizeof ( raw ) ) )
    {
        return 1;
    }

    alarm->m1 = 0;
    alarm->seconds = 0;
    alarm->m2 = raw.a2m2;
    alarm->minutes = raw.minutes10 * 10 + raw.minutes;
    alarm->m3 = raw.a2m3;
    alarm->hours = raw.hours10 * 10 + raw.hours;
    alarm->m4 = raw.a2m4;
    alarm->date = raw.date10 * 10 + raw.date;

    return 0;
}

/**
 * Write RTC Alarm #2 Data
 */
int8_t ds3231_write_alarm2 ( const struct ds3231_alarm_t *alarm )
{
    struct ds3231_raw_alarm2_t raw = { 0 };

    raw.a2m2 = alarm->m2;
    raw.minutes10 = alarm->minutes / 10;
    raw.minutes = alarm->minutes % 10;
    raw.a2m3 = alarm->m3;
    raw.hours10 = alarm->hours / 10;
    raw.hours = alarm->hours % 10;
    raw.a2m4 = alarm->m4;
    raw.date10 = alarm->date / 10;
    raw.date = alarm->date % 10;

    return ds3231_write_eeprom ( DS3231_EEPROM_ALARM2, &raw, sizeof ( raw ) );
}

/**
 * Read RTC Control Data
 */
int8_t ds3231_read_control ( struct ds3231_control_t *control )
{
    return ds3231_read_eeprom ( DS3231_EEPROM_CONTROL, control,
        sizeof ( struct ds3231_control_t ) );
}

/**
 * Write RTC Control Data
 */
int8_t ds3231_write_control ( const struct ds3231_control_t *control )
{
    return ds3231_write_eeprom ( DS3231_EEPROM_CONTROL, control,
        sizeof ( struct ds3231_control_t ) );
}
