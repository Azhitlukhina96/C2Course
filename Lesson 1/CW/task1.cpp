// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>


struct transaction
{
	int id;
	int price;
	char description[500];
	int amount_goods;
};

void print_price(struct transaction check[], int size)
{
	for (int i = 0; i < size-1; i++)
	{
		printf("\n\n==========================\n");
		printf("\nTransaction ID: %d;\nPrice: %d;\nGoods:%s;\nAmount of goods: %d;\n", check[i].id, check[i].price, check[i].description, check[i].amount_goods);
		printf("\n==========================\n");
	}
}

int max_goods(struct transaction check[], int size)
{
	int max_g = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (max_g < check[i].amount_goods)
		{
			max_g = check[i].amount_goods;
		}
	}


	printf("\n\n\n|||LOYAL PROGRAM||| \n\n");

	for (int i = 0; i < size - 1; i++)
	{
		if (max_g == check[i].amount_goods)
		{
			printf("\n\n==========================\n");
			printf("\nTransaction ID: %d;\nPrice: %d;\nGoods:%s;\nAmount of goods: %d;\n", check[i].id, check[i].price, check[i].description, check[i].amount_goods);
			printf("\n==========================\n");
		}
	}
	return max_g;
}

void min_goods(struct transaction check[], int size)
{
	int min_g = 50;

	for (int i = 0; i < size - 1; i++)
	{
		if (min_g > check[i].amount_goods)
		{
			min_g = check[i].amount_goods;
		}
	}


	printf("\n\n\n|||MINIMAL GOODS||| \n\n");

	for (int i = 0; i < size - 1; i++)
	{
		if (min_g == check[i].amount_goods)
		{
			printf("\n\n==========================\n");
			printf("\nTransaction ID: %d;\nPrice: %d;\nGoods:%s;\nAmount of goods: %d;\n", check[i].id, check[i].price, check[i].description, check[i].amount_goods);
			printf("\n==========================\n");
		}
	}

}

float avg_price(struct transaction check[], int size)
{
	float price = 0;
	for (int i = 0; i < size - 1; i++)
	{
		price = price + check[i].price;
	}

	float result = price / (size - 1);
	return result;

}

int check_amount(struct transaction check, int size)
{
	int amount = 0;
	int len = strlen(check.description);

	for (int j = 0; j < len; j++)

	{
		if (check.description[j] == ',')
		{
			amount++;
		}
	}
	return (amount + 1);
}

void search(struct transaction check[], int size)
{
	printf("\n\n\n|||SEARCH GOODS||| \n\n");
	char search[32];
	printf("Good name: ");
	scanf_s("%32s", search, 32);
	char *sub_string = NULL;
	for (int i = 0; i < size; i++)
	{
		sub_string = strstr(check[i].description, search);
		if (sub_string != NULL)
		{
			printf("\n\n==========================\n");
			printf("\nTransaction ID: %d;\nPrice: %d;\nGoods:%s;\nAmount of goods: %d;\n", check[i].id, check[i].price, check[i].description, check[i].amount_goods);
			printf("\n==========================\n");
		}
	}
}

int main()
{
	FILE *file;

	struct transaction *check;
	struct transaction *cbuf;
	struct transaction one_check;

	int size = 1;
	int i = 0;

	check = (transaction*)malloc(sizeof(transaction)*size);
	cbuf = (transaction*)malloc(sizeof(transaction)*size);


	errno_t err;
	err = fopen_s(&file, "C:\\Users\\uc2\\Desktop\\files\\transactions.txt", "r");
	if (err)
		printf_s("The file cannot open \n");
	else
	{
		while (fscanf_s(file, "%d;%d;%500s", &one_check.id, &one_check.price, one_check.description, 500) != EOF)
		{
			check[i].id = one_check.id;
			check[i].price = one_check.price;
			strcpy_s(check[i].description, one_check.description);
			check[i].amount_goods = check_amount(check[i], size);
			i++;

			if (i == size)
			{
				size = size + 1;

				cbuf = (transaction*)realloc(check, size * sizeof(transaction));
				check = cbuf;
			}
		}
	}

	print_price(check, size);
	printf("\nAverage price: %.2f USD;\n", avg_price(check, size));

	max_goods(check, size);
	min_goods(check, size);
	search(check, size);





    return 0;
}

