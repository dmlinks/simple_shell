#include "shell.h"

/**
 * my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: This struct containing potential arguments
 *	for constant function prototype.
 *
 *  Return: 0 always
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - A function that sets alias to string
 * @info: the parameter structure
 * @str:  string alias
 *
 * Return: success 0, error 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, t;
	int rete;

	p = str_chr(str, '=');
	if (!p)
		return (1);
	t = *p;
	*p = 0;
	rete = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = t;
	return (rete);
}

/**
 * set_alias - This code sets alias to string
 * @info: this is the parameter structure
 * @str: string alias
 *
 * Return: on success 0, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = str_chr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - this prints an alias string in the code
 * @node: alias node
 *
 * Return: on success 0, 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = str_chr(node->str, '=');
		for (b = node->str; b <= q; b++)
		_putchar(*b);
		_putchar('\'');
		put_s(q + 1);
		put_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: the structure containing arguments
 *	To maintain function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		q = str_chr(info->argv[i], '=');
		if (q)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
