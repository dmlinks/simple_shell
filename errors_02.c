#include "shell.h"

/**
 * err_atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_atoi(char *s)
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	eput_s(info->fname);
	eput_s(": ");
	print_d(info->line_count, STDERR_FILENO);
	eput_s(": ");
	eput_s(info->argv[0]);
	eput_s(": ");
	eput_s(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, cont = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cont++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			cont++;
		}
		current %= i;
	}
	__putchar('0' + current);
	cont++;

	return (cont);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sig = 0;
	char *pnt;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		sig = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pnt = &buffer[49];
	*pnt = '\0';

	do	{
		*--pnt = array[a % base];
		a /= base;
	} while (a != 0);

	if (sig)
		*--pnt = sig;
	return (pnt);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
