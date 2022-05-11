# avr-ds3231
DS3231 Library for AVR Atmega328

DS3231 RTC clock looks like:
![DS3231](https://www.gmelectronic.com/data/product/1024_1024/pctdetail.772-290.1.jpg)

Library has RTC clock alarms supported and depends on https://github.com/ecnx/avr-i2c


Link to datasheet: https://datasheets.maximintegrated.com/en/ds/DS3231.pdf


Set clock time example:

```
struct ds3231_alarm_t alarm = { 0 };
alarm.minutes = 23;
alarm.hours = 11;
ds3231_write_clock ( &alarm ); // 0 = success
```
