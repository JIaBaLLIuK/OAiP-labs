#include "functions.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Queue* head = NULL;
	Queue* tail = NULL;
	printf("����� ������� ������� ����� � �������:\n1. �������.\n2. ����� ����.\n0. ��������� ������.\n");
	int typeOfInput = InputAndCheck(0, 2);
	switch (typeOfInput)
	{
	case 1:
	{
		bool isFinished = false;
		system("CLS");
		do
		{
			printf("�������� ��������:\n1. �������� ������� � ���� � �� �����.\n2. �������� ������� � ������.\n");
			printf("3. ��������� ������� � ������.\n4. ������� ������ �������.\n5. ������� ������ �������.\n");
			printf("6. ������� ���� �������.\n7. �������� ��������� ��������.\n8. ���������� �������.\n0. ���������� ������.\n");
			int operation = InputAndCheck(0, 8);
			switch (operation)
			{
			case 1:
			{
				system("CLS");
				int stop = 0;
				do
				{
					printf("������� ������� �������:\n");
					int number = InputAndCheck(INT_MIN, INT_MAX);
					InputQueue(&head, &tail, number);
					printf("���������� ����?\n0 - ���\n1 - ��\n");
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
					printf("������� �����!\n");
				else if (status == -1)
					printf("��������� ������ ��� ������� ������ �������!\n");
				else if (status == 1)
					printf("������ ������� �������!\n");
				break;
			}
			case 5:
			{
				system("CLS");
				int status = Clean(&head, &tail, 5);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == -1)
					printf("��������� ������ ��� ������� ������ �������!\n");
				else if (status == 1)
					printf("����� ������� ������!\n");
				break;
			}
			case 6:
			{
				system("CLS");
				int status = CleanAll(&head, &tail);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == 1)
					printf("������� ��������!\n");
				break;
			}
			case 7:
			{
				system("CLS");
				printf("������� ����� ��� �������� �� �������:\n");
				int numForDelete = InputAndCheck(INT_MIN, INT_MAX);
				int status = CleanAny(&head, &tail, numForDelete);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == 1)
					printf("� ������� ��������� ������ ��������� �������, ������� � ��� ������!\n");
				else if (status == 2)
					printf("�������� ����� ���� ������� �� �������!\n");
				else if (status == -1)
					printf("� ������� ��� ������ ��������!\n");
				break;
			}
			case 8:
			{
				system("CLS");
				int status = Sort(&head, &tail);
				if (status == -1)
					printf("������� �����!\n");
				else if (status == 1)
					printf("������� �������������!\n");
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("�������� ������� � ����?\n0 - ���\n1 - ��\n");
				int queueToFile = InputAndCheck(0, 1);
				if (queueToFile == 1)
				{
					int status = QueueToFile(head, tail);
					if (status == -1)
						printf("������� �����! ������ � ���� ����������!\n");
					else if (status == -2)
						printf("������ ��� �������� �����!\n");
					else
						printf("������� ������� �������� � ����!\n");
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
			printf("��������� ������. ��������� ��������� ���� ������!\n");
			return 0;
		}
		printf("������� ���/���� �����:\n");  
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
					printf("��� ����� �������� ����������� �������! ��������� ����:\n");
					gets(fileName);
				}
			}
		}
		int isFile = FileToQueue(&head, &tail, fileName);
		if (isFile == -1)
		{
			printf("������ ����� �� ����������! ���������� ������...\n");
			return 0;
		}
		else if (isFile == 1)
			printf("����� ������� �������� � �������!\n");
		do
		{
			printf("�������� ��������:\n1. �������� ������� � ������.\n");
			printf("2. ��������� ������� � ������.\n3. ������� ������ �������.\n4. ������� ������ �������.\n");
			printf("5. ������� ���� �������.\n6. �������� ��������� ��������.\n7. ���������� �������.\n0. ���������� ������.\n");
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
					printf("������� �����!\n");
				else if (status == -1)
					printf("��������� ������ ��� ������� ������ �������!\n");
				else if (status == 1)
					printf("������ ������� �������!\n");
				break;
			}
			case 4:
			{
				system("CLS");
				int status = Clean(&head, &tail, 5);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == -1)
					printf("��������� ������ ��� ������� ������ �������!\n");
				else if (status == 1)
					printf("����� ������� ������!\n");
				break;
			}
			case 5:
			{
				system("CLS");
				int status = CleanAll(&head, &tail);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == 1)
					printf("������� ��������!\n");
				break;
			}
			case 6:
			{
				system("CLS");
				printf("������� ����� ��� �������� �� �������:\n");
				int numForDelete = InputAndCheck(INT_MIN, INT_MAX);
				int status = CleanAny(&head, &tail, numForDelete);
				if (status == 0)
					printf("������� �����!\n");
				else if (status == 1)
					printf("� ������� ��������� ������ ��������� �������, ������� � ��� ������!\n");
				else if (status == 2)
					printf("�������� ����� ���� ������� �� �������!\n");
				else if (status == -1)
					printf("� ������� ��� ������ ��������!\n");
				break;
			}
			case 7:
			{
				system("CLS");
				int status = Sort(&head, &tail);
				if (status == -1)
					printf("������� �����!\n");
				else if (status == 1)
					printf("������� �������������!\n");
				break;
			}
			case 0:
			{
				system("CLS");
				isFinished = true;
				printf("�������� ������� � ����?\n0 - ���\n1 - ��\n");
				int queueToFile = InputAndCheck(0, 1);
				if (queueToFile == 1)
				{
					int status = QueueToFile(head, tail);
					if (status == -1)
						printf("������� �����! ������ � ���� ����������!\n");
					else if (status == -2)
						printf("������ ��� �������� �����!\n");
					else
						printf("������� ������� �������� � ����!\n");
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