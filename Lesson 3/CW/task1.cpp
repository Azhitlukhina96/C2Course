// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void bubble_sort(int mas[],int size)
{
	clock_t time_begin = clock();
	int buf = 0;

	for (int i = 0; i < size; i++) 
	{            
		for (int j = size - 1; j > i; j--)
		{
			if (mas[j - 1] > mas[j])
			{
				buf = mas[j - 1];
				mas[j - 1] = mas[j];
				mas[j] = buf;
			}
		}
	}

	clock_t time_end = clock();
	printf("Time [SIZE: %d]: %.2fs\n", size, (double)(time_end - time_begin) / CLOCKS_PER_SEC);
}

int main()
{
	srand(time(0));

	int mas10[10];
	for (int i = 0; i < 10; i++)
	{
		mas10[i] = rand() % 30;
	}

	int mas100[100];
	for (int i = 0; i < 100; i++)
	{
		mas100[i] = rand() % 30;
	}

	int mas1000[1000];
	for (int i = 0; i < 1000; i++)
	{
		mas1000[i] = rand() % 30;
	}

	int mas10000[10000];
	for (int i = 0; i < 10000; i++)
	{
		mas10000[i] = rand() % 30;
	}

	int mas20000[20000];
	for (int i = 0; i < 20000; i++)
	{
		mas20000[i] = rand() % 30;
	}

	int mas50000[50000];
	for (int i = 0; i < 50000; i++)
	{
		mas50000[i] = rand() % 30;
	}

	int mas100000[100000];
	for (int i = 0; i < 100000; i++)
	{
		mas100000[i] = rand() % 30;
	}
	
	bubble_sort(mas10, 10);
	bubble_sort(mas100, 100);
	bubble_sort(mas1000, 1000);
	bubble_sort(mas10000, 10000);
	bubble_sort(mas20000, 20000);
	bubble_sort(mas50000, 50000);
	bubble_sort(mas100000, 100000);

    return 0;
}

