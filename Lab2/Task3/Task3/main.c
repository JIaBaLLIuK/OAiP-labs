#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int InputInformation(char*);
void OutputInformation(char*, int);
void ChangeSign(char*, int);

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char* fileName;
	fileName = (char*)calloc(100, sizeof(char));
	if (!fileName)
		return 0;
	printf("Введите имя/путь файла:\n");
	gets(fileName);
	int numAmount = InputInformation(fileName);
	if (!numAmount)
	{
		printf("Произошла ошибка!\n");
		return 0;
	}
	system("CLS");
	printf("Исходные числа в файле:\n");
	OutputInformation(fileName, numAmount);
	printf("Новые числа в файле:\n");
	ChangeSign(fileName, numAmount);
	OutputInformation(fileName, numAmount);
	free(fileName);
	return 0;
}

int InputInformation(char* fileName)
{
	int numAmount, numForFile, check;
	FILE* file;
	printf("Введите количество чисел для записи в файл:\n");
	check = scanf_s("%d", &numAmount);
	while (!check || numAmount < 1)
	{
		rewind(stdin);
		printf("Ошибка.Повторите ввод:\n");
		check = scanf_s("%d", &numAmount);
	}
	file = fopen(fileName, "w");
	if (!file)
	{
		printf("Произошла ошибка при открытии файла!\n");
		return 0;
	}
	for (int i = 0; i < numAmount; i++)
	{
		printf("Введите число для записи в файл:\n");
		check = scanf_s("%d", &numForFile);
		while (!check)
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &numForFile);
		}
		check = fwrite(&numForFile, sizeof(int), 1, file);
		if (!check)
		{
			printf("Произошла ошибка при записи числа в файл!\n");
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
		fread(&numFromFile, sizeof(int), 1, file);  
		printf("%d\n", numFromFile);
	}
	fclose(file);
}

void ChangeSign(char* fileName, int numAmount)
{
	FILE* file = fopen(fileName, "r+");
	int numFromFile;
	int numForFile;
	rewind(file);
	for (int i = 0; i < numAmount; i++)
	{
		fread(&numFromFile, sizeof(int), 1, file);
		numForFile = numFromFile * -1;
		int n = -1;
		fseek(file, n * sizeof(int), SEEK_CUR);
		fwrite(&numForFile, sizeof(int), 1, file);
		fseek(file, 0, SEEK_CUR);
	}
	fclose(file);
}