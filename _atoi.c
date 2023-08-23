#include "shell.h"

/**
 * intctve - true if in interactive  mode
 * @info: structure address
 *
 * Return: interactive mode returns 1 anything else is 0
 */
int intctve(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checksif it is a delimeter
 * @x: the character to check
 * @delim: delimeter string
 * Return: if true returns 1, 0 if false
 */
int is_delimeter(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @f: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int f)
{
	if ((f >= 'a' && f <= 'z') || (f >= 'A' && f <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoxam - changes string to integer
 * @s: conversion of string
 * Return: 0 if in string there is no number, otherwise number converted
 */

int _atoxam(char *s)
{
	int q, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (q = 0; s[q] != '\0' && flag != 2; i++)
	{
		if (s[q] == '-')
			sign *= -1;

		if (s[q] >= '0' && s[q] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
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
