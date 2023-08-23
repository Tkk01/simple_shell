#include "shell.h"

/**
 * _myhis - shows history list, command by line, preceded
 * numbers line, starting from 0.
 * @infor: Contains potential arguments. Maintains
 * constant function prototype.
 *  Return: Always 0
 */
int _myhis(info_t *infor)
{
	print_list(infor->history);
	return (0);
}

/**
 * unst_als - alias sets to string
 * @infor: parameter structure
 * @strg: the string alias
 *
 * Return: On success 0, 1 on error
 */
int unst_als(info_t *infor, char *strg)
{
	char *x, m;
	int reto;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	m = *x;
	*x = 0;
	reto = delete_node_at_index(&(infor->alias),
		get_node_index(infor->alias, node_starts_with(infor->alias, strg, -1)));
	*x = m;
	return (reto);
}

/**
 * set_als - alias sets to string
 * @infor: structure parameter
 * @strg: string alias
 *
 * Return: On success 0, 1 on error
 */
int set_als(info_t *infor, char *strg)
{
	char *d;

	d = _strchr(strg, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (unst_als(infor, strg));

	unst_als(infor, strg);
	return (add_node_end(&(infor->alias), strg, 0) == NULL);
}

/**
 * print_als - an alias string is printed
 * @nde: node of the alias
 *
 * Return: On success always 0, 1 on error
 */
int print_als(list_t *nde)
{
	char *b = NULL, *z = NULL;

	if (node)
	{
		b = _strchr(nde->str, '=');
		for (z = nde->str; z <= b; z++)
		_putchar(*z);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myals - represents alias builtin (man alias)
 * @infor: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: 0
 */
int _myals(info_t *infor)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (infor->argc == 1)
	{
		node = infor->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; infor->argv[a]; a++)
	{
		p = _strchr(infor->argv[a], '=');
		if (p)
			set_alias(infor, infor->argv[a]);
		else
			print_alias(node_starts_with(infor->alias, infor->argv[a], '='));
	}

	return (0);
}
