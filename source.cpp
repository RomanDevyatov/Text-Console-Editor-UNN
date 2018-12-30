#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "TText.h"

void menu(TText T);
void testmenu(TText T);

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "Russian");

    TTextLink::InitMemSystem();
    TText text = new (TTextLink);

    menu(text);

    system("pause");
    return 0;
}

void menu(TText T)
{
    string s;
    string mv;
    int flag = 0;

    while (1)
    {
        system("CLS");
        T.PrintAll();

        cout << "C H O O S E:" << endl;
        cout << "1. Add  a  LINE   LEVEL" << endl;
        cout << "2. Add  a  LINE   Section" << endl;
        cout << "3. Add  a  SUBLAYER" << endl;
        cout << "4. Add  a  SUBSECTION" << endl
             << endl;

        cout << "5. Go  First" << endl;
        cout << "6. Go  Next" << endl;
        cout << "7. Go  Down" << endl;
        cout << "8. Go  Prev" << endl
             << endl;

        cout << "9. Set  Current" << endl;
        cout << "10. Get  Current" << endl
             << endl;

        cout << "11. Delete  DownLine" << endl;
        cout << "12. Delete  DownSection" << endl;
        cout << "13. Delete  NextLine" << endl;
        cout << "14. Delete  NextSection" << endl
             << endl;

        cout << "r. Read  the  File" << endl;
        cout << "w. Write  in  the  File" << endl
             << endl;

        cout << "m. M E M   C L E A N E R" << endl;
        cout << "f. P R I N T  F R E E  LINKS" << endl
             << endl;

        cout << "q. Q U I T" << endl;
        cin >> mv;

        if (mv == "1")
        {
            cout << "You've chosen 'To Add  a  L I N E   L E V E L'." << endl
                 << "Set" << endl;
            do
            {
                flag = 0;
                cin >> s;
                if (s == "/")
                    exit(0);
                for (int i = 0; s[i] != '\0'; i++)
                    if (s[i] == '{' || s[i] == '}')
                        flag = 1;
            } while (flag == 1);
            T.InsNextLine(s);
        }
        if (mv == "2")
        {
            cout << "You've chosen 'To Add  a  L I N E   L E V E L'." << endl
                 << "Set" << endl;
            do
            {
                flag = 0;
                cin >> s;
                if (s == "/")
                    exit(0);
                for (int i = 0; s[i] != '\0'; i++)
                    if (s[i] == '{' || s[i] == '}')
                        flag = 1;
            } while (flag == 1);
            T.InsNextSection(s);
        }

        if (mv == "3")
        {
            cout << "You've chosen 'To Add  a  S U B T O T A L'." << endl
                 << "Set" << endl;
            do
            {
                flag = 0;
                cin >> s;
                if (s == "/")
                    exit(0);
                for (int i = 0; s[i] != '\0'; i++)
                    if (s[i] == '{' || s[i] == '}')
                        flag = 1;
            } while (flag == 1);
            T.InsDownLine(s);
        }
        if (mv == "4")
        {
            cout << "You've chosen 'To Add  a  S U B T O T A L'." << endl
                 << "Set" << endl;
            do
            {
                flag = 0;
                cin >> s;
                if (s == "/")
                    exit(0);
                for (int i = 0; s[i] != '\0'; i++)
                    if (s[i] == '{' || s[i] == '}')
                        flag = 1;
            } while (flag == 1);
            T.InsDownSection(s);
        }

        if (mv == "5")
            if (T.GoFirstLink())
                ;
        if (mv == "6")
            if (T.GoNextLink())
                ;
        if (mv == "7")
            if (T.GoDownLink())
                ;
        if (mv == "8")
            if (T.GoPrevLink())
                ;
        if (mv == "9")
        {
            cout << "You've chosen 'To Set Current'." << endl;
            cout << "Set" << endl;
            do
            {
                flag = 0;
                cin >> s;
                if (s == "/")
                    exit(0);
                for (int i = 0; s[i] != '\0'; i++)
                    if (s[i] == '{' || s[i] == '}')
                        flag = 1;
            } while (flag == 1);
            T.SetLine(s);
        }
        if (mv == "10")
        {
            cout << "You've chosen 'To Get Current'." << endl;
            cout << T.GetLine() << endl;
            system("pause");
        }
        if (mv == "11")
            T.DelDownLine();
        if (mv == "12")
            T.DelDownSection();
        if (mv == "13")
            T.DelNextLine();
        if (mv == "14")
            T.DelNextSection();
        if (mv == "f")
        {
            TTextLink::PrintFreeLink();
            system("pause");
        }
        if (mv == "r")
            T.Read("gerda.txt");
        if (mv == "w")
            T.Write("ForText.txt");
        if (mv == "m")
        {
            cout << "Number of vacant:" << TText::MemCleaner(T) << endl;
            system("pause");
        }
        if (mv == "q" || mv == "/")
            exit(0);
    }
}

void testmenu(TText T)
{
    if (T.GoFirstLink())
        ;
    T.SetLine("Genre");
    T.PrintAll();
    T.InsDownLine("Rock");
    if (T.GoDownLink())
        ;
    T.PrintAll();
    if (T.GoNextLink())
        ;
    T.PrintAll();
    T.InsNextLine("Jazz");
    if (T.GoNextLink())
        ;
    T.PrintAll();
    T.InsNextLine("Blues");
    if (T.GoNextLink())
        ;
    T.PrintAll();
    T.InsNextLine("Pop");
    T.InsDownLine("Britney Spears");
    T.InsNextLine("Shakira");

    T.PrintAll();
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());//current on blues
    //T.PrintAll();
    //T.InsDownLine("Chuck Berry");
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());//current on jazz
    //T.PrintAll();
    //T.InsDownLine("Louis Armstrong");
    //T.InsNextLine("Bunk Johnson");
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());
    //if (T.GoPrevLink());//current on rock
    //T.PrintAll();
    //T.InsDownLine("Judas Priest");
    //if (T.GoPrevLink());
    //T.PrintAll();
    /*T.GetLine();
  
  
     
  T.GoFirstLink();
      
  T.GoNextLink();
      
  T.GoDownLink();
      
  T.GoPrevLink();     */
}