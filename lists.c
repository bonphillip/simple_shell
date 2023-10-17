#include "shell.h"

/**
 * insert_first - inserts a node at the beginning of the list
 * @head: pointer to the head node
 * @str: string field of the node
 * @num: node index for history
 *
 * Return: size of list
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);

    new_head = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    new_node->next = *head;
    *head = new_node;
    return new_node;
}

/**
 * append_node - Adds a node to the end of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: size of list
 */
list_t *append_node(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return new_node;
}

/**
 * print_strings - prints only the string element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: the size of the list
 */
size_t print_strings(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return i;
}

/**
 * extract_node - Extracts a node at the specified position
 * @list: Address of pointer to the list head
 * @position: Index of the node to delete
 *
 * Return: on successful extraction 1, 0 on failure
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
    list_t *current_node, *previous_node;
    unsigned int count = 0;

     if (!head || !*head)
        return 0;

      if (!position)
    {
        current_node = *list;
        *list = (*list)->next;
        free(current_node->str);
        free(current_node);
        return 1;
    }

    current_node = *list;

    while (current_node)
    {
        if (count == position)
        {
            previous_node->next = current_node->next;
            free(current_node->str);
            free(current_node);
            return 1;
        }

        count++;
        prev_node = node;
        node = node->next;
    }
    return 0;
}

/**
 * deallocate_linked_list - Deallocates all nodes in the linked list
 * @list_head: Address of pointer to the list head
 *
 * Return: void
 */
void deallocate_linked_list(list_t **list_head)
{
    list_t *current_node, *next_node, *head;

    if (!list_head || !*list_head)
        return;

    head = *list_head;
    current_node = head;

    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->str);
        free(current_node);
        current_node = next_node;
    }
    *list_head = NULL;
}
