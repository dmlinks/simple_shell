#include "shell.h"

/**
 * my_exit - A function that exits the shell interface
 * @info: The Structure containing arguments.
 *	Used to maintain function prototype
 *		constant function prototype.
 *
 * Return: with a given exit status return exit
 *		(0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			eput_s(info->argv[1]);
			e_putchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - this changes the current directory
 * @info: the struct containing potential arguments for prototype
 *
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		put_s("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			put_s(str);
			_putchar('\n');
			return (1);
		}
		put_s(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		eput_s(info->argv[1]), e_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - A function that changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **ag_array;

	ag_array = info->argv;
	put_s("help call works. Function not yet implemented \n");
	if (0)
		put_s(*ag_array); /* temp att_unused workaround */
	return (0);
}
