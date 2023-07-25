#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_hed;

	if (!head)
		return (NULL);
	new_hed = malloc(sizeof(list_t));
	if (!new_hed)
		return (NULL);
	mem_set((void *)new_hed, 0, sizeof(list_t));
	new_hed->num = num;
	if (str)
	{
		new_hed->str = str_dup(str);
		if (!new_hed->str)
		{
			free(new_hed);
			return (NULL);
		}
	}
	new_hed->next = *head;
	*head = new_hed;
	return (new_hed);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *nod;

	if (!head)
		return (NULL);

	nod = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	mem_set((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = str_dup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *z)
{
	size_t a = 0;

	while (z)
	{
		put_s(z->str ? z->str : "(nil)");
		put_s("\n");
		z = z->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nodee, *prev_nodee;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodee = *head;
		*head = (*head)->next;
		free(nodee->str);
		free(nodee);
		return (1);
	}
	nodee = *head;
	while (nodee)
	{
		if (a == index)
		{
			prev_nodee->next = nodee->next;
			free(nodee->str);
			free(nodee);
			return (1);
		}
		a++;
		prev_nodee = nodee;
		nodee = nodee->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nod, *next_nod, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*head_ptr = NULL;
}

