#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct FirstCircle FirstCircle;
typedef struct SecondCircle SecondCircle;
typedef struct ResultCircle ResultCircle;

struct FirstCircle
{
	int number;
	FirstCircle* left;
	FirstCircle* right;
};

struct SecondCircle
{
	int number;
	SecondCircle* left;
	SecondCircle* right;
};

struct ResultCircle
{
	int number;
	ResultCircle* left;
	ResultCircle* right;
};

int InputAndCheck(int, int);
void InputInformation(FirstCircle**);
void PushResult(ResultCircle**, int);
int OutputInformation(FirstCircle*);
FirstCircle* ChooseNext(int, FirstCircle*);
void MakeNewCircle(FirstCircle**, SecondCircle**, ResultCircle**);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	printf("ВВОД ПЕРВОГО КОЛЬЦА (ПО ВОЗРАСТАНИЮ)\n");
	FirstCircle* firstStart = NULL;
	InputInformation(&firstStart);
	system("CLS");
	printf("ВВОД ВТОРОГО КОЛЬЦА (ПО ВОЗРАСТАНИЮ)\n");
	SecondCircle* secondStart = NULL;
	InputInformation(&secondStart);
	system("CLS");
	printf("ПЕРВОЕ КОЛЬЦО:\n");
	OutputInformation(firstStart);
	printf("ВТОРОЕ КОЛЬЦО:\n");
	OutputInformation(secondStart);
	ResultCircle* resultStart = NULL;
	MakeNewCircle(&firstStart, &secondStart, &resultStart);
	printf("РЕЗУЛЬТАТ\n");
	OutputInformation(resultStart);
	return 0;
}

int InputAndCheck(int minValue, int maxValue)
{
	int number, check;
	check = scanf_s("%d", &number);
	while (!check || number < minValue || number > maxValue)
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &number);
	}
	return number;
}

void InputInformation(FirstCircle** start)
{
	FirstCircle* s1;
	FirstCircle* s2;
	int stop = 0;
	int number = INT_MIN;
	if (!*start)
	{
		s1 = (FirstCircle*)malloc(1 * sizeof(FirstCircle));
		if (!s1)
		{
			printf("Ошибка при создании кольца!\n");
			return;
		}
		printf("Введите элемент кольца:\n");
		number = InputAndCheck(number, INT_MAX);
		s1->number = number;
		s1->left = s1->right = s1;
		*start = s1;
		printf("Прекратить ввод?\n0 - нет\n1 - да\n");
		stop = InputAndCheck(0, 1);
		if (stop)
			return;
	}
	else
		s1 = (*start)->right;
	do
	{
		s2 = (FirstCircle*)malloc(1 * sizeof(FirstCircle));
		if (!s2)
		{
			printf("Ошибка при создании кольца!\n");
			return;
		}
		printf("Введите элемент кольца:\n");
		number = InputAndCheck(number, INT_MAX);
		s2->number = number;
		s1->left = s2;
		s2->right = s1;
		s1 = s2;
		printf("Прекратить ввод?\n0 - нет\n1 - да\n");
		stop = InputAndCheck(0, 1);
	} while (!stop);
	s2->left = *start;
	(*start)->right = s2;
}

FirstCircle* ChooseNext(int direction, FirstCircle* start)
{
	switch (direction)
	{
	case 1:
		return start->right;
	case 2:
		return start->left;
	}
}

int OutputInformation(FirstCircle* start)
{
	if (!start)
		return -1;
	FirstCircle* s1 = start;
	printf("Как выводить числа из кольца:\n1 - по часовой стрелке\n2 - против часовой стрелки\n");
	int direction = InputAndCheck(1, 2);
	printf("Числа в кольце:\n");
	do
	{
		printf("%d\n", s1->number);
		s1 = ChooseNext(direction, s1);
	} while (s1 != start);
	return 1;
}

void PushResult(ResultCircle** start, int number)
{
	ResultCircle* s1;
	ResultCircle* s2;
	if (!*start)
	{
		s1 = (ResultCircle*)malloc(1 * sizeof(ResultCircle));
		if (!s1)
		{
			printf("Ошибка при создании кольца!\n");
			return;
		}
		s1->number = number;
		s1->left = s1->right = s1;
		*start = s1;
		return;
	}
	else
		s1 = (*start)->right;
	s2 = (ResultCircle*)malloc(1 * sizeof(ResultCircle));
	if (!s2)
	{
		printf("Ошибка при создании кольца!\n");
		return;
	}
	s2->number = number;
	s1->left = s2;
	s2->right = s1;
	s1 = s2;
	s2->left = *start;
	(*start)->right = s2;
}

void MakeNewCircle(FirstCircle** firstStart, SecondCircle** secondStart, ResultCircle** resultStart)
{
	FirstCircle* firstPtr = *firstStart;
	SecondCircle* secondPtr = *secondStart;
	FirstCircle* firstTemp = firstPtr;
	SecondCircle* secondTemp = secondPtr;
	do
	{
		int firstNum = firstPtr->number;
		int secondNum = secondPtr->number;
		if (firstNum < secondNum)
		{
			PushResult(resultStart, firstNum);
			firstPtr = firstPtr->left;
			if (firstPtr == *firstStart)
				firstTemp = NULL;
		}
		else if (firstNum > secondNum)
		{
			PushResult(resultStart, secondNum);
			secondPtr = secondPtr->left;
			if (secondPtr == *secondStart)
				secondTemp = NULL;
		}
		else
		{
			firstPtr = firstPtr->left;
			if (firstPtr == *firstStart)
				firstTemp = NULL;
			secondPtr = secondPtr->left;
			if (secondPtr == *secondStart)
				secondTemp = NULL;
		}
	} while (firstTemp && secondTemp);
	if (firstPtr == *firstStart)
	{
		while (secondPtr != *secondStart)
		{
			PushResult(resultStart, secondPtr->number);
			secondPtr = secondPtr->left;
		}
	}
	else if (secondPtr == *secondStart)
	{
		while (firstPtr != *firstStart)
		{
			PushResult(resultStart, firstPtr->number);
			firstPtr = firstPtr->left;
		}
	}
}

