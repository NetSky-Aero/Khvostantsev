#include <stdio.h>

    int main(void) 
{
    int a,b,c;

    printf("Трехзначное целое положительное число:\n");
    scanf("%d%d%d", &a, &b, &c);

    printf("%.2f\n", (float) (a + b + c) / 3);

    return 0;
}
