/*Весы
В стартер боксе Geek Brains есть электронные чашечные весы (вместимость каждой чашки 1 тонна) и гири массами 1г, 3г, 9г, 27г, и т.д. по одной штуке каждой массы.
Менеджер из рекламного отдела взял такие весы и не знает, можно ли взвесить что-нибудь тяжелое и если можно, сколько гирь придется положить на весы (на любую чашку).
Надо помочь ему. Формат входных данных: единственное натуральное число – масса взвешиваемого товара в граммах (не больше 1000000000).
Формат выходных данных: единственное целое число – общее количество гирь или число –1 если данный товар взвесить невозможно.

Примеры:
Входные данные: 8 Результат работы: 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_weights(int weight)
{
    int total_weights = 0;
    long long max_mass = 0;
    long long power = 1;

    while (max_mass < 1000000000)
    {
        max_mass = max_mass * 3 + power;
        power *= 3;
    }

    if (weight > max_mass)
    {
        return -1;
    }

    while (weight > 0)
    {
        int remainder = weight % 3;

        if (remainder == 1)
        {
            total_weights++;
        } else if (remainder == 2)
        {
            total_weights++;
            weight += 1;
        }

        weight /= 3;
    }

    return total_weights;
}

int main()
{
    int weight;
    scanf("%d", &weight);
    if (weight <= 0 || weight > 1000000000)
    {
        printf("-1\n");
        return 0;
    }
    int result = count_weights(weight);
    printf("%d\n", result);

    return 0;
}
