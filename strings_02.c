#include "shell.h"

/**
 * str_cpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *str_cpy(char *dest, char *src)
{
	int d = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[d])
	{
		dest[d] = src[d];
		d++;
	}
	dest[d] = 0;
	return (dest);
}

/**
 * str_dup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *str)
{
	int length = 0;
	char *rete;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rete = malloc(sizeof(char) * (length + 1));
	if (!rete)
		return (NULL);
	for (length++; length--;)
		rete[length] = *--str;
	return (rete);
}

/**
 * put_s - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void put_s(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

