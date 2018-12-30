#ifndef _TTEXT_H_
#define _TTEXT_H_

#include "TTextLink.h"

#include <stack>
#include <string>
#include <fstream>

class TText;
typedef TTextLink *PTTextLink;
typedef TText *PTText;

class TText
{
  protected:
    PTTextLink pFirst;                      // указатель корня дерева
    PTTextLink pCurrent;                    // указатель текущей строки
    stack<PTTextLink> Path;                 // стек траектории движения по тексту
    stack<PTTextLink> St;                   // стек для итератора
    PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
    void PrintTextSince(PTTextLink ptl);    // печать текста со звена ptl
    PTTextLink ReadText(ifstream &TxtFile); //чтение текста из файла
    void PrintToFile(PTTextLink ptl, int TextLevel, ofstream &File);

  public:
    TText(PTTextLink pl = NULL);
    ~TText() { pFirst = NULL; }

    static int MemCleaner(TText txt); // сборка мусора

    //PTText getCopy();

    // навигация
    int GoFirstLink(void);  // переход к первой строке
    int GoDownLink(void);   // переход к следующей строке по Down
    int GoNextLink(void);   // переход к следующей строке по Next
    int GoPrevLink(void);   // переход к предыдущей позиции в тексте
                            // доступ
    string GetLine(void);   // чтение текущей строки
    void SetLine(string s); // замена текущей строки

    // модификация
    void InsDownLine(string s);    // вставка строки в подуровень
    void InsDownSection(string s); // вставка раздела в подуровень
    void InsNextLine(string s);    // вставка строки в том же уровне
    void InsNextSection(string s); // вставка раздела в том же уровне
    void DelDownLine(void);        // удаление строки в подуровне
    void DelDownSection(void);     // удаление раздела в подуровне
    void DelNextLine(void);        // удаление строки в том же уровне
    void DelNextSection(void);     // удаление раздела в том же уровне

    // итератор
    int Reset(void);             // установить на первую запись
    int IsTextEnded(void) const; // текст завершен?
    int GoNext(void);            // переход к следующей записи

    //работа с файлами
    void Read(char *pFileName);  // ввод текста из файла
    void Write(char *pFileName); // вывод текста в файл

    //печать
    void PrintAll(void); // печать текста
};
#endif