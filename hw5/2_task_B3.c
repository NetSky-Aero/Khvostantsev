/*
Сумма квадратов маленьких чисел
Ввести два целых числа a и b (a ≤ b) и вывести сумму квадратов всех чисел от a до b.
*/

#include <stdio.h>
#include <math.h>

int main (void) 
{
    int a, b, c;
    printf("Введи два целых числа a и b, где a <= b и b <=100): ");
    scanf("%d%d", &a, &b);
    if (a > b || b > 100) 
    {
        printf("Ошибка\n");
        return 1;
    }
    for (; a <= b; a++) 
    {
        c += (int) pow(a, 2);
    }
    printf("%d\n", c);
    return 0;
}
