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

void InputQueue(Queue** head, Queue** tail, int number)
{
	Queue* elem = (Queue*)calloc(1, sizeof(Queue));
	if (!elem)
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	elem->number = number;
	if (!*head)
		*head = *tail = elem;
	else
	{
		(*tail)->next = elem;
		elem->prev = *tail;
		*tail = elem;
	}
}

void Show(Queue* head, Queue* tail, int variant)
{
	system("CLS");
	if (!head)
	{
		printf("Очередь пуста!\n");
		return;
	}
	if (variant == 2)
	{
		Queue* ptr = head;
		printf("Числа в очереди (с головы):\n");
		while (ptr)
		{
			printf("%d\n", ptr->number);
			ptr = ptr->next;
		}
	}
	else if (variant == 3)
	{
		Queue* ptr = tail;
		printf("Числа в очереди (с хвоста):\n");
		while (ptr)
		{
			printf("%d\n", ptr->number);
			ptr = ptr->prev;
		}
	}
}

int Clean(Queue** head, Queue** tail, int variant)
{
	if (!*head || !*tail)
		return 0;
	if (variant == 4)
	{
		Queue* temp = (Queue*)calloc(1, sizeof(Queue));
		if (!temp)
			return -1;
		temp = (*head)->next;
		temp->prev = NULL;
		free(*head);
		*head = temp;
		return 1;
	}
	else
	{
		Queue* temp = (Queue*)calloc(1, sizeof(Queue));
		if (!temp)
			return -1;
		temp = (*tail)->prev;
		temp->next = NULL;
		free(*tail);
		*tail = temp;
		return 1;
	}
}

int CleanAll(Queue** head, Queue** tail)
{
	if (!*head || !*tail)
		return 0;
	while (*head)
		*head = (*head)->next;
	while (*tail)
		*tail = (*tail)->prev;
	*head = *tail = NULL;
	return 1;
}

int CleanAny(Queue** head, Queue** tail, int numForDelete)
{
	Queue* ptr = *head;
	if (!*head || !*tail)
		return 0;
	if (!ptr->next && ptr->number == numForDelete)
	{
		free(ptr);
		*head = *tail = NULL;
		return 1;
	}
	while (ptr && ptr->number != numForDelete)
		ptr = ptr->next;
	if (!ptr)
		return -1;
	if (ptr->number == numForDelete)
	{
		if (ptr == *tail)
		{
			*tail = (*tail)->prev;
			(*tail)->next = NULL;
		}
		else if (ptr == *head)
		{
			*head = (*head)->next;
			(*head)->prev = NULL;
		}
		else
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
		}
		free(ptr);
		return 2;
	}
}

int Sort(Queue** head, Queue** tail)
{
	if (!*head || !*tail)
		return -1;
	Queue* t = NULL;
	Queue* t1 = NULL
		;
	int r;
	do {
		for (t1 = *head; t1->next != t; t1 = t1->next)
			if (t1->number > t1->next->number)
			{
				r = t1->number;
				t1->number = t1->next->number;
				t1->next->number = r;
			}
		t = t1;
	} while ((*head)->next != t);
	return 1;
}

int QueueToFile(Queue* head, Queue* tail)
{
	system("CLS");
	if (!head)
		return -1;
	FILE* file = fopen("queue.txt", "w");
	if (!file)
		return -2;
	Queue* ptr = head;
	while (ptr)
	{
		fprintf(file, "%d\n", ptr->number);
		ptr = ptr->next;
	}
	return 1;
}

int FileToQueue(Queue** head, Queue** tail, char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file)
		return -1;
	while (!feof(file))
	{
		Queue* elem = (Queue*)calloc(1, sizeof(Queue));
		if (!elem)
		{
			printf("Произошла ошибка при выделении памяти!\n");
			return;
		}
		int number;
		if (fscanf(file, "%d", &number) > 0)
		{
			elem->number = number;
			if (!*head)
				*head = *tail = elem;
			else
			{
				(*tail)->next = elem;
				elem->prev = *tail;
				*tail = elem;
			}
		}
	}
	return 1;
}