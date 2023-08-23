#include "shell.h"

/**
 * _myenviron - the environment is printed
 * @infor: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: 0
 */
int _myenviron(info_t *infor)
{
	print_list_str(infor->env);
	return (0);
}

/**
 * _getenvir - fetches value of environ variable
 * @infor: COntains potential arguments. Maintains constant function prototype.
 * @name: environ variable name
 *
 * Return: the value
 */
char *_getenvir(info_t *infor, const char *name)
{
	list_t *node = infor->env;
	char *b;

	while (node)
	{
		b = starts_with(node->str, name);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenviron - Ejects environment variable
 * @infor: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetenviron(info_t *infor)
{
	int v;

	if (infor->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (v = 1; v <= info->argc; v++)
		_unsetenv(info, info->argv[v]);

	return (0);
}

/**
 * populate_environ_list - populates linked list
 * @info: Contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_environ_list(info_t *info)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	info->env = node;
	return (0);
}
