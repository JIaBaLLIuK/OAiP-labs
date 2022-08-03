#include "functions.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Circle* start = NULL;
	printf("Каким образом вводить числа в кольцо:\n1. Вручную.\n2. Через файл.\n0. Завершить работу.\n");
	int typeOfInput = InputAndCheck(0, 2);
	switch (typeOfInput)
	{
	case 1:
	{
		bool isFinished = false;
		system("CLS");
		do
		{
			printf("Выберите действие:\n1. Создание кольца и ввод в него чисел.\n2. Просмотор кольца.\n3. Удаление элемента из точки входа.\n");
			printf("4. Удаление заданного элемента.\n5. Очистка кольца.\n6. Сортировка по возрастанию.\n7. Сортировка по убыванию.\n");
			printf("0. Завершение работы.\n");
			int operation = InputAndCheck(0, 7);
			switch (operation)
			{
			case 1:
			{
				system("CLS");
				InputInformation(&start);
				system("CLS");
				break;
			}
			case 2:
			{
				system("CLS");
				int status = OutputInformation(start);
				if (status == -1)
					printf("Кольцо пустое!\n");
				break;
			}
			case 3:
			{
				system("CLS");
				start = DeleteStart(start);
				break;
			}
			case 4:
			{
				system("CLS");
				start = DeleteAny(start);
				break;
			}
			case 5:
			{
				system("CLS");
				while (start)
					start = DeleteStart(start);
				break;
			}
			case 6:
			{
				system("CLS");
				start = PtrSort(start);
				break;
			}
			case 7:
			{
				system("CLS");
				ValueSort(start);
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("Записать кольцо в файл?\n0 - нет\n1 - да\n");
				int circleToFile = InputAndCheck(0, 1);
				if (circleToFile == 1)
				{
					int status = CircleToFile(start);
					if (status == -1)
						printf("Кольцо пусто! Запись в файл невозможна!\n");
					else if (status == -2)
						printf("Ошибка при создании файла!\n");
					else
						printf("Кольцо успешно записано в файл!\n");
				}
				break;
			}
			}
		} while (!isFinished);
		break;
	}
	case 2:
	{
		bool isFinished = false;
		system("CLS");
		char forbiddenSymbols[] = { '/', '|', '<', '>', '?', '"', '*' };
		char* fileName = (char*)calloc(100, sizeof(char));
		if (!fileName)
		{
			printf("Произошла ошибка. Программа завершает свою работу!\n");
			return 0;
		}
		printf("Введите имя/путь файла:\n");
		rewind(stdin);
		gets(fileName);
		for (int i = 0; fileName[i] != '\0'; i++)
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
		system("CLS");
		int isFile = FileToCircle(&start, fileName);
		if (isFile == -1)
		{
			printf("Такого файла не существует! Завершение работы...\n");
			return 0;
		}
		else if (isFile == -2)
			return 0;
		else if (isFile == 1)
			printf("Числа успешно записаны в кольцо!\n");
		do
		{
			printf("Выберите действие:\n1. Просмотор кольца.\n2. Удаление элемента из точки входа.\n");
			printf("3. Удаление заданного элемента.\n4. Очистка кольца.\n5. Сортировка по возрастанию.\n6. Сортировка по убыванию.\n");
			printf("0. Завершение работы.\n");
			int operation = InputAndCheck(0, 6);
			switch (operation)
			{
			case 1:
			{
				system("CLS");
				int status = OutputInformation(start);
				if (status == -1)
					printf("Кольцо пустое!\n");
				break;
			}
			case 2:
			{
				system("CLS");
				start = DeleteStart(start);
				break;
			}
			case 3:
			{
				system("CLS");
				start = DeleteAny(start);
				break;
			}
			case 4:
			{
				system("CLS");
				while (start)
					start = DeleteStart(start);
				break;
			}
			case 5:
			{
				system("CLS");
				PtrSort(start);
				break;
			}
			case 6:
			{
				system("CLS");
				ValueSort(start);
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("Записать кольцо в файл?\n0 - нет\n1 - да\n");
				int circleToFile = InputAndCheck(0, 1);
				if (circleToFile == 1)
				{
					int status = CircleToFile(start);
					if (status == -1)
						printf("Кольцо пусто! Запись в файл невозможна!\n");
					else if (status == -2)
						printf("Ошибка при создании файла!\n");
					else
						printf("Кольцо успешно записано в файл!\n");
				}
				break;
			}
			}
		} while (!isFinished);
		break;
	}
	case 0:
		return 0;
	}
}