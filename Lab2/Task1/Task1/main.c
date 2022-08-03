#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int InputInformation(char*);
void OutputInformation(char*, int);

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int numAmount, check;
	char* fileName;
	fileName = (char*)calloc(100, sizeof(char));  // выделение памяти под имя файла
	if (!fileName)  // проверка выделения памяти
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return 0;
	}
	printf("Введите имя/путь для создания нового файла:\n");
	gets(fileName);  // ввод имени файла
	numAmount = InputInformation(fileName);
	if (!numAmount)
		return 0;
	system("CLS");
	OutputInformation(fileName, numAmount);
	free(fileName);  // очистка памяти
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
		while (!check)  // проверка ввода
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

