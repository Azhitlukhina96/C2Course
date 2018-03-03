// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Node
{
	int value;
	struct Node *next;
} Node;

typedef struct SearchResult
{
	int min;
	int max;
} SearchResult;

void push(Node **head, int data)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->value = data;
	tmp->next = (*head);
	(*head) = tmp;
}

void listall(Node *head)
{
	while(head)
	{
		printf("Value: %d;\n", head->value);
		head = head->next;
	}
}

SearchResult search_max_min(Node *head)
{
	SearchResult result;
	if (head)
	{
		result.max = head->value;
		result.min = head->value;
	}

	while (head)
	{

		if (result.min > head->value)
		{
			result.min = head->value;
		}

		if (result.max < head->value)
		{
			result.max = head->value;
		}

		head = head->next;

	}

	return result;

}

int ListSum(Node *head)
{
	int sum = 0;
	while (head)
	{
		sum = head->value + sum;
		head = head->next;
	}
	return sum;
}

int main()
{
	srand(time(0));

	Node *head = NULL;

	for (int i = 0; i <= 9; i++)
	{
		push(&head, rand()%10-6);
	}

	
	listall(head);

	
	printf("\nMaximum value in a row: %d;\n", search_max_min(head).max);
	printf("Minimum value in a row: %d;\n", search_max_min(head).min);

	printf("\nSum of all values: %d;\n", ListSum(head));

	return 0;
}

