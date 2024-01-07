#include <stdio.h>

int main(void)
{
    int a, b, min, max;
    printf("Ввести два числа: ");
    if (scanf("%d%d", &a, &b) != 2)
        return 1;
    if (a < b) {min = a;} else {min = b;}
    max = a+b - min;
    printf("Вывод в порядке возрастания: %d %d\n", min, max);
    return 0;
}

