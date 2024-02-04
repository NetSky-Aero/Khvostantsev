/*
D16 Практик 3
Точная степень двойки
Написать логическую рекурсивную функцию и используя ее определить является ли введенное натуральное число точной степенью двойки.
int is2pow(int n)
 */

#include <stdio.h>

int is2pow(int n)
{
    if (n%2) 
    {
        return n == 1;
    }
    else if (n > 1 && n < 2) 
    {
        return 0;
    }
    else 
    {
        return n / 2;
    }
}
int main(void)
{
    int n;
    printf("Введите одно натуральное число: ");
    scanf ("%d", &n); 
    is2pow(n) ? printf ("YES") : printf ("NO");
    return 0;
}
