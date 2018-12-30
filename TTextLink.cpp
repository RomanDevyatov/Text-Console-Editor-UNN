#include "TTextLink.h"

TTextMem TTextLink::MemHeader;

void* TTextLink::operator new(size_t size) //выделение звена            size_t это беззнаковый целый тип данных, возвращаемый оператором sizeof
{
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != NULL)
        MemHeader.pFree = (pLink->pNext);
    else
    {
        //throw "Memmory Error";
        cout << "Memmory Error" << endl;
        system("pause");
        exit(-1);
    }

    return pLink;
}

void TTextLink::InitMemSystem(int size) //инициализация памяти
{
    MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size - 1);

    PTTextLink pLink = MemHeader.pFirst;
    //сцепка блоков
    for (int i = 0; i < size - 1; i++, pLink++)
        pLink->pNext = pLink + 1;
    pLink->pNext = NULL;
}

void TTextLink::operator delete(void *pM) //освобождение звена
{
    PTTextLink pLink = (PTTextLink)pM;
    (pLink->pNext) = MemHeader.pFree;
    MemHeader.pFree = pLink;
}

void TTextLink::PrintFreeLink(void) //печать свободных звеньев
{
    PTTextLink pLink = MemHeader.pFree;
    cout << "List of free links:" << endl;
    for (int i = 0; pLink != NULL; pLink = pLink->pNext, i++)
        cout << i << ": " << pLink->Str << endl;
}
