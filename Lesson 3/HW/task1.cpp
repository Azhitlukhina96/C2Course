// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<cstdio>
#include<stdlib.h>
#include<string>
#include <locale>
#include <math.h>

typedef struct Int_Stack
{
	int n;
	struct Int_Stack *next;
}Int_Stack;

typedef struct Stack
{
	char c;
	struct Stack *next;
}Stack;

Int_Stack* push(Int_Stack *head, int a)
{
	Int_Stack *pointer;
	pointer = (Int_Stack*)malloc(sizeof(Int_Stack));
	pointer->n = a;
	pointer->next = head;
	return pointer;
}

Stack* push(Stack *head, char a)
{
	Stack *pointer;
	pointer = (Stack*)malloc(sizeof(Stack));
	pointer->c = a;
	pointer->next = head;
	return pointer;
}

int pop(Int_Stack **head)
{
	Int_Stack *pointer;
	int a;
	if (*head == NULL)
		return '\0';
	pointer = *head;
	a = pointer->n;
	*head = pointer->next;
	free(pointer);
	return a;
}

char pop(Stack **head)
{
	Stack *pointer;
	char a;
	if (*head == NULL)
		return '\0';
	pointer = *head;
	a = pointer->c;
	*head = pointer->next;
	free(pointer);
	return a;
}

int prior(char a)
{
	switch (a)
	{
	case '*':
	case '/':
		return 3;
	case '-':
	case '+':
		return 2;
	case '(':
		return 1;
	}
}

int string_to_number(char* input_string)
{
	int result = 0;
	int k = 0, i = 10;
	while (input_string[k] != '\0')
	{
		result = result * i + (input_string[k] - '0');
		k++;
	}
	return result;
}

const int BUFFER_SIZE = 100;

bool parse(char *input_string, int &result)
{
	char number[15];
	Int_Stack* stack = NULL;
	int k = 0, i = 0;
	int r1, r2;
	bool is_Number = true;
	while (input_string[k] != '\0')
	{
		if (input_string[k] >= '0' && input_string[k] <= '9')
		{
			while (input_string[k] != '|')
			{
				number[i] = input_string[k];
				k++;
				i++;
			}
			number[i] = '\0';
			stack = push(stack, string_to_number(number));
			k++;
			i = 0;
		}
		else
		{
			r2 = pop(&stack);
			r1 = pop(&stack);
			switch (input_string[k])
			{
			case '+': result = r1 + r2; stack = push(stack, result);
				break;
			case '-': result = r1 - r2; stack = push(stack, result);
				break;
			case '*': result = r1 * r2; stack = push(stack, result);
				break;
			case '/': if (r2 == 0) return false; result = r1 / r2; stack = push(stack, result);
				break;
			}
			k++;
		}
	}
	if (stack != NULL)
	{
		result = pop(&stack);
	}
	return true;
}

char* polish_notation(char *input_string)
{
	Stack *operands = NULL;
	char *output_string = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	int k, point;
	k = point = 0;
	while (input_string[k] != '\0' && input_string[k] != '\n')
	{
		if (input_string[k] == ')')
		{
			while ((operands->c) != '(')
				output_string[point++] = pop(&operands);
			pop(&operands);
		}

		if (input_string[k] >= '0' && input_string[k] <= '9')
		{
			output_string[point++] = input_string[k];
			if (input_string[k + 1]<'0' || input_string[k + 1]>'9')
				output_string[point++] = '|';
		}
		if (input_string[k] == '(')
			operands = push(operands, '(');
		if (input_string[k] == '+' || input_string[k] == '-' || input_string[k] == '/' || input_string[k] == '*')
		{
			if (operands == NULL)
				operands = push(operands, input_string[k]);
			else
				if (prior(operands->c) < prior(input_string[k]))
					operands = push(operands, input_string[k]);
				else
				{
					while ((operands != NULL) && (prior(operands->c) >= prior(input_string[k])))
					{
						output_string[point++] = pop(&operands);
					}
					operands = push(operands, input_string[k]);
				}
		}
		k++;
	}
	while (operands != NULL)
		output_string[point++] = pop(&operands);
	output_string[point] = '\0';
	return output_string;
}

int main()
{
	FILE *operations_file;
	FILE *result_file;
	printf_s("Trying to open a file: operations.txt ...\n");
	errno_t err = fopen_s(&operations_file, "E:\\operations.txt", "r");
	if (err)
	{
		printf_s("The file operations.txt was not opened\n");
		return 0;
	}
	printf_s("Success\n");
	printf_s("Trying to open a file: result.txt ...\n");
	err = fopen_s(&result_file, "E:\\result.txt", "w");
	if (err)
	{
		printf_s("The file result.txt was not opened\n");
		return 0;
	}
	printf_s("Success\n");
	printf_s("Processing data ...\n");
	char *buffer;
	buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	char *polish_string;
	int result;
	while (fgets(buffer, BUFFER_SIZE, operations_file) != NULL)
	{
		polish_string = polish_notation(buffer);
		if (parse(polish_string, result))
			fprintf(result_file, "%d\n", result);
		else
			fprintf(result_file, "NaN\n");
	}
	printf_s("Success\n");
	printf_s("The result was wtitten into result.txt file\n");

	return 0;
}
