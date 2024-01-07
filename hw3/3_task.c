#include <stdio.h>

int main(void) 
{
    int a,b,c;
    printf("Два целых числа через пробел:\n");
    scanf("%d%d", &a, &b);
    c = a-b;
    printf("%d", c); // можно было по варианту "printf ("%d-%d=%d", a, b, a-b )", но захотел сделать так
    return 0;
}
