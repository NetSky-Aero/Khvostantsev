/*
D14 ДЗ 4
Все нечетные
Дана последовательность целых чисел через пробел, завершающаяся числом 0. Выведите все нечетные числа из этой последовательности, сохраняя их порядок. 
 */

#include <stdio.h>

void number(int num)
{
    scanf("%d", &num);
    if (num == 0)
        return;
    if (num % 2 != 0)
        printf("%d ", num);
    return number (num);
}

int main(void)
{
    printf("Введите числа: ");
    number(0);
    return 0;
}

