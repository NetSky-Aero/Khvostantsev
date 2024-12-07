/* ����� ������
������� ��������� ������ ��� �������� ���������� �� �������������� ������: typedef struct list { void *address; size_t size; char comment[64]; struct list *next; } list;
��������� ����������� ������ ���� �������, ������� ����������� ������ ������ � ���������� ������� ����� ������ ������������.
����� �������� � ���� address, ���� size - ��������������� ������ ������� �����. ���� ������ ������, �� ������� ������ ���������� NULL. �������� �������: size_t totalMemoryUsage(list *head)

�������:
������� ������:
3
	  140525067852320 10
	  140525067852350 30
	  140525067852900 100
��������� ������: 140
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
