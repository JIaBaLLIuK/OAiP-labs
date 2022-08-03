#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

void InputInformation(char*, int);
void OutputInformation(char*);
int FindSum(char*);
void ChangeToSpace(char*);

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char forbiddenSymbols[] = { '/', '|', '<', '>', '?', '"', '*' };  // массив запрещенных символов
	char* fileName = (char*)calloc(100, sizeof(char));  // выделение памяти под имя/путь файла
	if (!fileName)  // проверка выделения памяти
	{
		printf("Произошла ошибка. Программа завершает свою работу!\n");
		return 0;
	}
	printf("Введите имя/путь файла:\n");  // ввод имени/пути файла
	rewind(stdin);
	gets(fileName); 
	for (int i = 0; fileName[i] != '\0'; i++)  // проверка имени/путь на наличие запрещенных символов
	{
		for (int j = 0; j < sizeof(forbiddenSymbols); j++)
		{
			if (fileName[i] == forbiddenSymbols[j])
			{
				i = 0;
				j = 0;
				printf("Имя файла содержит запрещённые символы! Повторите ввод:\n");
				gets(fileName);
			}
		}
	}
	int numbersAmount;
	printf("Введите количество чисел для записи в файл:\n");  // ввод количества чисел для записи в файл
	scanf_s("%d", &numbersAmount);
	while (numbersAmount < 1)  // проверка ввода
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		scanf_s("%d", &numbersAmount);
	}
	system("CLS");
	bool isFinished = false;
	bool isInputedNumbers = false;
	do
	{
		printf("Выберите действие:\n1. Ввод чисел в файл.\n2. Вывод чисел из файла.\n");  // выбор операции
		printf("3. Поиск суммы чисел в файле.\n4. Замена самого длинного числа на пробелы.\n5. Завершить программу.\n");
		int operation;
		int check = scanf_s("%d", &operation);  // ввод операции
		while (operation < 1 || operation > 6 || !check)  // проверка ввода операции
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &operation);
		}
		switch (operation)
		{
		case 1:
			system("CLS");
			InputInformation(fileName, numbersAmount);
			isInputedNumbers = true;
			break;
		case 2:
			system("CLS");
			if (!isInputedNumbers)  // проверка наличие введённых чисел в файле
			{
				printf("Сначала нужно ввести числа в файл!\n");  // ввод чисел в файл при их отсутствии
				InputInformation(fileName, numbersAmount);
				isInputedNumbers = true;
			}
			printf("Исходные числа в файле:\n");
			OutputInformation(fileName);  // вывод информации на экран
			break;
		case 3:
			system("CLS");
			if (!isInputedNumbers)  // проверка наличие введённых чисел в файле
			{
				printf("Сначала нужно ввести числа в файл!\n");  // ввод чисел в файл при их отсутствии
				InputInformation(fileName, numbersAmount);
				isInputedNumbers = true;
			}
			printf("Исходные числа в файле:\n");
			OutputInformation(fileName);
			printf("Их сумма равна %d.\n", FindSum(fileName));
			break;
		case 4:
			system("CLS");
			if (!isInputedNumbers)  // проверка наличие введённых чисел в файле
			{
				printf("Сначала нужно ввести числа в файл!\n");  // ввод чисел в файл при их отсутствии
				InputInformation(fileName, numbersAmount);
				isInputedNumbers = true;
			}
			ChangeToSpace(fileName);
			printf("Новые числа в файле:\n");
			OutputInformation(fileName);
			break;
		case 5:
			isFinished = true;
			break;
		}
	} while (!isFinished);
	free(fileName);
	return 0;
}

void InputInformation(char* fileName, int numbersAmount)
{
	FILE* file;
	if (!(file = fopen(fileName, "w")))  // проверка открытия файла
	{
		printf("Ошибка при открытии файла!\n");
		return;
	}
	int numForFile;
	for (int i = 0; i < numbersAmount; i++)  // ввод чисел в файл
	{
		printf("Введите число для записи в файл:\n");
		int check = scanf_s("%d", &numForFile);
		while (!check)  // проверка введённого числа
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &numForFile);
		}
		fprintf(file, "%d\n", numForFile);
	}
	system("CLS");
	fclose(file);
}

void OutputInformation(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file)  // проверка открытия файла
	{
		printf("Ошибка при открытии файла!\n");
		return;
	}
	rewind(file);
	while (!feof(file))
	{
		int numFromFile;
		if (fscanf(file, "%d", &numFromFile) > 0)  // считывание числа из файла и проверка
			printf("%d\n", numFromFile);  // вывод числа на экран
	}
	fclose(file);
}

int FindSum(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file)  // проверка открытия файла
	{
		printf("Ошибка при открытии файла!\n");
		return;
	}
	int sum = 0;
	rewind(file);
	while (!feof(file))
	{
		int numFromFile;
		if (fscanf(file, "%d", &numFromFile) > 0)  // считывание числа из файла и проверка
			sum += numFromFile;  // поиск суммы чисел в файле
	}
	fclose(file);
	return sum;
}

void ChangeToSpace(char* fileName)
{
	FILE* file = fopen(fileName, "r+");  // открытие файла
	if (!file)  // проверка открытия файла
	{
		printf("Произошла ошибка при открытии файла!\n");
		return;
	}
	int currentLength = 0;
	int maxLength = 0;
	fpos_t position = NULL;
	while (!feof(file))
	{
		int numFromFile;
		if (fscanf(file, "%d", &numFromFile) > 0)  // считывание числа из файла и проверка
		{
			for (int i = 1; numFromFile / i >= 1; i *= 10)  // поиск длины числа
				currentLength++;
			if (currentLength >= maxLength)  // сравнение найденной длины числа с максимальной
			{
				maxLength = currentLength;
				fgetpos(file, &position);  // получение позиции самого длинного числа из файла
			}
			currentLength = 0;
		}
	}
	fsetpos(file, &position);
	fseek(file, -maxLength, SEEK_CUR);  // перемещение в начало самого длинного числа
	for (int i = 0; i < maxLength; i++)
		fprintf(file, "%c", ' ');  // замена на пробел
	fclose(file);
}