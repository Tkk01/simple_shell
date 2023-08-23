#include "shell.h"

/**
 * _myex - moves you out of the shell
 * @info: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: moves you out with given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myex(info_t *info)
{
	int excheck;

	if (info->argv[1]) /* If exists exit arguement */
	{
		excheck = _erratoi(info->argv[1]);
		if (excheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes current directory
 * @info: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *a, *dire, buffer[1024];
	int chdir_ret;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dire = _getenv(info, "HOME=");
		if (!dire)
			chdir_ret =
				chdir((dire = _getenv(info, "PWD=")) ? dire : "/");
		else
			chdir_ret = chdir(dire);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dire = _getenv(info, "OLDPWD=")) ? dire : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes directory
 * @info: Contains potential arguments. Maintains
 * constant function prototype.
 * Return: Always 0
 */
int _help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
