/*
B4 Урок 5 ДЗ 2
Ровно три цифры
Ввести целое число и определить, верно ли, что в нём ровно 3 цифры.
 */

#include <stdio.h>

int main(void) 
{
    int a, count;
    printf("Введи целое число: ");
    scanf("%d", &a);
    for(; a != 0; count++, a = a / 10);
    count == 3 ? printf("YES") : printf("NO");
    return 0;
}

