#include "shell.h"

/**
 * _eputs - prints input string
 * @str: string to print
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - writes c to stderr
 * @c: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, then errno is appropriately set.
 */
int _eputchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[f++] = c;
	return (1);
}

/**
 * _putfd - prints c to given fd
 * @c: Character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1, and errno is set
 */
int _putfd(char c, int fd)
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
 * _putsfd - prints input string
 * @str: the string to print
 * @fd: filedescriptor to write
 *
 * Return: the number of chars inputted
 */
int _putsfd(char *str, int fd)
{
	int g = 0;

	if (!str)
		return (0);
	while (*str)
	{
		g += _putfd(*str++, fd);
	}
	return (g);
}
