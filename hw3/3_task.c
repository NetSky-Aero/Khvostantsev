#include <stdio.h>

int main(void) 
{
    int a,b,c;
    printf("Два целых числа через пробел:\n");
    scanf("%d%d", &a, &b);
    c = a-b;
    printf("%d", c);
    return 0;
}

