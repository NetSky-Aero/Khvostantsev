/* Всего памяти
Описана структура данных для хранения информации об использованной памяти: typedef struct list { void *address; size_t size; char comment[64]; struct list *next; } list;
Требуется реализовать только одну функцию, которая анализирует данный список и возвращает сколько всего памяти используется.
Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать NULL. Прототип функции: size_t totalMemoryUsage(list *head)

Примеры:
Входные данные:
3
	  140525067852320 10
	  140525067852350 30
	  140525067852900 100
Результат работы: 140
*/

#include <stdio.h>
#include <stddef.h>

typedef struct list
{
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

size_t totalMemoryUsage(list *head)
{
    if (head == NULL)
    {
        return 0;
    }

    size_t total = 0;
    list *current = head;

    while (current != NULL)
    {
        total += current->size;
        current = current->next;
    }

    return total;
}

int main(void)
{
    list node3 = { (void *)140525067852900, 100, "Block 3", NULL };
    list node2 = { (void *)140525067852350, 30, "Block 2", &node3 };
    list node1 = { (void *)140525067852320, 10, "Block 1", &node2 };

    size_t total = totalMemoryUsage(&node1);
    printf("%zu\n", total);

    return 0;
}
