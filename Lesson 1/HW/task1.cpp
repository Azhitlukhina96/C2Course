// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct transaction
{
	int id;
	int price;
	char description[500];
	int amount_goods;
};

struct buffid
{
	int id;
	int price;
};

float avg_min_max(struct transaction check[], int size)
{
	float price = 0;
	int min_g = 50;
	int max_g = 0;


	for (int i = 0; i < size - 1; i++)
	{

		//printf("\n\n==========================\n");
		//printf("\nTransaction ID: %d;\nPrice: %d;\nGoods:%s;\nAmount of goods: %d;\n", check[i].id, check[i].price, check[i].description, check[i].amount_goods);
		//printf("\n==========================\n");

		price = price + check[i].price;

		if (min_g > check[i].amount_goods)
		{
			min_g = check[i].amount_goods;
		}

		if (max_g < check[i].amount_goods)
		{
			max_g = check[i].amount_goods;
		}
	}

	printf("\nMax goods: %d", max_g);
	printf("\nMin goods: %d\n", min_g);
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

void sort_insert(struct buffid list[], int size)
{
	int counter = 0;
	int tmp = 0;
	for (int i = 1; i < size - 1; i++)
	{
		for (int j = i; j > 0 && list[j - 1].price > list[j].price; j--)
		{
			tmp = list[j - 1].price;
			list[j - 1].price = list[j].price;
			list[j].price = tmp;
		}
	}
}

int main()
{
	FILE *file;

	struct transaction *check;
	struct transaction *cbuf;
	struct transaction one_check;
	struct buffid *mainbuf;

	int size = 1;
	int i = 0;

	check = (transaction*)malloc(sizeof(transaction)*size);
	cbuf = (transaction*)malloc(sizeof(transaction)*size);


	clock_t time_begin = clock();
	errno_t err;
	err = fopen_s(&file, "C:\\Users\\User\\Desktop\\all_transactions.txt", "r");
	if (err)
		printf_s("The file cannot open \n");
	else
	{
		while (fscanf_s(file, "%d;%d;%500s", &check[i].id, &check[i].price, check[i].description, 500) != EOF)
		{
			check[i].amount_goods = check_amount(check[i], size);
			i++;

			if (i == size)
			{
				size = size + size * 10;

				cbuf = (transaction*)realloc(check, size * sizeof(transaction));
				check = cbuf;
			}
		}
	}
	clock_t time_end = clock();
	printf("Time [file reading took]: %.2fs;\n", (double)(time_end - time_begin) / CLOCKS_PER_SEC);

	size = i + 1;

	mainbuf = (buffid*)malloc(sizeof(buffid)*size);

	for (int i = 0; i < size; i++)
	{
		mainbuf[i].id = check[i].id;
		mainbuf[i].price = check[i].price;
	}

	//print_price(check, size);
	printf("\nAverage price: %.2f USD;\n", avg_min_max(check, size));

	printf("Operations amount: %d;\n", mainbuf[size - 2].id);

	sort_insert(mainbuf, size);

	clock_t end = clock();
	printf("Time [took to complete program]: %.2fs;\n", (double)(end - time_end) / CLOCKS_PER_SEC);

	search(check, size);



	return 0;
}
