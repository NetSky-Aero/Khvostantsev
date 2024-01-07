#include <stdio.h>

int main(void)
{
    int a,b,c,x,y;
    printf("Три целых числа через пробел:\n");
    scanf ("%d%d%d", &a, &b, &c);
    x = a+b+c;
    y = a*b*c;
    printf("%d\n %d", x, y); // можно было по варианту "printf("%d+%d+%d=%d", a, b, с, a+b+с ) и т.д.", но захотел сделать так
    return 0;
}

