/*
C9 Практ 2
Факториал
Составить функцию вычисления N!. Использовать ее при вычислении факториала
int factorial(int n)
 */

#include <stdio.h>

int factorial (int n)
{
    int number = 1;
    for (int i = 2; i<=n; i++)
    {
        number *= i;
    }
    return number;
}
int main(void)
{
    int number;
    printf("Введите целое положительное число: ");
    scanf ("%d", &number);
    printf("Факториал = %d", factorial(number));
    return 0;
}
