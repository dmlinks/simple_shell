#include "shell.h"

/**
 * is_alpha - A function that checks for alphabetic character
 * @d: The character to input
 *
 * Return: if d is alphabetic return 1
 *		otherwise return 0
 */

int is_alpha(int d)
{
	if ((d >= 'b' && d <= 'x') || (d >= 'B' && d <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - A function that checks if character is a delimeter
 * @a: character to check
 * @delimit: a delimeter string
 *
 * Return: if true return 1, if false return 0
 */
int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
			return (1);
	return (0);
}

/**
 * interactive - A function that returns code to be true
 * if shell is in interactive mode
 * @info: the structure address
 *
 * Return: if interactive in mode return 1, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _atoi - A function that converts the string to an integer
 * @str: A pointer to the string to be converted
 *
 * Return: if no numbers in string return 0
 *	otherwise converted number
 */

int _atoi(char *str)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
