#include <stdio.h>

int main(void)
{
    int a,b,c,x;
    printf("Три целых числа через пробел: ");
    scanf("%d%d%d", &a, &b, &c);
    x=a+b+c;
    printf("%d", x); // можно было по варианту "printf ("%d+%d+%d=%d", a, b, с, a+b+с )", но захотел сделать так
    return 0; 
}



