#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>

#define SIZE 20

typedef struct Tree Tree;

struct Tree
{
	char* word;
	char* translation;
	Tree* leftPtr;
	Tree* rightPtr;
};

int InputAndCheck(int, int);
void ClearBuffer();
void InputInformation(Tree** root);
void FreeTree(Tree** tree);
void RecursionShow(Tree*);
void StackShow(Tree*);
Tree* DeleteAny(Tree*, char*);
Tree* DeleteAndPush(Tree*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int stop = 0;
	Tree* root = NULL;
	do
	{
		printf("Выберите действие:\n");
		printf("1. Ввести информацию в дерево.\n2. Просмотор информации в дереве (рекурсивно).\n");
		printf("3. Просмотр информации в дереве (через стек).\n4. Удаление любого элемента.\n5. Очистка дерева.\n");
		printf("0. Завершение работы.\n");
		int operation;
		operation = InputAndCheck(0, 5);
		switch (operation)
		{
		case 1:
			system("CLS");
			InputInformation(&root);
			break;
		case 2:
			system("CLS");
			printf("Информация из дерева:\n");
			if (!root)
				printf("Дерево пустое!\n");
			RecursionShow(root);
			break;
		case 3:
			system("CLS");
			printf("Информация из дерева:\n");
			if (!root)
				printf("Дерево пустое!\n");
			StackShow(root);
			break;
		case 5:
			system("CLS");
			FreeTree(&root);
			printf("Дерево очищено!\n");
			break;
		case 4:
		{
			system("CLS");
			if (!root)
				printf("Дерево пустое!\n");
			char forDelete[20];
			printf("Введите слово для удаления:\n");
			rewind(stdin);
			gets(forDelete);
			system("CLS");
			root = DeleteAny(root, forDelete);
			break;
		}
		case 0:
			system("CLS");
			stop = 1;
			break;
		}
	} while (!stop);
	return 0;
}

void InputInformation(Tree** root)
{
	Tree* newNode = (Tree*)calloc(1, sizeof(Tree));
	if (!newNode)
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	newNode->word = (char*)calloc(SIZE, sizeof(char));
	if (!(newNode->word))
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	newNode->translation = (char*)calloc(SIZE, sizeof(char));
	if (!(newNode->translation))
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	Tree* tmp;
	printf("Введите слово:\n");
	ClearBuffer();
	gets(newNode->word);
	printf("Введите перевод данного слова:\n");

	gets(newNode->translation);
	system("CLS");
	newNode->leftPtr = newNode->rightPtr = NULL;
	if (*root == NULL)
	{
		*root = newNode;
		return;
	}
	else
	{
		tmp = *root;
		while (1)
		{
			if (strcmp(tmp->word, newNode->word) == 0)
			{
				printf("Один из данных узлов уже содержится в дереве!\n");
				return;
			}
			else if (strcmp(tmp->word, newNode->word) < 0)
			{
				if (!tmp->rightPtr)
				{
					tmp->rightPtr = newNode;
					return;
				}
				else
				{
					tmp = tmp->rightPtr;
				}
			}
			else
			{
				if (!tmp->leftPtr)
				{
					tmp->leftPtr = newNode;
					return;
				}
				else
				{
					tmp = tmp->leftPtr;
				}
			}
		}
	}
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

void RecursionShow(Tree* root)
{
	if (root)
	{
		printf("Слово '%s' переводится как '%s'.\n", root->word, root->translation);
		if (root->leftPtr)
			RecursionShow(root->leftPtr);
		if (root->rightPtr)
			RecursionShow(root->rightPtr);
	}
}

void StackShow(Tree* root)
{
	typedef struct stack stack;
	struct stack
	{
		Tree* temp;
		stack* s;
	} *st, * st1 = NULL;
	int pr = 1;
	st = (stack*)calloc(1, sizeof(stack));
	if (!st)
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	st->temp = root;
	st->s = st1;
	printf("Слово '%s' переводится как '%s'.\n", root->word, root->translation);
	while (st || root->rightPtr)
	{
		do
		{
			if (pr && root->leftPtr)
				root = root->leftPtr;
			else if (root->rightPtr)
				root = root->rightPtr;
			pr = 1;
			if (root->leftPtr && root->rightPtr)
			{
				st1 = st;
				st = (stack*)calloc(1, sizeof(stack));
				if (!st)
				{
					printf("Произошла ошибка при выделении памяти!\n");
					return;
				}
				st->temp = root;
				st->s = st1;
			}
			printf("Слово '%s' переводится как '%s'.\n", root->word, root->translation);
		} while (root->leftPtr || root->rightPtr);
		if (st)
		{
			root = st->temp;
			st1 = st->s;
			free(st);
		}
		st = st1;
		if (root->leftPtr && root->rightPtr)
			pr = 0;
		else
			break;
	}
}

Tree* DeleteAny(Tree* root, char* forDelete)
{
	Tree* Del = root;
	Tree* Prev_Del = NULL;
	Tree* R;
	Tree* Prev_R;
	while (Del != NULL && strcmp(Del->word, forDelete))
	{
		Prev_Del = Del;
		if (strcmp(Del->word, forDelete) > 0)
			Del = Del->leftPtr;
		else
			Del = Del->rightPtr;
	}
	if (!Del)
	{
		printf("В дереве отсутсвует введенное слово!\n");
		return root;
	}
	if (!Del->rightPtr)
		R = Del->leftPtr;
	else if (!Del->leftPtr)
		R = Del->rightPtr;
	else
	{
		Prev_R = Del;
		R = Del->leftPtr;
		while (R->rightPtr)
		{
			Prev_R = R;
			R = R->rightPtr;
		}
		if (Prev_R == Del)
			R->rightPtr = Del->rightPtr;
		else
		{
			R->rightPtr = Del->rightPtr;
			Prev_R->rightPtr = R->leftPtr;
			R->leftPtr = Prev_R;
		}
	}
	if (Del == root)
		root = R;
	else if (strcmp(Del->word, Prev_Del->word) < 0)
		Prev_Del->leftPtr = R;
	else
		Prev_Del->rightPtr = R;
	free(Del);
	return root;
}


void FreeTree(Tree** tree)
{
	if (!*tree)
		printf("Дерево пустое!\n");
	else
	{
		if ((*tree)->leftPtr)
			FreeTree(&(*tree)->leftPtr);
		if ((*tree)->rightPtr)
			FreeTree(&(*tree)->rightPtr);
	}
	*tree = NULL;
}

void ClearBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
