#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Queue Queue;

struct Queue
{
	Queue* next;
	Queue* prev;
	int number;
};

int InputAndCheck(int, int);
void InputQueue(Queue**, Queue**, int);
void Show(Queue*, Queue*, int);
int Clean(Queue**, Queue**, int);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Queue* head = NULL;
	Queue* tail = NULL;
	printf("������� ���������� ����� ��� �������������� ������ � �������:\n");
	int numbersAmount = InputAndCheck(1, INT_MAX);
	for (int i = 0; i < numbersAmount; i++)
	{
		printf("������� ����� ��� ������ � �������:\n");
		int number = InputAndCheck(INT_MIN, INT_MAX);
		InputQueue(&head, &tail, number);
	}
	system("CLS");
	printf("���� �������� �����?\n1 - � �������\n2 - � �������\n");
	int inputType = InputAndCheck(1, 2);
	system("CLS");
	switch (inputType)
	{
	case 1:
	{
		int stop = 0;
		do
		{
			printf("������� �����:\n");
			int newNumber = InputAndCheck(INT_MIN, INT_MAX);  // 1 2 3 4 5 =>  4 5 1 2
			int headNumber = head->number;
			int status = Clean(&head, &tail, 4);
			if (status == 0)
				printf("������� �����!\n");
			else
			{
				if (newNumber == headNumber)
					InputQueue(&head, &tail, newNumber);
			}
			printf("���������?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		break;
	}
	case 2:
	{
		int stop = 0;
		do
		{
			printf("������� �����:\n");
			int newNumber = InputAndCheck(INT_MIN, INT_MAX);  // 1 2 3 4 5 =>  4 5 1 2
			InputQueue(&head, &tail, newNumber);
			int headNumber = head->number;
			int status = Clean(&head, &tail, 4);
			if (status == 0)
				printf("������� �����!\n");
			else
			{
				if (newNumber == headNumber)
					InputQueue(&head, &tail, newNumber);
			}
			printf("���������?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		break;
	}
	}
	Show(head, tail, 2);
	return 0;
}

int InputAndCheck(int minValue, int maxValue)
{
	int number, check;
	check = scanf_s("%d", &number);
	while (!check || number < minValue || number > maxValue)
	{
		rewind(stdin);
		printf("������. ��������� ����:\n");
		check = scanf_s("%d", &number);
	}
	return number;
}

void InputQueue(Queue** head, Queue** tail, int number)
{
	Queue* elem = (Queue*)calloc(1, sizeof(Queue));
	if (!elem)
	{
		printf("��������� ������ ��� ��������� ������!\n");
		return;
	}
	elem->number = number;
	if (!*head)
		*head = *tail = elem;
	else
	{
		(*tail)->next = elem;
		elem->prev = *tail;
		*tail = elem;
	}
}

void Show(Queue* head, Queue* tail, int variant)
{
	system("CLS");
	if (!head)
	{
		printf("������� �����!\n");
		return;
	}
	if (variant == 2)
	{
		Queue* ptr = head;
		printf("����� � ������� (� ������):\n");
		while (ptr)
		{
			printf("%d\n", ptr->number);
			ptr = ptr->next;
		}
	}
	else if (variant == 3)
	{
		Queue* ptr = tail;
		printf("����� � ������� (� ������):\n");
		while (ptr)
		{
			printf("%d\n", ptr->number);
			ptr = ptr->prev;
		}
	}
}

int Clean(Queue** head, Queue** tail, int variant)
{
	if (!*head || !*tail)
		return 0;
	if (variant == 4)
	{
		Queue* temp = (Queue*)calloc(1, sizeof(Queue));
		if (!temp)
			return -1;
		temp = (*head)->next;
		temp->prev = NULL;
		free(*head);
		*head = temp;
		return 1;
	}
	else
	{
		Queue* temp = (Queue*)calloc(1, sizeof(Queue));
		if (!temp)
			return -1;
		temp = (*tail)->prev;
		temp->next = NULL;
		free(*tail);
		*tail = temp;
		return 1;
	}
}