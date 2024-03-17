#include "temp_function.h"
#include <stdio.h>

void Information(void)
{
    printf("\n\nFor information, enter: myprog.exe -h\n");
    printf("\n");
}

void changeIJ(struct sensor* info, int i, int j)
{
    struct sensor temp;
    temp =    info[i];
    info[i] = info[j];
    info[j] = temp;
}

void SortByT(struct sensor* info, int n)
{
    for(int i = 0; i<n; ++i)
        for(int j = i; j<n; ++j)
            if(info[i].t >=info[j].t)
                changeIJ(info, i, j);
}

unsigned int DateToInt(struct sensor*info)
{
    return info->year << 16 | info->month <<8 |
    info-> day << 8 | info-> hours << 8 | info-> minutes;
}

void SortByDate(struct sensor* info, int n)
{
    for(int i = 0; i<n; ++i)
        for(int j = i; j<n; ++j)
              if(DateToInt(info+i) >= 
                 DateToInt(info + j))
                  changeIJ(info, i, j);
}

void print(struct sensor* info,int number)
{
printf("\n*******************************\n");
    for(int i=0;i<number;i++)
        printf("%04d-%02d-%02d-%02d-%02d t = %3d\n",
            info[i].year,
            info[i].month,
            info[i].day,
            info[i].hours,
            info[i].minutes,
            info[i].t
        );
}

void print_month_statistic(struct sensor* info,int number, int month, double Avr_Month_T, int Min_Month_T, int Max_Month_T)
{
    Avr_Month_T = Avr_Month_Temp(info, number, month);
    Min_Month_T = Min_Month_Temp(info, number, month);
    Max_Month_T = Max_Month_Temp(info, number, month);
    for(int i = 0; i < number; i++)
    {
        if(info[i].month == month)
        {
            printf("%5d%10d%15.2lf%20d%25d\n", info[i].year, info[i].month, Avr_Month_T, Min_Month_T, Max_Month_T);
            break;
        }
    }
}

double Avr_Month_Temp(struct sensor* info, int number, int month)
{
    int sum = 0;
    double average = 0;
    int count = 0;
    for(int i = 0; i < number; i++)
    {
        if(info[i]. month == month)
        {
             count++;
             sum = sum + info[i].t;
        }
    }
    average = (double)sum/count;
    return average;
}

int Min_Month_Temp(struct sensor* info, int number, int month)
{
    int min_t = 100;
    for(int i = 0; i < number; i++)
    {
        if(info[i].month == month && min_t > info[i].t)
        {
            min_t = info[i].t;
        }
    }

    return min_t;
}

int Max_Month_Temp(struct sensor* info, int number, int month)
{
    int max_t = -100;
    for(int i = 0; i < number; i++)
    {
        if(info[i].month == month && max_t < info[i].t)
        {
            max_t = info[i].t;
        }
    }
    return max_t;
}

double Avr_Yearh_Temp(struct sensor* info, int number)
{
    int sum = 0;
    double average = 0;
    int count = 0;
    for(int i = 0; i < number; i++)
    {
        if(info[i].year == 2021)
        {
             count++;
             sum = sum + info[i].t;
        }
    }
    average = (double)sum/count;
    printf("\n****************************************\n");
    printf("\nSrednegodovaya temperatura %.2lfC\n", average);
    return average;
}

int Min_Yearh_Temp(struct sensor* info, int number)
{
    int min_t = info[0].t;
    for (int k = 0; k < number; k++)
    {
        if(info[k].year == 2021 && min_t > info[k].t)
        {
          min_t = info[k].t;
        }
    }

    printf("\n****************************************\n");
    printf("\nMinimal'naya godovaya temperatura %dC\n", min_t);
    return min_t;
}

int Max_Yearh_Temp(struct sensor* info, int number)
{
    int max_t = info[0].t;
    for (int k = 0; k < number; k++)
    {
        if(info[k].year == 2021 && max_t < info[k].t)
        {
          max_t = info[k].t;
        }
    }
    printf("\n****************************************\n");
    printf("\nMaksimal'naya godovaya temperatura %dC\n", max_t);
    printf("\n****************************************\n");
    return max_t;
}