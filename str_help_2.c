#include "shell.h"
/**
 * _revstr - reverse string
 * @s: string to reverse
 *
 * Return: reversed string
 */
char *_revstr(char *s)
{
	int i = 0, j = 0, length = 0, half = 0;
	char *rev = s;
	char buff;

	length = _strlen(s);

	if (length % 2 == 0)
		half = length / 2;
	else
		half = (length - 1) / 2;
	for (i = length - 1; i >= half; j++, i--)
	{
		buff = rev[j];
		rev[j] = s[i];
		s[i] = buff;
	}
	return (s);
}
