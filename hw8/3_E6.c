/*
E6
Среднее арифметическое массива
Считать массив из 12 элементов и подсчитать среднее арифметическое элементов массива.  
 */


#include <stdio.h>

int main(void)
{
    int n = 12;
    float num[12], sum = 0.0, average;
    for (int i = 0; i < n; ++i)
    {   
        printf("%d. Введите число: ", i+1);
        scanf("%f", &num[i]);
        sum += num[i];
    }
    average = sum / n;
    printf("Среднее арифметическое элементов массива = %.2f\n", average);
    return 0;
}

