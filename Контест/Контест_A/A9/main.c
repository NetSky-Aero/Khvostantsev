/*Упаковать массив
В программе реализована структура данных:
struct pack_array {
uint32_t array; // поле для хранения упакованного массива из 0 и 1
uint32_t count0 : 8; // счетчик нулей в array
uint32_t count1 : 8; // счетчик единиц в array
}
Необходимо реализовать программу, которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу: void array2struct(int [], struct pack_array *)

Примеры:
Входные данные: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 Результат работы: 4294901760 16 16
Входные данные: 1 1 1 1 1 1 1 1 1 0 1 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 Результат работы: 4289134601 17 15
*/

#include <stdio.h>
#include <stdint.h>

struct pack_array
{
    uint32_t array;
    uint32_t count0 : 8;
    uint32_t count1 : 8;
};

void array2struct(int arr[], struct pack_array *result)
{
    result->array = 0;
    result->count0 = 0;
    result->count1 = 0;

    for (int i = 0; i < 32; i++)
    {
        if (arr[i] == 1)
        {
            result->array |= (1U << (31 - i));
            result->count1++;
        }
        else
        {
            result->count0++;
        }
    }
}

int main(void)
{
    struct pack_array result;
    int input[32];
    for (int i = 0; i < 32; i++)
    {
        scanf("%d", &input[i]);
    }
    array2struct(input, &result);
    printf("%u %u %u\n", result.array, result.count0, result.count1);
    return 0;
}
