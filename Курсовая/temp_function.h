#ifndef TEMP_FUNCTION_H_INCLUDED
#define TEMP_FUNCTION_H_INCLUDED

#include <stdint.h>
#include <stdio.h>

struct sensor
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    int8_t t;
};

void help(void);
double Avr_Month_Temp(struct sensor* info, int n, int month);
int Min_Month_Temp(struct sensor* info, int n, int month);
int Max_Month_Temp(struct sensor* info, int n, int month);
double Avr_Yearh_Temp(struct sensor* info, int n);
int Min_Yearh_Temp(struct sensor* info, int n);
int Max_Yearh_Temp(struct sensor* info, int n);
void print_month_statistic(struct sensor* info,
                            int number, 
                            int month, 
                            double Avr_Month_Temp, 
                            int Min_Month_Temp, 
                            int Max_Month_Temp);
void changeIJ(struct sensor* info, int i, int j);
void SortByT(struct sensor* info, int n);
unsigned int DateToInt(struct sensor*info);
void SortByDate(struct sensor* info, int n);
void print(struct sensor* info,int number);

#endif