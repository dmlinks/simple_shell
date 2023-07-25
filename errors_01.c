#include "shell.h"

/**
 * eput_s - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void eput_s(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}

/**
 * e_putchar - writes the character c to stderr
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int e_putchar(char a)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}

/**
 * put_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * put_sfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int put_sfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += put_fd(*str++, fd);
	}
	return (a);
}
