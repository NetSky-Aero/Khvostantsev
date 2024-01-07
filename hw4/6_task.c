#include <stdio.h>

int main(void)
{
    int a, b;
    printf("Введите два числа: ");
    scanf("%d%d", &a, &b);
    if (a < b)
        printf("Less\n");
    else if (a > b)
        printf("Above\n");
    else
        printf("Equal\n"); 
    return 0;
}

