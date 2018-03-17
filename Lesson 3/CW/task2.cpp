// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node
{
	int id;
	int value;
	char goods[511];
	struct node *next;
} node;

void merge(node *a, node *b, node **c)
{
	node tmp;
	*c = NULL;
	if (a == NULL) {
		*c = b;
		return;
	}
	if (b == NULL) {
		*c = a;
		return;
	}
	if (a->value < b->value) {
		*c = a;
		a = a->next;
	}
	else {
		*c = b;
		b = b->next;
	}
	tmp.next = *c;
	while (a && b) {
		if (a->value < b->value) {
			(*c)->next = a;
			a = a->next;
		}
		else {
			(*c)->next = b;
			b = b->next;
		}
		(*c) = (*c)->next;
	}
	if (a) {
		while (a) {
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}
	if (b) {
		while (b) {
			(*c)->next = b;
			(*c) = (*c)->next;
			b = b->next;
		}
	}
	*c = tmp.next;
}

void push(node **head, int id, int value, char goods[])
{
	node *tmp = (node*)malloc(sizeof(node));
	tmp->id = id;
	tmp->value = value;
	strcpy_s(tmp->goods, goods);
	tmp->next = (*head);
	(*head) = tmp;
}

void print_node(node *head)
{
	printf("\n----------\n");
	printf("ID: %d;\nPrice: %d;\nGoods: %s;", head->id, head->value, head->goods, 511);
	printf("\n----------\n");
}

void listall(node *head)
{
	while (head)
	{
		printf("\n----------\n");
		printf("ID: %d;\nPrice: %d;\nGoods: %s;", head->id, head->value, head->goods, 511);
		printf("\n----------\n");
		head = head->next;
	}
}

int main()
{
	FILE *file;
	int id = 0;
	int value = 0;
	char goodlist[511];
	node *head = NULL;

	errno_t err;
	err = fopen_s(&file, "C:\\Users\\uc2\\Desktop\\transactions.txt", "r");
	if (err)
		printf_s("The file cannot open \n");
	else
	{
		while (fscanf_s(file, "%d;%d;%511s", &id, &value, goodlist, 511) != EOF)
		{
			node *new_node = (node*)malloc(sizeof(node));
			new_node->id = id;
			new_node->value = value;
			new_node->next = NULL;
			merge(new_node, head, &head);
			
			strcpy_s(new_node->goods, goodlist);
			//print_node(new_node);
		}
	}

	listall(head);

    return 0;
}

