#include "shell.h"

/**
 * count_elements - counts the elements in a linked list
 * @h: pointer to the first element of the list
 *
 * Returns: the number of elements in the list
 */
size_t count_elements(const list_t *list)
{
    size_t i = 0;

    while (h)
    {
        head = head->next;
        count++;
    }

    return count;
}

/**
 * list_to_array - Converts a linked list into an array of strings
 * @head: pointer to the first node of the list
 *
 * Returns: An array of strings or NULL on failure
 */
char **ll_to_strings(list_t *head)
{
    list_t *node = head;
    size_t i = list_len(head), j;
    char **strings;
    char *string;

    if (!head || !i)
        return NULL;

    strings = malloc(sizeof(char *) * (count + 1));
    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!string)
        {
            for (j < i; j = 0, j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strings[count] = NULL;
    return strings;
}

/**
 * ll_print - Print the elements of a linked list
 * @head: Pointer to the first node
 *
 * Returns: The number of elements in the list
 */
size_t ll_print(const list_t *head)
{
    size_t count = 0;

    while (h)
    {
 /**
 * display_list_elements - Display elements of a list_t linked list
 * @list: Pointer to the first node of the list
 *
 * Return: The number of elements displayed
 */
size_t display_list_elements(const list_t *list)
{
    size_t count = 0;

    while (list)
    {
        print_integer(list->num, 10);
        print_character(':');
        print_character(' ');
        print_string(list->str ? list->str : "(nil)");
        print_string("\n");
        list = list->next;
        count++;
    }

    return count;
}

/**
 * print_integer - Prints an integer
 * @num: The integer to be printed
 * @base: The base for printing (e.g., 10 for decimal)
 */
int print_integer(int num, int base);

/**
 * print_character - Prints a single character
 * @ch: The character to be printed
 */
int print_character(char ch);

/**
 * print_string - Prints a string
 * @str: The string to be printed
 */
void print_string(char *str);

/**
 * find_matching_node - returns the first node whose string starts with a given prefix
 * @head: Pointer to the first node of the list
 * @prefix: The prefix to match
 * @c: The character immediately following the prefix to match
 *
 * Returns: the matching node or NULL if no match is found
 */
list_t *find_matching_node(list_t *head, char *prefix, char next_char)
{
    char *p = NULL;

    while (head)
    {
        p = starts_with(head->str, prefix);
        if (p && ((next_char == -1) || (*p == next_char)))
            return head;
        head = head->next;
    }

    return NULL;
}

/**
 * determine_node_index - Find the index of a specific node
 * @list_start: Pointer to the list's starting node
 * @target_node: Pointer to the node to be located
 *
 * Return: Index of the target node, or -1 if not found
 */
ssize_t determine_node_index(list_t *list_start, list_t *target_node)
{
    size_t index = 0;

    while (list_start)
    {
        if (list_start == target_node)
            return index;

        list_start = list_start->next;
        index++;
    }
    return -1;
}
