#define BufLength 80

#include <string>
#include <cstring>

#include "TText.h"

static char StrBuf[BufLength + 1]; //буфер для ввода строк
static int TextLevel = 0;          //номер текущего уровня текста

TText::TText(PTTextLink pl)
{
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
    pCurrent = pl;
}

//навигация
int TText::GoFirstLink(void) //переход к первой строке
{
    while (!Path.empty())
        Path.pop(); //очистка стека
    pCurrent = pFirst;
    if (pCurrent == NULL)
    {
        cout << "pCurrent == NULL" << endl;
        TextLevel = 0;
        system("pause");
        return 0; //error
    }
    else
        return 1; //ok
}

int TText::GoDownLink(void) //переход к след. строке по down
{
    int res = 0;
    if (pCurrent != NULL)
        if (pCurrent->pDown != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pDown;
            res = 1; //ok
        }
    return res;
}

int TText::GoNextLink(void) //переход к след. строке по Next
{
    int res = 0;
    if (pCurrent != NULL)
        if (pCurrent->pNext != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pNext;
            res = 1; //ok
        }
    return res;
}

int TText::GoPrevLink(void) //переход к пред. позиции в тексте
{
    int res;
    if (Path.empty())
    {
        cout << "What are you doing, man? pCurrent == pFirst." << endl
             << "Where is one place you would be?(rhetorical question)";
        system("pause");
        res = 0;
    }
    else
    {
        pCurrent = Path.top();
        Path.pop(); //removed from Path
        res = 1;    //ok
    }

    return res;
}
//ACCESS
string TText::GetLine(void) //reading of current string
{
    if (pCurrent == NULL)
        return string("");
    else
        return string(pCurrent->Str);
}

void TText::SetLine(string s) //replacement of current string
{
    if (pCurrent == NULL)
        cout << "Text error SetLine" << endl;
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}

//modifications
void TText::InsDownLine(string s)
{
    if (pCurrent == NULL)
        cout << "Text error InsDownLine" << endl;
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", pd, NULL);

        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl;
        //TextLevel++;
    }
}

void TText::InsDownSection(string s) // вставка раздела в подуровень
{
    if (pCurrent == NULL)
        cout << "Text error InsDownSection" << endl;
    else
    {
        PTTextLink pd = pCurrent->pDown;             //rename
        PTTextLink pl = new TTextLink("", NULL, pd); //new mem for link
        strncpy(pl->Str, s.c_str(), TextLineLength); //text copy
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl; //reidenticating
                              //TextLevel++;
    }
}

void TText::InsNextLine(string s) // вставка строки в том же уровне
{
    if (pCurrent == NULL)
        cout << "Text error InsNextLine" << endl;
    else
    {
        PTTextLink pn = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", pn, NULL);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
    }
}

void TText::InsNextSection(string s) // вставка раздела в том же уровне
{
    if (pCurrent == NULL)
        cout << "Text error InsNextSection" << endl;
    else if ((pCurrent->pNext) != NULL)
    {
        PTTextLink pn = pCurrent->pNext;                    //rename
        PTTextLink pl = new TTextLink("", pn, (pn->pNext)); //new memory for link   pn is subtotal of pl, pl is next for pCurr
        strncpy(pl->Str, s.c_str(), TextLineLength);        //text copy
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl; //reidenticating
    }
    else
        InsNextLine(s);
}

void TText::DelDownLine(void) // удаление строки в подуровне
{
    if (pCurrent == NULL)
        cout << "Text error DelDownLine" << endl;
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink p11 = pCurrent->pDown;
        PTTextLink p12 = (p11->pNext);
        if ((p11->pDown) == NULL)
        {
            pCurrent->pDown = p12; //только для атома
        }
    }
}

void TText::DelDownSection(void)
{
    if (pCurrent == NULL)
        cout << "Text error DelDownSection" << endl;
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink p11 = pCurrent->pDown;
        PTTextLink p12 = p11->pNext;
        pCurrent->pDown = p12;
        //we delete whole section thats all
    }
}

void TText::DelNextLine(void) // удаление СТРОКИ в том же уровне
{
    if (pCurrent == NULL)
        cout << "Text error DelNextLine" << endl;
    else if ((pCurrent->pNext) != NULL)
    {
        PTTextLink p11 = pCurrent->pNext;
        PTTextLink p12 = (p11->pNext);
        if (p11->pDown == NULL)
        {
            pCurrent->pNext = p12; //только для атома
        }
    }
}

void TText::DelNextSection(void) // удаление РАЗДЕЛА в том же уровне
{
    if (pCurrent == NULL)
        cout << "Text error DelNextSection" << endl;
    else if ((pCurrent->pNext) != NULL)
    {
        PTTextLink p11 = pCurrent->pNext;
        PTTextLink p12 = p11->pNext;
        pCurrent->pNext = p12;
    }
}

