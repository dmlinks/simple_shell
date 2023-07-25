#include "shell.h"

/**
 **strn_cpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *
 *Return: the concatenated string
 */
char *strn_cpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **strn_cat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the number of bytes to be maximally used
 *
 *Return: the concatenated string
 */
char *strn_cat(char *dest, char *src, int n)
{
	int a, q;
	char *s = dest;

	a = 0;
	q = 0;
	while (dest[a] != '\0')
		a++;
	while (src[q] != '\0' && q < n)
	{
		dest[a] = src[q];
		a++;
		q++;
	}
	if (q < n)
		dest[a] = '\0';
	return (s);
}

/**
 **str_chr - locates a character in a string
 *@a: the string to be parsed
 *@c: the character to look for
 *
 *Return: (a) a pointer to the memory area s
 */
char *str_chr(char *a, char c)
{
	do {
		if (*a == c)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
