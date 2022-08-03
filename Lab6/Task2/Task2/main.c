#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Circle Circle;

struct Circle
{
	int number;
	Circle* left;
	Circle* right;
};

int InputAndCheck(int, int);
void InputInformation(Circle**);
int OutputInformation(Circle*);
Circle* ChooseNext(int, Circle*);
Circle* DeleteStart(Circle*);
Circle* DeleteAny(Circle*, int);
int DeleteNegative(Circle**);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	printf("ВВОД КОЛЬЦА\n");
	Circle* start = NULL;
	InputInformation(&start);
	system("CLS");
	OutputInformation(start);
	int deleted = DeleteNegative(&start);
	if (deleted < 0)
		printf("Число %d было удалено!\n", deleted);
	else
		printf("Произошла ошибка!\n");
	OutputInformation(start);
	return 0;
}

int DeleteNegative(Circle** start)
{
	Circle* ptr = *start;
	do
	{
		int number = ptr->number;
		if (number < 0)
		{
			*start = DeleteAny(*start, number);
			return number;
		}
		ptr = ChooseNext(2, *start);
	} while (ptr != *start);
	return 1;
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

void InputInformation(Circle** start)
{
	Circle* s1;
	Circle* s2;
	int stop = 0;
	if (!*start)
	{
		s1 = (Circle*)malloc(1 * sizeof(Circle));
		if (!s1)
		{
			printf("Ошибка при создании кольца!\n");
			return;
		}
		printf("Введите элемент кольца:\n");
		s1->number = InputAndCheck(INT_MIN, INT_MAX);
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
		s2 = (Circle*)malloc(1 * sizeof(Circle));
		if (!s2)
		{
			printf("Ошибка при создании кольца!\n");
			return;
		}
		printf("Введите элемент кольца:\n");
		s2->number = InputAndCheck(INT_MIN, INT_MAX);
		s1->left = s2;
		s2->right = s1;
		s1 = s2;
		printf("Прекратить ввод?\n0 - нет\n1 - да\n");
		stop = InputAndCheck(0, 1);
	} while (!stop);
	s2->left = *start;
	(*start)->right = s2;
}

Circle* ChooseNext(int direction, Circle* start)
{
	switch (direction)
	{
	case 1:
		return start->right;
	case 2:
		return start->left;
	}
}

int OutputInformation(Circle* start)
{
	if (!start)
		return -1;
	Circle* s1 = start;
	printf("Как выводить числа из кольца:\n1 - по часовой стрелке\n2 - против часовой стрелки\n");
	int direction = InputAndCheck(1, 2);
	system("CLS");
	printf("Числа в кольце:\n");
	do
	{
		printf("%d\n", s1->number);
		s1 = ChooseNext(direction, s1);
	} while (s1 != start);
	return 1;
}

Circle* DeleteStart(Circle* start)
{
	Circle* s1;
	if (!start)
	{
		printf("Кольцо пустое!\n");
		return start;
	}
	s1 = start->right;
	if (start->right == start)
	{
		free(start);
		return NULL;
	}
	else
	{
		start->left->right = s1;
		s1->left = start->left;
		free(start);
		return s1;
	}
}

Circle* DeleteAny(Circle* start, int numForDelete)
{
	Circle* s1 = NULL;
	if (!start)
	{
		printf("Кольцо пустое!\n");
		return 0;
	}
	s1 = start;
	do
	{
		if (s1->number != numForDelete)
			s1 = s1->right;
		else
		{
			if (s1->right == s1)
			{
				free(s1);
				return NULL;
			}
			if (start == s1)
				start = start->right;
			s1->left->right = s1->right;
			s1->right->left = s1->left;
			free(s1);
			return start;
		}
	} while (s1 != start);
	printf("Число %d в кольце отсутсвует!\n", numForDelete);
	return start;
}