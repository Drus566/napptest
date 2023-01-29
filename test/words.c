#include <stdio.h>
#include <locale.h>

int main(void)
{  
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t myArray[] = { L'П', L'р', L'и', L'в', L'е', L'т', L' ', L'м', L'и', L'р', L'\0' };

    wchar_t *ptr1 = myArray;

    while (*ptr1 != L'\0') {
       wprintf(L"%lc, %x\n", *ptr1, *ptr1);
       if (*ptr1 == L'П')
       {
            wprintf(L"COOL\n");
       }
       ptr1++;
    }
    int start, end;
    start = 0x410;
    end = 0x451;

    for (int i = start; i <= end; i++)
    {
        wprintf(L"%lc, %x, %d, %o\n", i, i, i, i);
    }
    return 0;
}