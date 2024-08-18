#include "shell.h"
/**
 * alloc_mngr - allocate space and archive allocations
 * @ptr: pointer to allocated memory
 * @size: size of desired allocation
  *
 * Return: pointer to allocated space on Success, NULL on fail
 */
char *alloc_mngr(char *ptr, size_t size)
{
	/* allocated space */
	ptr = _realloc(ptr, size);
	if (!(ptr)) /* check for alloc fail */
	{
		perror("hsh");
		free_mem_list(&mem_head);
		return (NULL);
	}

	/* archive allocation in list */
	mem_head = add_mem_node(&mem_head, ptr);

	/* return pointer to newly allocated mem */
	return (ptr);
}

/**
 * add_mem_node - link new node at beginning of list
 * @head: current list head
 * @ptr: pointer to store in new node
 *
 * Return: pointer to new list head
 */
mem_list *add_mem_node(mem_list **head, char *ptr)
{
	mem_list *new; /* ptr to new node */

	/* allocate for new node */
	new = malloc(sizeof(mem_list));
	if (!new)
		return (NULL);

	/* initialize new node */
	new->mem_ptr = ptr;
	new->next = *head;

	/* assign new node as list head */
	*head = new;

	return (*head);
}
/**
 * free_mem_list - free list and sety head to NULL
 * @head: pointer to struct to free
 */
void free_mem_list(mem_list **head)
{
	mem_list *temp;

	if (head)
	{
		while (*head)
		{
			temp = *head; /* assign temp pointer to current head */
			*head = (*head)->next; /* move head forward */
			if (temp->mem_ptr) /* pointer to allocation is not NULL */
				free(temp->mem_ptr); /* free allocation */
			free(temp); /* free node */
		}
		*head = NULL; /* restore head pointer to NULL */
	}
}
/**
 * _realloc - reallocate memory
 * @ptr: old allocation
 * @new_size: size of new alloc
 *
 * Return: newly alloc pointer on Succes, old pointer
 * if old and new size are equal, NULL on Fail
 */
char *_realloc(char *ptr, size_t new_size)
{
	char *re_ptr;
	size_t old_size = _strlen(ptr);
	size_t i = 0;

	/* check special cases */
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	/* allocate for new pointer */
	re_ptr = malloc(new_size);
	if (!re_ptr) /* check for alloc fail */
		return (NULL);

	/* copy old to new */
	if (ptr)
	{
		for (i = 0; i < old_size && i < new_size; i++)
			*(re_ptr + i) = *(ptr + i);

		/* free(ptr); free old pointer */
	}

	/* initialize new memory */
	_memset((re_ptr + old_size), 0, (new_size - old_size));

	/* return new pointer */
	return (re_ptr);
}
/**
 * _memset - fill memory with constant byte
 * @s: memory area to fill
 * @b: constant byte
 * @n: bytes to fill
 *
 * Return: pointer to memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}
