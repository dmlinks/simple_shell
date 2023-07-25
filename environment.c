#include "shell.h"

/**
 * my_env - This  prints the current environ
 * @info: this struct containing potential arguments
 *	To maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - Gets the value of an environ variable
 * @info: This struct containing potential arguments
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - This Initialize a new environment variable,
 *             or modify an existing one
 * @info: this struct containing potential arguments.
 *
 *  Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		eput_s("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myun_setenv - This remove an environment variable
 * @info: this struct containing potential arguments
 *	Used to maintain function prototype.
 *
 * Return: Always 0
 */
int myun_setenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		eput_s("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		un_setenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: this structure containing potential arguments
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
