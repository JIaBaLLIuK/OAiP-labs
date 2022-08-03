#include "functions.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Queue* head = NULL;
	Queue* tail = NULL;
	printf("Каким образом вводить числа в очередь:\n1. Вручную.\n2. Через файл.\n0. Завершить работу.\n");
	int typeOfInput = InputAndCheck(0, 2);
	switch (typeOfInput)
	{
	case 1:
	{
		bool isFinished = false;
		system("CLS");
		do
		{
			printf("Выберите действие:\n1. Создание очереди и ввод в неё чисел.\n2. Просмотр очереди с головы.\n");
			printf("3. Просмотор очереди с хвоста.\n4. Очистка головы очереди.\n5. Очистка хвоста очереди.\n");
			printf("6. Очистка всей очереди.\n7. Удаление заданного элемента.\n8. Сортировка очереди.\n0. Завершение работы.\n");
			int operation = InputAndCheck(0, 8);
			switch (operation)
			{
			case 1:
			{
				system("CLS");
				int stop = 0;
				do
				{
					printf("Введите элемент очереди:\n");
					int number = InputAndCheck(INT_MIN, INT_MAX);
					InputQueue(&head, &tail, number);
					printf("Прекратить ввод?\n0 - нет\n1 - да\n");
					stop = InputAndCheck(0, 1);
				} while (!stop);
				system("CLS");
				break;
			}
			case 2:
				system("CLS");
				Show(head, tail, 2);
				break;
			case 3:
				system("CLS");
				Show(head, tail, 3);
				break;
			case 4:
			{
				system("CLS");
				int status = Clean(&head, &tail, 4);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == -1)
					printf("Произошла ошибка при очистке головы очереди!\n");
				else if (status == 1)
					printf("Голова очереди очищена!\n");
				break;
			}
			case 5:
			{
				system("CLS");
				int status = Clean(&head, &tail, 5);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == -1)
					printf("Произошла ошибка при очистке хвоста очереди!\n");
				else if (status == 1)
					printf("Хвост очереди очищен!\n");
				break;
			}
			case 6:
			{
				system("CLS");
				int status = CleanAll(&head, &tail);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == 1)
					printf("Очередь очиещена!\n");
				break;
			}
			case 7:
			{
				system("CLS");
				printf("Введите число для удаления из очереди:\n");
				int numForDelete = InputAndCheck(INT_MIN, INT_MAX);
				int status = CleanAny(&head, &tail, numForDelete);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == 1)
					printf("В очереди находился только введенный элемент, который и был удален!\n");
				else if (status == 2)
					printf("Введённое число было удалено из очереди!\n");
				else if (status == -1)
					printf("В очереди нет такого элемента!\n");
				break;
			}
			case 8:
			{
				system("CLS");
				int status = Sort(&head, &tail);
				if (status == -1)
					printf("Очередб пуста!\n");
				else if (status == 1)
					printf("Очередь отсортирована!\n");
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("Записать очередь в файл?\n0 - нет\n1 - да\n");
				int queueToFile = InputAndCheck(0, 1);
				if (queueToFile == 1)
				{
					int status = QueueToFile(head, tail);
					if (status == -1)
						printf("Очередь пуста! Запись в файл невозможна!\n");
					else if (status == -2)
						printf("Ошибка при создании файла!\n");
					else
						printf("Очерель успешно записана в файл!\n");
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
		int isFile = FileToQueue(&head, &tail, fileName);
		if (isFile == -1)
		{
			printf("Такого файла не существует! Завершение работы...\n");
			return 0;
		}
		else if (isFile == 1)
			printf("Числа успешно записаны в очередь!\n");
		do
		{
			printf("Выберите действие:\n1. Просмотр очереди с головы.\n");
			printf("2. Просмотор очереди с хвоста.\n3. Очистка головы очереди.\n4. Очистка хвоста очереди.\n");
			printf("5. Очистка всей очереди.\n6. Удаление заданного элемента.\n7. Сортировка очереди.\n0. Завершение работы.\n");
			int operation = InputAndCheck(0, 7);
			switch (operation)
			{
			case 1:
				system("CLS");
				Show(head, tail, 2);
				break;
			case 2:
				system("CLS");
				Show(head, tail, 3);
				break;
			case 3:
			{
				system("CLS");
				int status = Clean(&head, &tail, 4);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == -1)
					printf("Произошла ошибка при очистке головы очереди!\n");
				else if (status == 1)
					printf("Голова очереди очищена!\n");
				break;
			}
			case 4:
			{
				system("CLS");
				int status = Clean(&head, &tail, 5);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == -1)
					printf("Произошла ошибка при очистке хвоста очереди!\n");
				else if (status == 1)
					printf("Хвост очереди очищен!\n");
				break;
			}
			case 5:
			{
				system("CLS");
				int status = CleanAll(&head, &tail);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == 1)
					printf("Очередь очиещена!\n");
				break;
			}
			case 6:
			{
				system("CLS");
				printf("Введите число для удаления из очереди:\n");
				int numForDelete = InputAndCheck(INT_MIN, INT_MAX);
				int status = CleanAny(&head, &tail, numForDelete);
				if (status == 0)
					printf("Очередь пуста!\n");
				else if (status == 1)
					printf("В очереди находился только введенный элемент, который и был удален!\n");
				else if (status == 2)
					printf("Введённое число было удалено из очереди!\n");
				else if (status == -1)
					printf("В очереди нет такого элемента!\n");
				break;
			}
			case 7:
			{
				system("CLS");
				int status = Sort(&head, &tail);
				if (status == -1)
					printf("Очередб пуста!\n");
				else if (status == 1)
					printf("Очередь отсортирована!\n");
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("Записать очередь в файл?\n0 - нет\n1 - да\n");
				int queueToFile = InputAndCheck(0, 1);
				if (queueToFile == 1)
				{
					int status = QueueToFile(head, tail);
					if (status == -1)
						printf("Очередь пуста! Запись в файл невозможна!\n");
					else if (status == -2)
						printf("Ошибка при создании файла!\n");
					else
						printf("Очерель успешно записана в файл!\n");
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
	return 0;
}