//iterator
int TText::Reset(void)
{
    while (!St.empty())
        St.pop();
    pCurrent = pFirst;
    if (pCurrent != NULL)
    {
        St.push(pCurrent);
        if (pCurrent->pNext != NULL)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != NULL)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded(void) const // текст завершен?
{
    return !St.size();
}

int TText::GoNext(void) // переход к следующей записи
{
    if (!IsTextEnded())
    {
        pCurrent = St.top();
        St.pop();
        if (pCurrent != pFirst)
        {
            if (pCurrent->pNext != NULL)
                St.push(pCurrent->pNext);
            if (pCurrent->pDown != NULL)
                St.push(pCurrent->pDown);
        }
        return IsTextEnded();
    }
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) // поиск первого атома
{
    PTTextLink tmp = pl;
    while (!tmp->IsAtom())
    {
        St.push(tmp);
        tmp = tmp->GetDown();
    }

    return tmp;
}

void TText::PrintAll(void) // печать вссего текста
{
    TextLevel = 0;
    PrintTextSince(pFirst);
}

void TText::PrintTextSince(PTTextLink ptl) // печать текста со звена ptl
{
    int flag = 0, k = 0;

    if (ptl != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
        {
            cout << '\t';
        }
        if (TextLevel == 0)
            if (ptl == pCurrent && pCurrent->GetStr() != "")
                cout << "->";
            else
                cout << "  ";
        else
        {
            if (ptl == pCurrent)
            {
                if (ptl->Str != "")
                    cout << "->";
            }
            else
                cout << "  ";
        }
        cout << ptl->Str << endl;
        TextLevel++;
        PrintTextSince(ptl->GetDown());
        TextLevel--;
        PrintTextSince(ptl->GetNext());
    }
}

void TText::Read(char *pFileName) // ввод текста из файла
{
    ifstream TxtFile(pFileName);
    TextLevel = 0;

    if (&TxtFile != NULL)
    {
        pFirst = ReadText(TxtFile);
        pCurrent = pFirst;
    }
    else
        cerr << "Error Opening File" << endl;
}

PTTextLink TText::ReadText(ifstream &TxtFile) //чтение текста из файла
{
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while (TxtFile.eof() == 0) //while file is not completed
    {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}')
        {
            TextLevel--;
            break;
        }
        else if (StrBuf[0] == '{')
        { //рекурсия
            TextLevel++;
            (ptl->pDown) = ReadText(TxtFile);
        }
        else
        {
            for (int r = 0; StrBuf[r] != '\0'; r++)
                if (StrBuf[r] != ' ')
                {
                    (ptl->pNext) = new TTextLink(StrBuf, NULL, NULL);
                    ptl = (ptl->pNext);
                    break;
                }
        }
    }

    ptl = pHead;
    if (pHead->pDown == NULL)
    {
        pHead = (pHead->pNext); //moved pHead
        delete ptl;
    }

    return pHead;
}

void TText::Write(char *pFileName)
{
    ofstream File(pFileName);

    PrintToFile(pFirst, 0, File);
}
int flag = 0; //global variable for printtofile
void TText::PrintToFile(PTTextLink ptl, int TextLevel, ofstream &File)
{
    if (ptl != NULL)
    {
        /*for (int i = 0; i < TextLevel; i++)
      File << '\t';    */
        File << ptl->Str << endl;

        if (ptl->GetDown() != NULL)
        {
            flag++;
            File << '{' << endl;
        }
        else if ((ptl->GetDown() == NULL) && (ptl->GetNext() == NULL) && flag != 0)
        {
            --flag;
            File << '}' << endl;
        }

        TextLevel++;
        PrintToFile(ptl->GetDown(), TextLevel, File);

        TextLevel--;
        //ВНИМАНИЕ К О С Т Ы Л Ь
        if (ptl->GetDown() != NULL && (ptl->GetDown()) != NULL)
            if (TextLevel == 0 && (ptl->GetDown())->GetDown() != NULL && ((ptl->GetDown())->GetNext() != NULL) && (flag != 0))
            {
                --flag;
                File << '}' << endl;
            }
        PrintToFile(ptl->GetNext(), TextLevel, File);
    }
}

    int TText::MemCleaner(TText txt) //сборка мусор
    {                                //пробная версия - в памяти только один текст
        string st;
        //маркировка строк текста - маркер "&&&"
        for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
        {
            st = txt.GetLine();
            if (st.find("&&&") != 0)
                txt.SetLine("&&&" + txt.GetLine()); //writing in current "&&&"+.....
        }
        //маркировка списка свободных звеньев
        PTTextLink pLink = TTextLink::MemHeader.pFree;
        // PTTextLink dop = txt->pFirst;
        for (; pLink != NULL; pLink = (pLink->pNext))
            strcpy(pLink->Str, "&&&");

        int i = 0;
        //сборка мусора
        pLink = TTextLink::MemHeader.pFirst; //pLink points on pFirst which in MemeText
        for (; pLink <= TTextLink::MemHeader.pLast; pLink++)
        {
            if (strstr(pLink->Str, "&&&") != NULL)    //возвращает первое вхождение "&&&" иначе возвращает ничего
                strcpy(pLink->Str, (pLink->Str) + 3); //копирует, начиная с 3его
            else{
                delete pLink; //"неучтенное" звено в список свободных(calling our delete)
                i++;
            }
        }

        return i;
    }

