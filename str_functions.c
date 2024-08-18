#include "MyShell.h"

/**
 * _strdup - function that returns a pointer to a newly allocated space in
 * memory, which contains a copy of the string given as a parameter.
 *
 * @str: array
 *
 * Return: Pointer of a string copied.
 */
char *_strdup(char *str)
{
	int i, j;
	char *string;

	if (str == NULL)
		return (0);
	i = 0;

	while (*(str + i) != '\0')
		i++;
	string = malloc(i + 1);
	if (string == 0)
		return (0);
	for (j = 0; j < i; j++)
		*(string + j) = *(str + j);
	return (string);
}

/**
 * _strcat - FUnction will concatenate two strings
 * @dest: The caracter to print
 * @src: The word to print
 *Return: String concatenate.
 */

char *_strcat(char *dest, char *src)
{

	int i = 0, c = 0, n = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[c] != '\0')
	{
		c++;
	}
	while (n <= c)
	{
		dest[i] = src[n];
		n++;
		i++;
	}
	return (dest);
}

/**
 * _strlen - return the length of a string
 * @s: The caracter to print
 *
 *Return: return the number of character of a string.
 */
int _strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * _strcmp - String comparate
 * @s1: String One
 * @s2: String Two
 *
 *Return: The diference of the two string, if return 0 is the same string.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strcpy - copy a string.
 * @dest: Array Copied
 * @src: - Source of array
 * Return: the string copied.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = src[i];
	return (dest);

}
