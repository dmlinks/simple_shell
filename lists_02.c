#include "shell.h"

/**
 * list_len - determines length of linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *z)
{
	size_t a = 0;

	while (z)
	{
		z = z->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), q;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (q = 0; q < a; q++)
				free(strs[q]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *z)
{
	size_t a = 0;

	while (z)
	{
		put_s(convert_number(z->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		put_s(z->str ? z->str : "(nil)");
		put_s("\n");
		z = z->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}

