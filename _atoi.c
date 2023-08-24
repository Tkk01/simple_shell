#include "shell.h"

/**
 * interactive - prints true kama the shell is in interactive mode
 * @info: address of the structure
 *
 * Return: if in interactive mode return 1 otherwise give 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - confirms delimeter character
 * @c: the character in question
 * @delim: string of the delimeter
 * Return: If true return 1 otherwise return 0.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - looks out for characters that are alphabetic
 * @c: The character to type in
 * Return: if b is alphabetic then return 1, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && b <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string is conv to integer
 * @s: string conversion
 * Return: Print 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
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
