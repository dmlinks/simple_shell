#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * un_setenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 *
 *  Return: 1 on delete, 0 otherwise
*/
int un_setenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *
 *  Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *a;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		a = starts_with(node->str, var);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

