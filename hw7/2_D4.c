/*
D4 ДЗ 1
В прямом порядке
Дано натуральное число N. Выведите все его цифры по одной, в прямом порядке, разделяя их пробелами или новыми строками. Необходимо реализовать рекурсивную функцию.
void print_num(int num)
 */


#include <stdio.h>

void print_num(int num)
{
    if (num != 0)
        print_num(num / 10);
    else
        return;
    printf("%d ", num % 10);
    return;
}

int main(void)
{
    int num = 0;
    printf("Введите число: ");
    scanf("%d", &num);
    print_num(num);
    return 0;
}

