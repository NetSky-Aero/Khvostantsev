#ifndef TEMP_FUNCTION_H
#define TEMP_FUNCTION_H

#include <stdint.h>
#include <stdio.h>

#define SIZE 50

struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    int8_t temperature;
};
struct data
{
    uint32_t number;
    struct sensor info[SIZE];
};

union sensor_serdes
{
    struct data _data;
    uint8_t bytes[sizeof(struct data)];
};

int8_t Avr_Month_Temp(struct sensor *data, uint8_t size, uint8_t month);
int8_t Min_Month_Temp(struct sensor *data, uint8_t size, uint8_t month);
int8_t Max_Month_Temp(struct sensor *data, uint8_t size, uint8_t month);
int8_t Avr_Yearh_Temp(struct sensor *data, uint8_t size, uint8_t year);
int8_t Min_Yearh_Temp(struct sensor *data, uint8_t size, uint8_t year);
int8_t Max_Yearh_Temp(struct sensor *data, uint8_t size, uint8_t year);

#endif