/*
C11 ДЗ 
НОД
Составить функцию, которая определяет наибольший общий делитель двух натуральных и привести пример ее использования.
int nod(int a, int b)
 */


#include <stdio.h>

int nod(int a, int b)
{
    while(a > 0 && b > 0)
        if(a > b)
            a %= b;
        else
            b %= a;
    return a + b;
}
int main(void)
{
    int a,b;
    printf("Введите два целых положительных числа: ");
    scanf ("%d%d", &a,&b);
    printf("Наибольший общий делитель: %d", nod(a,b));
    return 0;
}
