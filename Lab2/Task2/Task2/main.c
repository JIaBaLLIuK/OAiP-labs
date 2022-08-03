#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>

int InputInformation(char*);
void OutputInformation(char*, int);
int CountPrimeNumbers(char*, int);

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char* fileName;
	fileName = (char*)calloc(100, sizeof(char));  // выдедение памяти под имя/путь файла
	if (!fileName)  // проверка выделения памяти
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return 0;
	}
	printf("Введите имя/путь для файла:\n");
	gets(fileName);
	int numAmount = InputInformation(fileName);
	if (!numAmount)
		return 0;
	system("CLS");
	printf("Введённые числа:\n");
	OutputInformation(fileName, numAmount);
	printf("\nСреди них находится %d чисел являются простыми.\n", CountPrimeNumbers(fileName, numAmount));
	free(fileName);
	return 0;
}

int InputInformation(char* fileName)
{
	int numAmount, numForFile, check;
	FILE* file = fopen(fileName, "w");  // открытие файла
	if (!file)  // проверка открытия файла
	{
		printf("Произошла ошибка при открытии файла!\n");
		return 0;
	}
	printf("Введите количество чисел для записи в файл:\n");  // ввод количества чисел для записи
	check = scanf_s("%d", &numAmount);
	while (!check || numAmount < 1)  // проверка ввода
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &numAmount);
	}
	for (int i = 0; i < numAmount; i++)
	{
		printf("Введите число под номером %d:\n", i + 1);  // ввод числа
		check = scanf_s("%d", &numForFile);
		while (!check || numForFile < 2)  // проверка ввода
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &numForFile);
		}
		check = fwrite(&numForFile, sizeof(int), 1, file);  // ввод числа в файл
		if (!check)  // проверка ввода в файл
		{
			printf("Произошла ошибка при записи в файл!\n");
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	return numAmount;
}

void OutputInformation(char* fileName, int numAmount)
{
	FILE* file = fopen(fileName, "r");
	int numFromFile;
	rewind(file);
	for (int i = 0; i < numAmount; i++)
	{
		fread(&numFromFile, sizeof(int), 1, file);  // вывод чисел из файла
		printf("%d\n", numFromFile);
	}
	fclose(file);
}

int CountPrimeNumbers(char* fileName, int numAmount)
{
	FILE* file = fopen(fileName, "r");
	int numFromFile;
	int counter = 0;
	rewind(file);
	for (int i = 0; i < numAmount; i++)
	{
		fread(&numFromFile, sizeof(int), 1, file);
		if (numFromFile == 2 || numFromFile == 3)
			counter++;
		for (int j = 2; j <= (int)sqrt(numFromFile); j++)  // проверка числа на простоту
		{
			if (numFromFile % j == 0)
				break;
			else if (j == (int)sqrt(numFromFile))
				counter++;
		}
	}
	fclose(file);
	return counter;
}