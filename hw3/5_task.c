#include <stdio.h>

int main(void)
{
    int a, b;
    printf("Ввести трехзначное целое положительное число: ");
    if (scanf("%d", &a ) != 1 || ! a)
        return 1;
    for ( b = 1; a; a /= 10 )
        b *= a % 10;
    printf("Произведение цифр: %d", b);
    return 0;
}

