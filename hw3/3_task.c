#include <stdio.h>

    int main(void) 
{
    int a,b,c;
    printf("Два целых числа через пробел:\n");
    scanf("%d%d", &a, &b);
    //printf("%d-%d=%d", a, b, a-b);
    c = a-b;
    printf("%d", c);
    return 0;
}

