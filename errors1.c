#include "shell.h"

/**
 * _erratoi - changes string to integer
 * @r: is the string to be changed
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *r)
{
	int a = 0;
	unsigned long int result = 0;

	if (*r == '+')
		r++;
	for (a = 0;  r[a] != '\0'; a++)
	{
		if (r[a] >= '0' && r[a] <= '9')
		{
			result *= 10;
			result += (r[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints error message
 * @info: the parameter & return info struct
 * @est: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_err(info_t *info, char *est)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * print_dc - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fdi: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dc(int input, int fdi)
{
	int (*__putchar)(char) = _putchar;
	int v, count = 0;
	unsigned int _abs_, current;

	if (fdi == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (v = 1000000000; v > 1; v /= 10)
	{
		if (_abs_ / v)
		{
			__putchar('0' + current / v);
			count++;
		}
		current %= v;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - converter function,
 * @numb: is number
 * @base: is base
 * @flags: is argument flags
 *
 * Return: string
 */
char *convert_num(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long b = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		b = -numb;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[b % base];
		b /= base;
	} while (b != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - Substitutes instance of '#' with '\0'
 * @buf: address string to modify
 *
 * Return: Always 0;
 */
void remove_comment(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}
