#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Queue Queue;

struct Queue
{
	Queue* next;
	Queue* prev;
	int number;
};

int InputAndCheck(int, int);
void InputQueue(Queue**, Queue**, int);
void Show(Queue*, Queue*, int);
int Clean(Queue**, Queue**, int);
int CleanAll(Queue**, Queue**);
int CleanAny(Queue**, Queue**, int);
int Sort(Queue**, Queue**);
int QueueToFile(Queue*, Queue*);
int FileToQueue(Queue**, Queue**, char*);

