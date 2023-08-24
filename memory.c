#include "shell.h"

/**
 * bfree - pointer is free and addresses NULL
 * @ptr: indicates which pointer address to free
 *
 * Return: for freed 1, for not freed 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
