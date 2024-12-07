#include <stdio.h>

int main(void)
{
    int N, max, count, num;

    scanf("%d", &N);
    scanf("%d", &max);
    count = 1;

    for (int i = 1; i < N; ++i)
	{
        scanf("%d", &num);
        if (num > max)
		{
            max = num;
            count = 1;
        } else if (num == max)
		{
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
