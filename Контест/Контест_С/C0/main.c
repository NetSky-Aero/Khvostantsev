/* Вычеркивание
Сколько различных трехзначных чисел можно получить из заданного натурального N, вычеркивая цифры из его десятичной записи?

Примеры:
Входные данные: 1111111111111111111111111
Результат работы: 1
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIGITS 100

int count_unique_three_digit_numbers(const char *number)
{
    int len = strlen(number);
    bool seen[1000] = {0};
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
            {
            for (int k = j + 1; k < len; k++)
            {
                int num = (number[i] - '0') * 100 +
                          (number[j] - '0') * 10 +
                          (number[k] - '0');
                if (!seen[num])
                {
                    seen[num] = true;
                    count++;
                }
            }
        }
    }

    return count;
}

int main()
{
    char number[MAX_DIGITS + 1];
    scanf("%s", number);
    int result = count_unique_three_digit_numbers(number);
    printf("%d\n", result);

    return 0;
}
