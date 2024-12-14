#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 20

struct list                                                         // Определяю структуры односвязного списка
{
    char word[MAX_WORD_LENGTH];
    struct list *next;
};

void add_to_list(struct list **head, const char *word)              // Функция добавления слова в список
{
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(new_node->word, word, MAX_WORD_LENGTH - 1);
    new_node->word[MAX_WORD_LENGTH - 1] = '\0';
    new_node->next = *head;
    *head = new_node;
}

void swap_elements(struct list *a, struct list *b)                  // Функция обмена двух элементов списка
{
    char temp[MAX_WORD_LENGTH];
    strncpy(temp, a->word, MAX_WORD_LENGTH);
    strncpy(a->word, b->word, MAX_WORD_LENGTH);
    strncpy(b->word, temp, MAX_WORD_LENGTH);
}

void sort_list(struct list *head)                                   // Функция сортировки списка по алфавиту
{
    if (head == NULL) return;
    struct list *i, *j;
    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->word, j->word) > 0)
            {
                swap_elements(i, j);
            }
        }
    }
}

void print_list(struct list *head)                                  // Функция вывода списка
{
    struct list *current = head;
    while (current != NULL)
    {
        printf("%s", current->word);
        if (current->next != NULL)
        {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void delete_list(struct list *head)                                 // Функция удаления списка
{
    struct list *current = head;
    while (current != NULL)
    {
        struct list *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    char input[100];
    struct list *head = NULL;

//    printf("Enter a string of words ending with a period: ");       // Ввод строки
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Error reading input\n");
        return 1;
    }
    size_t len = strlen(input);                                     // Убираю символ новой строки, если он есть
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    len = strlen(input);                                            // Удаляю точку в конце строки
    if (len > 0 && input[len - 1] == '.')
    {
        input[len - 1] = '\0';
    }
    char *word = strtok(input, " ");                                // Разбиваю строку на слова
    while (word != NULL) {
        add_to_list(&head, word);
        word = strtok(NULL, " ");
    }
    sort_list(head);                                                // Сортирую список
    print_list(head);                                               // Вывожу отсортированный список
    delete_list(head);                                              // Удаляю список

    return 0;
}
