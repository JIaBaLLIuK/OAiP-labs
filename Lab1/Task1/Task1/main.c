#include <stdio.h>
#include <locale.h>
#include <string.h>

union Check
{
    int num;
	struct 
	{
        unsigned a0 : 1;
        unsigned a1 : 1;
        unsigned a2 : 1;
        unsigned a3 : 1;
	} byte;
} checkNum;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int num, check;
    printf("Введите число:\n");  // ввод числа
    check = scanf_s("%d", &num);
    while (!check)
    {
        rewind(stdin);
        printf("Ошибка. Повторите ввод:\n");
        check = scanf_s("%d", &num);
    }
    checkNum.num = num;
    printf("4 младших бита введённого числа: ");
    printf("%d, %d, %d, %d.\n", checkNum.byte.a3, checkNum.byte.a2, checkNum.byte.a1, checkNum.byte.a0);  // вывод 4 младших битов
    return 0;
}