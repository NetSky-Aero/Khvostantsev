#include <stdio.h>

int main(void)
{
    int a, b, c, max;
    printf("Введите три числа: ");
    scanf("%d%d%d", &a, &b, &c);
    if (a >= b && a >= c)
    {
    max = a;
    }
    else 
    {
    if (b >= a && b >= c)
    max = b;
    else
    max = c;
    }
    printf("Наибольшее число: %d\n", max);
    return 0;
}

