#include "shell.h"
/**
 * builtin_cd - change directory
 * @argv: command table
 *
 * Return: 0 on Success, -1 on Failure
 */
int builtin_cd(char *const *argv)
{
	/* if cd is only arg or has option "~" */
	if (argv[1] == NULL || !(_strcmp(argv[1], "~")))
	{
		if (cd_HOME()) /* move to HOME directory */
			return (-1); /* on failure */
	}
	else if (!(_strcmp(argv[1], "."))) /* if arg is ".", change to current dir */
	{
		if (cd_current()) /* move to PWD */
			return (-1); /* failed to move */
	}
	else if (!(_strcmp(argv[1], "-"))) /* if arg is "-", move to OLDPWD */
	{
		if (cd_prev()) /* move to OLDPWD */
			return (-1); /* failed to move */
	}
	else if (!(_strcmp(argv[1], ".."))) /* if arg is "..", move to parent dir */
	{
		if (cd_parent()) /* move to parent dir */
			return (-1); /* failed to move */
	} /* if arg is "~" and has chars following */
	else if ((!(_strncmp(argv[1], "~", 1)) && (argv[1][1] != '\0')))
	{
		if (cd_user(argv[1])) /* move to user home */
			return (-1); /* failed to move */
	}
	else
	{
		if (cd_arg(argv[1])) /* move to designated dir */
			return (-1); /* failure to change dir */
	}
	return (0); /* successful change of dir */
}
/**
 * cd_parent - move to parent directory
 * Return: 0 on Success, 1 on Failure
 */
int cd_parent(void)
{
	char *target_dir = NULL;
	size_t i;

	/* retrieve target path */
	target_dir = get_target("PWD=");
	if (target_dir) /* get current path */
	{
		/* move from end of path to first '/' */
		for (i = _strlen(target_dir); target_dir[i] != '/';)
			i--;
		/* iterate back to end, setting to ever byte to 0 */
		for (; target_dir[i]; i++)
			target_dir[i] = '\0';

		if (chdir(target_dir) == 0) /* move to parent dir */
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
	}

	return (-1); /* if get_target returns an error */
}
/**
 * cd_prev - move to previous directory
 * Return: 0 on Success, 1 on Failure
 */
int cd_prev(void)
{
	char *target_dir = NULL;

	/* retrieve target path */
	target_dir = get_target("OLDPWD=");
	if (target_dir) /* get OLDPWD path */
	{
		if (chdir(target_dir) == 0) /* change dir */
		{
			set_OLDPWD();
			set_PWD(target_dir);
			/* print new PWD to orient user */
			write(STDOUT_FILENO, target_dir, (_strlen(target_dir)));
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		else
			return (-1); /* if chdir fails */
	}

	return (-1); /* if get_target returns an error */
}
/**
 * cd_HOME - change to home directory
 * Return: 0 on Success, -1 on Failure
 */
int cd_HOME(void)
{
	char *target_dir = NULL;

	/* retrieve target path */
	target_dir = get_target("HOME=");
	if (target_dir) /* get home path */
	{
		if (chdir(target_dir) == 0) /* change dir */
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
		else
			return (-1); /* if chdir fails */
	}

	return (-1); /* if get_target returns an error */
}
/**
 * cd_current - move to current working directory
 * Return: 0 on Success, 1 on Failure
 */
int cd_current(void)
{
	char *target_dir = NULL;

	/* retrieve PWD path */
	target_dir = get_target("PWD=");
	if (target_dir) /* if path found */
	{
		if (chdir(target_dir) == 0) /* change dir */
		{
			set_OLDPWD();
			set_PWD(target_dir);
			return (0);
		}
		else
			return (-1); /* if chdir fails */
	}

	return (-1); /* if get_target returns an error */
}
