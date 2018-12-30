#ifndef _TTEXTLINK_H_
#define _TTEXTLINK_H_

//#include "TDatValue.h"

#include <iostream>
#include <stdio.h>
using namespace std;

#include <malloc.h>
#include <string.h>
//#include "TTexter.h"

#define TextLineLength 20
#define MemSize 30 // количество выделяемой памяти

class TText;
class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem
{
    PTTextLink pFirst; // указатель на первое звено
    PTTextLink pLast;  // указатель на последнее звено
    PTTextLink pFree;  // указатель на первое свободное звено

    friend class TText;
    friend class TTextLink;
};

typedef TTextMem *PTTextMem;

class TTextLink
{
  protected:
    TStr Str;                  // поле для хранения строки текста
    PTTextLink pNext, pDown;   // указатели по тек. уровень и на подуровень
    static TTextMem MemHeader; // система управления памятью

  public:
    static void InitMemSystem(int size = MemSize); // инициализация памяти
    void *operator new(size_t size);               // выделение звена
    void operator delete(void *pM);                // освобождение звена
    static void PrintFreeLink(void);               // печать свободных звеньев
    //static void MemCleaner(TText txt); // сборка мусора

    TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL)
    {
        pNext = pn;
        pDown = pd;

        if (s != NULL)
            strcpy(Str, s);
        else
            Str[0] = '\0';
    }
    ~TTextLink() {}
    string GetStr()
    {
        return Str;
    }

    int IsAtom() { return pDown == NULL; } // проверка атомарности звена
    PTTextLink GetNext() { return pNext; }
    PTTextLink GetDown() { return pDown; }

    friend class TText;
};
#endif
