#include "temp_function.h"

int8_t Avr_Month_Temp(struct sensor *data, uint8_t size, uint8_t month)
{
    int avr = 0;
    int cnt = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
            avr += data[i].temperature;
            cnt++;
        }
    }
    avr /= cnt;
    return avr;
}

int8_t Min_Month_Temp(struct sensor *data, uint8_t size, uint8_t month)
{
    int min = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
        }
    }
    return min;
}

int8_t Max_Month_Temp(struct sensor *data, uint8_t size, uint8_t month)
{
    int max = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
        }
    }
    return max;
}

int8_t Avr_Yearh_Temp(struct sensor *data, uint8_t size, uint8_t year)
{
    int avr = 0;
    int cnt = 0;
    int data = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == year)
        {
            avr += data[i].temperature;
            cnt++;
        }
    }
    avr /= cnt;
    return avr;
}

int8_t Min_Yearh_Temp(struct sensor *data, uint8_t size, uint8_t year)
{
    int min = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == year)
        {
        }
    }
    return min;
}

int8_t Max_Yearh_Temp(struct sensor *data, uint16_t size, uint8_t year)
{
    int max = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        if (data[i].month == year)
        {
        }
    }
    return max;
}