#include "shell.h"
/**
 * free_static_mem_list - free list and sety head to NULL
 * @head: pointer to list to free
 */
void free_static_mem_list(mem_list **head)
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
