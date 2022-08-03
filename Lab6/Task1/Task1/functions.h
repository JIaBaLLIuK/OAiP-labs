#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Circle Circle;

struct Circle
{
	int number;
	Circle* left;
	Circle* right;
};

int InputAndCheck(int, int);
void InputInformation(Circle**);
int OutputInformation(Circle*);
Circle* ChooseNext(int, Circle*);
Circle* DeleteStart(Circle*);
Circle* DeleteAny(Circle*);
Circle* PtrSort(Circle*);
void ValueSort(Circle*);
int CircleToFile(Circle*);
int FileToCircle(Circle**, char*);
