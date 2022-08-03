#include <stdio.h>
#include <Windows.h>
#include <limits.h>
#include <malloc.h>

typedef struct FirstQueue FirstQueue;
typedef struct SecondQueue SecondQueue;
typedef struct ResultQueue ResultQueue;

struct FirstQueue
{
	int number;
	FirstQueue* next;
	FirstQueue* prev;
};

struct SecondQueue
{
	int number;
	SecondQueue* next;
	SecondQueue* prev;
};

struct ResultQueue
{
	int number;
	ResultQueue* next;
	ResultQueue* prev;
};

int CleanAll(FirstQueue**, FirstQueue**);
int InputAndCheck(int, int);
void Push(FirstQueue**, FirstQueue**, int);
void Show(FirstQueue*, FirstQueue*);
void MakeAscendingResult(FirstQueue*, FirstQueue*, SecondQueue*, SecondQueue*);
void MakeDescendingResult(FirstQueue*, FirstQueue*, SecondQueue*, SecondQueue*);
void MakeOtherResult(FirstQueue*, FirstQueue*, SecondQueue*, SecondQueue*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("����� ������� ������� �����?\n1 - �� �����������\n2 - �� ��������\n3 - ������ ������� �� �����������, ������ - �� ��������\n");
	int typeOfInput = InputAndCheck(1, 3);
	switch (typeOfInput)
	{
	case 1:
	{
		system("CLS");
		printf("���� ������ ������� (�� �����������).\n");
		FirstQueue* firstHead = NULL;
		FirstQueue* firstTail = NULL;
		int number = INT_MIN;
		int stop = 0;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(number, INT_MAX);
			Push(&firstHead, &firstTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		printf("���� ������ ������� (�� �����������).\n");
		SecondQueue* secondHead = NULL;
		SecondQueue* secondTail = NULL;
		stop = 0;
		number = INT_MIN;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(number, INT_MAX);
			Push(&secondHead, &secondTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		system("CLS");
		printf("����� � ������ ������� (� ������):\n");
		Show(firstHead, firstTail);
		printf("����� �� ������ ������� (� ������):\n");
		Show(secondHead, secondTail);
		MakeAscendingResult(firstHead, firstTail, secondHead, secondTail);
		break;
	}
	case 2:
	{
		system("CLS");
		printf("���� ������ ������� (�� ��������).\n");
		FirstQueue* firstHead = NULL;
		FirstQueue* firstTail = NULL;
		int number = INT_MAX;
		int stop = 0;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(INT_MIN, number);
			Push(&firstHead, &firstTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		printf("���� ������ ������� (�� ��������).\n");
		SecondQueue* secondHead = NULL;
		SecondQueue* secondTail = NULL;
		stop = 0;
		number = INT_MAX;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(INT_MIN, number);
			Push(&secondHead, &secondTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		system("CLS");
		printf("����� � ������ ������� (� ������):\n");
		Show(firstHead, firstTail);
		printf("����� �� ������ ������� (� ������):\n");
		Show(secondHead, secondTail);
		MakeDescendingResult(firstHead, firstTail, secondHead, secondTail);
		break;
	}
	case 3:
	{
		system("CLS");
		printf("���� ������ ������� (�� �����������).\n");
		FirstQueue* firstHead = NULL;
		FirstQueue* firstTail = NULL;
		int number = INT_MIN;
		int stop = 0;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(number, INT_MAX);
			Push(&firstHead, &firstTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		printf("���� ������ ������� (�� ��������).\n");
		SecondQueue* secondHead = NULL;
		SecondQueue* secondTail = NULL;
		stop = 0;
		number = INT_MAX;
		do
		{
			printf("������� ����� �����:\n");
			number = InputAndCheck(INT_MIN, number);
			Push(&secondHead, &secondTail, number);
			printf("���������� ����?\n0 - ���\n1 - ��\n");
			stop = InputAndCheck(0, 1);
		} while (!stop);
		system("CLS");
		printf("����� � ������ ������� (� ������):\n");
		Show(firstHead, firstTail);
		printf("����� �� ������ ������� (� ������):\n");
		Show(secondHead, secondTail);
		MakeOtherResult(firstHead, firstTail, secondHead, secondTail);
		break;
	}
	}
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

void Push(FirstQueue** head, FirstQueue** tail, int number)
{
	FirstQueue* elem = (FirstQueue*)calloc(1, sizeof(FirstQueue));
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

int CleanAll(FirstQueue** head, FirstQueue** tail)
{
	if (!*head || !*tail)
		return 0;
	while (*head)
		*head = (*head)->next;
	while (*tail)
		*tail = (*tail)->prev;
	*head = *tail = NULL;
	return 1;
}

void Show(FirstQueue* head, FirstQueue* tail)
{
	if (!head)
	{
		printf("������� �����!\n");
		return;
	}
	FirstQueue* ptr = head;
	while (ptr)
	{
		printf("%d\n", ptr->number);
		ptr = ptr->next;
	}
}

void MakeDescendingResult(FirstQueue* firstHead, FirstQueue* firstTail, SecondQueue* secondHead, SecondQueue* secondTail)
{
	if (!firstHead || !secondHead)
	{
		printf("��������� ������!\n");
		return;
	}
	FirstQueue* firstPtr = firstHead;
	SecondQueue* secondPtr = secondHead;
	ResultQueue* resultHead = NULL;
	ResultQueue* resultTail = NULL;
	while (firstPtr && secondPtr)
	{
		int firstNumber = firstPtr->number;
		int secondNumber = secondPtr->number;
		if (firstPtr->number > secondPtr->number)
		{
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
		else
		{
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->next;
		}
	}
	if (!firstPtr)
	{
		while (secondPtr)
		{

			int secondNumber = secondPtr->number;
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->next;
		}
	}
	if (!secondPtr)
	{
		while (firstPtr)
		{
			int firstNumber = firstPtr->number;
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
	}
	printf("����� � ����� ������� �� �������� (� ������):\n");
	ResultQueue* resultPtr = resultHead;
	if (CleanAll(&firstHead, &firstTail))
	{
		while (resultPtr)
		{
			int number = resultPtr->number;
			Push(&firstHead, &secondHead, number);
			resultPtr = resultPtr->next;
		}
	}
	printf("����� � ����� ������� �� ����������� (� ������):\n");
	Show(firstHead, firstTail);
}

void MakeAscendingResult(FirstQueue* firstHead, FirstQueue* firstTail, SecondQueue* secondHead, SecondQueue* secondTail)
{
	if (!firstHead || !secondHead)
	{
		printf("��������� ������!\n");
		return;
	}
	FirstQueue* firstPtr = firstHead;
	SecondQueue* secondPtr = secondHead;
	ResultQueue* resultHead = NULL;
	ResultQueue* resultTail = NULL;
	while (firstPtr && secondPtr)
	{
		int firstNumber = firstPtr->number;
		int secondNumber = secondPtr->number;
		if (firstPtr->number < secondPtr->number)
		{
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
		else
		{
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->next;
		}
	}
	if (!firstPtr)
	{
		while (secondPtr)
		{

			int secondNumber = secondPtr->number;
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->next;
		}
	}
	if (!secondPtr)
	{
		while (firstPtr)
		{
			int firstNumber = firstPtr->number;
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
	}
	ResultQueue* resultPtr = resultHead;
	if (CleanAll(&firstHead, &firstTail))
	{
		while (resultPtr)
		{
			int number = resultPtr->number;
			Push(&firstHead, &secondHead, number);
			resultPtr = resultPtr->next;
		}
	}
	printf("����� � ����� ������� �� ����������� (� ������):\n");
	Show(firstHead, firstTail);
}

void MakeOtherResult(FirstQueue* firstHead, FirstQueue* firstTail, SecondQueue* secondHead, SecondQueue* secondTail)
{
	if (!firstHead || !secondHead)
	{
		printf("��������� ������!\n");
		return;
	}
	FirstQueue* firstPtr = firstHead;
	SecondQueue* secondPtr = secondTail;
	ResultQueue* resultHead = NULL;
	ResultQueue* resultTail = NULL;
	while (firstPtr && secondPtr)
	{
		int firstNumber = firstPtr->number;
		int secondNumber = secondPtr->number;
		if (firstPtr->number < secondPtr->number)
		{
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
		else
		{
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->prev;
		}
	}
	if (!firstPtr)
	{
		while (secondPtr)
		{

			int secondNumber = secondPtr->number;
			Push(&resultHead, &resultTail, secondNumber);
			secondPtr = secondPtr->prev;
		}
	}
	if (!secondPtr)
	{
		while (firstPtr)
		{
			int firstNumber = firstPtr->number;
			Push(&resultHead, &resultTail, firstNumber);
			firstPtr = firstPtr->next;
		}
	}
	printf("����� � ����� ������� �� ����������� (� ������):\n");
	ResultQueue* resultPtr = resultHead;
	if (CleanAll(&firstHead, &firstTail))
	{
		while (resultPtr)
		{
			int number = resultPtr->number;
			Push(&firstHead, &secondHead, number);
			resultPtr = resultPtr->next;
		}
	}
	printf("����� � ����� ������� �� ����������� (� ������):\n");
	Show(firstHead, firstTail);
}