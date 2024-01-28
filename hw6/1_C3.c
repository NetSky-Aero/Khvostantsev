/*
C3 Практ 1
Среднее арифметическое чисел
Написать функцию, которая возвращает среднее арифметическое двух переданных ей аргументов (параметров).
int middle(int a, int b)
*/


#include <stdio.h>

int middle(int a, int b)
{
    int calculate;
    calculate = (a+b)/2;
    return calculate;
}
int main(void)
{
    int a,b;
    printf("Ведите два числа: ");
    scanf("%d%d",&a,&b);
    printf("Среднее арифмитическое = %d\n", middle(a,b));
    return 0;
}

