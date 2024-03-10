#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct str_freq
{
	char *str;
	int count;
	struct str_freq *next;
} str_freq;

/**
 * get_distinct_k - A function to get the kth distinct string
 * @nodes: The head of a linked list storing the strings and
 * their frequency
 * @k: The term of the distinct string we seek
 * Return: The string at the kth unique position
 */

char *get_distinct_k(str_freq *nodes, int k)
{
	int unique = 0;

	while (nodes != NULL)
	{
		if (nodes->count == 1)
		{
			unique++;
			if (unique == k)
				return (nodes->str);
		}
		nodes = nodes->next;
	}
	return ("");
}

/**
 * add_new_node - A function to add a new node to the end of the
 * linked list
 * @nodes: The head of a linked list storing the strings and
 * their frequence
 * @str: The string for the new node
 */

void add_new_node(str_freq **nodes, char *str)
{
	str_freq *new_node;
	str_freq *current = *nodes;

	new_node = malloc(sizeof(str_freq));
	new_node->str = strdup(str);
	new_node->count = 1;
	new_node->next = NULL;
	if (*nodes == NULL)
		*nodes = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

/**
 * add_node - A function to check if a node is already present
 * if it is, the count is incremented by one
 * else a new node is created
 *
 * @node: The address of the nodes linked list
 * @str: The string we want to add to the new position
 */

void add_node(str_freq **node, char *str)
{
	int found = 0;
	str_freq *moving_node = *node;

	while (moving_node != NULL)
	{
		if (strcmp(moving_node->str, str) == 0)
		{
			found = 1;
			moving_node->count++;
			break;
		}
		moving_node = moving_node->next;
	}
	if (!found)
	{
		add_new_node(node, str);
	}
}

/**
 * main - The entry point to this program that finds the kth distinct string
 * Return: always 0 for successful
 */

int main(void)
{
	int n, k;
	int index;
	char *buff;
	size_t initial_buff_size = 0;
	ssize_t status;
	str_freq *nodes = NULL;
	str_freq *next_node;


	status = getline(&buff, &initial_buff_size, stdin);
	if (status > 0)
		n = atoi(buff);
	for (index = 0; index < n; index++)
	{
		status = getline(&buff, &initial_buff_size, stdin);
		if (status > 0)
		{
			add_node(&nodes, buff);
		}
	}
	status = getline(&buff, &initial_buff_size, stdin);
	if (status > 0)
		k = atoi(buff);
	free(buff);
	printf("%s", get_distinct_k(nodes, k));
	while (nodes != NULL)
	{
		next_node = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_node;
	}
	return (0);
}
