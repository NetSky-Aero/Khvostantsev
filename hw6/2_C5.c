/*
C5 ДЗ 
Сумма от 1 до N
Составить функцию, которая определяет сумму всех чисел от 1 до N и привести пример ее использования.
 */


#include <stdio.h>

int number (int a)
{
    int number = 0;
    for(int i=1; i<=a; i++)
    {
        number += i;
    }
    return number;
}

int main (void)
{
    int a;
    printf("Введите положительное число: ");
    scanf("%d", &a);
    printf("Сумма чисел: %d", number(a));
    return 0;
}

