#include "functions.h"

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

int FileToCircle(Circle** start, char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file)
		return -1;
	int number;
	Circle* s1 = NULL;
	Circle* s2 = NULL;
	while (!feof(file))
	{
		if (fscanf(file, "%d", &number) > 0)
		{
			if (!*start)
			{
				s1 = (Circle*)malloc(1 * sizeof(Circle));
				if (!s1)
				{
					printf("Ошибка при создании кольца!\n");
					return -2;
				}
				s1->number = number;
				s1->left = s1->right = s1;
				*start = s1;
			}
			else
			{
				s1 = (*start)->right;
				s2 = (Circle*)malloc(1 * sizeof(Circle));
				if (!s2)
				{
					printf("Ошибка при создании кольца!\n");
					return -2;
				}
				s2->number = number;
				s1->left = s2;
				s2->right = s1;
				s2->left = *start;
				(*start)->right = s2;
			}
		}
	}
	return 1;
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

Circle* DeleteAny(Circle* start)
{
	Circle* s1 = NULL;
	if (!start)
	{
		printf("Кольцо пустое!\n");
		return 0;
	}
	s1 = start;
	printf("Введите число, которое необходимо удалить:\n");
	int numForDelete = InputAndCheck(INT_MIN, INT_MAX);
	system("CLS");
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

Circle* PtrSort(Circle* start)
{
	if (!start)
	{
		printf("Кольцо пустое!\n");
		return start;
	}
	Circle* s1;
	Circle* s2;
	Circle* s3;
	int i;
	s1 = start;
	do
	{
		s2 = s1->right;
		s3 = s1;
		do
		{
			if (s3->number < s2->number)
				s3 = s2;
			s2 = s2->right;
		} while (s2 != start);
		if (s3 != s1)
		{
			if (start == s1)
				start = s3;
			s3->left->right = s3->right;
			s3->right->left = s3->left;
			s1->left->right = s3;
			s3->right = s1;
			s3->left = s1->left;
			s1->left = s3;
		}
		else
			s1 = s1->right;
	} while (s1->right != start);
	return start;
}

void ValueSort(Circle* start)
{
	if (!start)
	{
		printf("Кольцо пустое!\n");
		return;
	}
	Circle* s1;
	Circle* s2;
	s1 = start;
	do
	{
		int temp = s1->number;
		s2 = s1;
		do
		{
			s2 = ChooseNext(1, s2);
			if (temp > s2->number)
			{
				s1->number = s2->number;
				s2->number = temp;
				temp = s1->number;
			}
		} while (ChooseNext(1, s2) != start);
		s1 = ChooseNext(1, s1);
	} while (ChooseNext(1, s1) != start);
}

int CircleToFile(Circle* start)
{
	if (!start)
		return -1;
	FILE* file = fopen("circle.txt", "w");
	if (!file)
		return -2;
	Circle* s1 = start;
	system("CLS");
	printf("Как записать числа из кольца в файл:\n1 - по часовой стрелке\n2 - против часовой стрелки\n");
	int direction = InputAndCheck(1, 2);
	system("CLS");
	do
	{
		fprintf(file, "%d\n", s1->number);
		s1 = ChooseNext(direction, s1);
	} while (s1 != start);
	return 1;
}
