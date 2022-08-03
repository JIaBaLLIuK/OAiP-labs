#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

typedef struct Stack Stack;
typedef struct Tree Tree;

struct Tree
{
	char* word;
	Tree* leftPtr;
	Tree* rightPtr;
};

struct Stack
{
	char* word;
	Stack* next;
};

void Push(Stack**, char*);
void ShowStack(Stack*);
void InputInformation(Tree**);
void RecursionShow(Tree*);
int InputAndCheck(int, int);
void ClearBuffer();
void Task(Tree*, Stack**, Tree*);
Tree* DeleteAny(Tree*, char*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int stop = 0;
	Tree* root = NULL;
	Stack* top = NULL;
	do
	{
		InputInformation(&root);
		printf("Прекратить ввод?\n0 - нет\n1 - да\n");
		stop = InputAndCheck(0, 1);
	} while (stop == 0);
	system("CLS");
	printf("Информация в исходном дереве:\n");
	RecursionShow(root);
	printf("Информация в дереве после удаления:\n");
	Task(root, &top, root);
	RecursionShow(root);
	printf("Информация в стеке:\n");
	ShowStack(top);
	return 0;
}

void Task(Tree* root, Stack** top, Tree* tempRoot)
{
	if (root)
	{
		char* temp = root->word;
		for (int i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == 'а' || temp[i] == 'А')
			{
				root = DeleteAny(tempRoot, temp);
				Push(top, temp);
				break;
			}
		}
		if (root->leftPtr)
			Task(root->leftPtr, top, tempRoot);
		if (root->rightPtr)
			Task(root->rightPtr, top, tempRoot);
	}
}

void InputInformation(Tree** root)
{
	Tree* newNode = (Tree*)calloc(1, sizeof(Tree));
	if (!newNode)
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	newNode->word = (char*)calloc(80, sizeof(char));
	if (!(newNode->word))
	{
		printf("Произошла ошибка при выделении памяти!\n");
		return;
	}
	Tree* tmp;
	printf("Введите слово:\n");
	rewind(stdin);
	gets(newNode->word);
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
		puts(root->word);
		if (root->leftPtr)
			RecursionShow(root->leftPtr);
		if (root->rightPtr)
			RecursionShow(root->rightPtr);
	}
}

void ClearBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void Push(Stack** top, char* word)
{
	Stack* position = *top;
	if (!(*top = (Stack*)calloc(1, sizeof(Stack))))
	{
		printf("Произошла ошибка при создании стека.\n");
		return;
	}
	else
	{
		(*top)->word = word;
		(*top)->next = position;
		position = *top;

	}
}

void ShowStack(Stack* top)
{
	if (!top)
	{
		printf("Стек пуст.\n");
		return;
	}
	do
	{
		puts(top->word);
		top = top->next;
	} while (top);
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