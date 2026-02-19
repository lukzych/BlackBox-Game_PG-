#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

enum Ruch
{
    gora, dol, lewo, prawo
};

struct Promien
{
    int numer;
    char odbicie;
};

struct Polozenie
{
    int k;
    int w;
};

struct Historia
{
    Promien infoPoczPrzed;
    Promien infoKonPrzed;
    Promien infoPoczPo;
    Promien infoKonPo;
    int indexPoczatekInfo;
    int indexKoniecInfo;
};
struct Plansza
{
    char** atomy;
    int iloscMin;
    int ruch;
    int wymiar;
    Promien* informacje;
    Polozenie kursor;
    bool** przypuszczalne;
    int iloscWolnychPrzypuszczalnych;
    Historia historia[5];
    int historiaIlosc;
    int indexHistorii;
};

void wyswietlLogo()
{
    cout << "     ____    _                 _        ____" << endl;
    cout << "    |  _  \\ | |               | |      |  _ \\" << endl;
    cout << "    | |_) | | |  __ _    ___  | | __   | |_) |   ___   __   __" << endl;
    cout << "    |  _<   | | / _` |  / __| | |/ /   |  _ <   / _ \\  \\ \\ / /" << endl;
    cout << "    | |_) | | || (_| | | (__  | | <    | (_) | | (_) |   > <   " << endl;
    cout << "    | ____/ |_| \\__,_|  \\___| |_|\\_\\   | ___/   \\___/  /_/ \\_\\  " << endl;

    cout << "    Lukasz Zych s197842" << endl;

    cout << endl;
    cout << endl;
    cout << endl;
}

bool naPlanszy(int w, int k, int wymiar)
{
    return 0 <= w && w < wymiar && 0 <= k && k < wymiar;
}
void wstawPoleOdzialywania(int w, int k, Plansza& plansza, char znak)
{
    if (naPlanszy(w, k, plansza.wymiar))
    {
        if (plansza.atomy[w][k] == ' ')
        {
            plansza.atomy[w][k] = znak;
        }
        else if (plansza.atomy[w][k] != 'A')
        {
            plansza.atomy[w][k] = '|';
        }
    }
}

void wypiszPom(Plansza plansza)
{
    cout << endl;
    for (int w = 0; w < plansza.wymiar; w++)
    {
        for (int k = 0; k < plansza.wymiar; k++)
        {
            cout << "+--";
        }
        cout << "+" << endl;
        cout << "|";
        for (int k = 0; k < plansza.wymiar; k++)
        {
            if (plansza.atomy[w][k] == '|')
                cout << "L |";
            else
                cout << plansza.atomy[w][k] << " |";
        }
        cout << endl;
    }
    for (int k = 0; k < plansza.wymiar; k++)
    {
        cout << "+--";
    }
    cout << "+" << endl;
    cout << endl;
}

Plansza stworzPlansze(int wymiar, int iloscMin)
{
    Plansza plansza;

    plansza.wymiar = wymiar;
    plansza.iloscMin = iloscMin;
    plansza.ruch = 0;
    plansza.kursor.k = 0;
    plansza.kursor.w = -1;
    plansza.historiaIlosc = 0;
    plansza.indexHistorii = -1;
    plansza.atomy = new char* [wymiar];
    plansza.przypuszczalne = new bool* [wymiar];
    plansza.iloscWolnychPrzypuszczalnych = iloscMin;
    for (int w = 0; w < wymiar; w++)
    {
        plansza.atomy[w] = new char[wymiar];
        plansza.przypuszczalne[w] = new bool[wymiar];
        for (int k = 0; k < wymiar; k++)
        {
            plansza.atomy[w][k] = ' ';
            plansza.przypuszczalne[w][k] = false;
        }
    }
    plansza.informacje = new Promien[wymiar * 4];
    for (int i = 0; i < wymiar * 4; i++)
    {
        plansza.informacje[i].numer = -1;
        plansza.informacje[i].odbicie = ' ';
    }


    while (iloscMin > 0)
    {
        int k = rand() % wymiar;
        int w = rand() % wymiar;
        if (plansza.atomy[w][k] != 'A')
        {
            plansza.atomy[w][k] = 'A';
            wstawPoleOdzialywania(w - 1, k - 1, plansza, '1');
            wstawPoleOdzialywania(w - 1, k, plansza, 'x');
            wstawPoleOdzialywania(w - 1, k + 1, plansza, '2');

            wstawPoleOdzialywania(w, k - 1, plansza, 'x');
            wstawPoleOdzialywania(w, k + 1, plansza, 'x');

            wstawPoleOdzialywania(w + 1, k - 1, plansza, '4');
            wstawPoleOdzialywania(w + 1, k, plansza, 'x');
            wstawPoleOdzialywania(w + 1, k + 1, plansza, '3');
            iloscMin--;
        }

    }

    wypiszPom(plansza);
    return plansza;
}

void skasujPlansze(Plansza& plansza)
{
    for (int w = 0; w < plansza.wymiar; w++)
    {
        delete[] plansza.atomy[w];
        delete[] plansza.przypuszczalne[w];
    }
    delete[] plansza.atomy;
    delete[] plansza.przypuszczalne;
    delete[] plansza.informacje;

}



void wypiszLiniePozioma(int wymiar, bool pusteBoki)
{
    if (pusteBoki)
        cout << "       +";
    else
        cout << "---+---+";
    for (int i = 0; i < wymiar; i++)
    {
        cout << "---+";
    }
    if (pusteBoki)
        cout << "        " << endl;
    else
        cout << "---+---" << endl;
}
void wypiszOpisPola(Promien* informacje, int index)
{
    int numer = informacje[index].numer;
    if (numer < 0)
    {
        cout << "   ";
        return;
    }
    if (numer < 10)
    {
        cout << ' ';
    }
    cout << numer << informacje[index].odbicie;
}

//char ktore G D
void wypiszMiejsceNaStraly(int wymiar, char ktore, Polozenie kursor)
{
    cout << "       |";
    for (int i = 0; i < wymiar; i++)
    {
        if (ktore == 'G' && kursor.w == -1 && i == kursor.k)
            cout << "[v]|";
        else if (ktore == 'D' && kursor.w == wymiar && i == kursor.k)
            cout << "[^]|";
        else
            cout << "   |";
    }
    cout << "       " << endl;
}

char dajOznaczeniePola(int w, int k, const Plansza& plansza, bool koniec, bool help)
{
    if (help)
    {
        if (plansza.atomy[w][k] == 'A')
            return 'A';
        else if (plansza.przypuszczalne[w][k])
            return 'o';
        else return ' ';
    }
    if (koniec)
    {
        if (plansza.atomy[w][k] == 'A' && plansza.przypuszczalne[w][k])
            return 'O';
        else if (plansza.atomy[w][k] == 'A' && !plansza.przypuszczalne[w][k])
            return 'A';
        else if (plansza.atomy[w][k] != 'A' && plansza.przypuszczalne[w][k])
            return 'X';
        else return ' ';
    }
    if (plansza.przypuszczalne[w][k])
        return 'o';
    else return ' ';
}

void wypiszPlansze(const Plansza& plansza, bool koniec, bool help = false)
{
    cout << "w=" << plansza.kursor.w << " k=" << plansza.kursor.k << endl;
    cout << "       |";
    for (int i = 0; i < plansza.wymiar; i++)
    {
        wypiszOpisPola(plansza.informacje, i);
        cout << "|";
    }
    cout << "       " << endl;

    wypiszLiniePozioma(plansza.wymiar, true);
    wypiszMiejsceNaStraly(plansza.wymiar, 'G', plansza.kursor);
    wypiszLiniePozioma(plansza.wymiar, false);

    for (int w = 0; w < plansza.wymiar; w++)
    {
        wypiszOpisPola(plansza.informacje, plansza.wymiar * 4 - 1 - w);

        if (plansza.kursor.k == -1 && plansza.kursor.w == w)
            cout << "|[>]|";
        else
            cout << "|   |";

        for (int k = 0; k < plansza.wymiar; k++)
        {
            char pole = dajOznaczeniePola(w, k, plansza, koniec, help);
            if (plansza.kursor.k == k && plansza.kursor.w == w)
            {
                if (plansza.przypuszczalne[w][k])
                    cout << "[" << pole << "]|";
                else
                    cout << "[" << pole << "]|";
            }
            else
            {
                if (plansza.przypuszczalne[w][k])
                    cout << " " << pole << " |";
                else
                    cout << " " << pole << " |";
            }

        }

        if (plansza.kursor.k == plansza.wymiar && plansza.kursor.w == w)
            cout << "[<]|";
        else
            cout << "   |";

        wypiszOpisPola(plansza.informacje, plansza.wymiar + w);
        cout << endl;
        wypiszLiniePozioma(plansza.wymiar, false);
    }
    wypiszMiejsceNaStraly(plansza.wymiar, 'D', plansza.kursor);
    wypiszLiniePozioma(plansza.wymiar, true);

    cout << "       |";
    for (int i = 0; i < plansza.wymiar; i++)
    {
        wypiszOpisPola(plansza.informacje, plansza.wymiar * 3 - 1 - i);
        cout << "|";
    }
    cout << "       " << endl;
}

bool polozenieKursoraPoprawne(int w, int k, int wymiar)
{
    return -1 <= w && w <= wymiar && -1 <= k && k <= wymiar &&
        (w != -1 || k != -1) && (w != -1 || k != wymiar)
        && (w != wymiar || k != -1) && (w != wymiar || k != wymiar);
}

void przemiescKursor(char polecenie, Polozenie& kursor, int wymiar)
{
    if (polecenie == 'w' && polozenieKursoraPoprawne(kursor.w - 1, kursor.k, wymiar))
    {
        kursor.w--;
    }
    if (polecenie == 's' && polozenieKursoraPoprawne(kursor.w + 1, kursor.k, wymiar))
    {
        kursor.w++;
    }
    if (polecenie == 'a' && polozenieKursoraPoprawne(kursor.w, kursor.k - 1, wymiar))
    {
        kursor.k--;
    }
    if (polecenie == 'd' && polozenieKursoraPoprawne(kursor.w, kursor.k + 1, wymiar))
    {
        kursor.k++;
    }
}

void dodajHistoriePrzed(int indexPoczatekInfo, int indexKoniecInfo, Plansza& plansza)
{
    int dlugoscHistorii = 5;

    Historia elementHistori;
    elementHistori.indexPoczatekInfo = indexPoczatekInfo;
    elementHistori.indexKoniecInfo = indexKoniecInfo;

    elementHistori.infoPoczPrzed = plansza.informacje[indexPoczatekInfo];
    if (indexKoniecInfo != -1)
    {
        elementHistori.infoKonPrzed = plansza.informacje[indexKoniecInfo];
    }

    plansza.historiaIlosc = plansza.indexHistorii + 1;


    if (plansza.historiaIlosc < dlugoscHistorii)
    {
        plansza.historia[plansza.historiaIlosc] = elementHistori;
        plansza.indexHistorii++;
        plansza.historiaIlosc++;
    }
    else
    {
        for (int i = 0; i < dlugoscHistorii - 1; i++)
        {
            plansza.historia[i] = plansza.historia[i + 1];
        }
        plansza.historia[dlugoscHistorii - 1] = elementHistori;
    }
}
void dodajHistoriePo(int indexPoczatekInfo, int indexKoniecInfo, Plansza& plansza)
{
    plansza.historia[plansza.indexHistorii].infoPoczPo = plansza.informacje[indexPoczatekInfo];
    if (indexKoniecInfo != -1)
    {
        plansza.historia[plansza.indexHistorii].infoKonPo = plansza.informacje[indexKoniecInfo];
    }
}

void cofnijHistorie(Plansza& plansza)
{
    if (plansza.indexHistorii < 0)
    {
        return;
    }
    plansza.ruch--;
    Historia elHist = plansza.historia[plansza.indexHistorii];
    plansza.informacje[elHist.indexPoczatekInfo] = elHist.infoPoczPrzed;
    if (elHist.indexKoniecInfo != -1)
    {
        plansza.informacje[elHist.indexKoniecInfo] = elHist.infoKonPrzed;
    }
    plansza.indexHistorii--;
}
void powtorzHistorie(Plansza& plansza)
{
    if (plansza.indexHistorii == 4 || plansza.indexHistorii + 1 == plansza.historiaIlosc)
    {
        return;
    }
    plansza.ruch++;
    Historia elHist = plansza.historia[plansza.indexHistorii];
    plansza.informacje[elHist.indexPoczatekInfo] = elHist.infoPoczPo;
    plansza.informacje[elHist.indexKoniecInfo] = elHist.infoKonPo;
    plansza.indexHistorii++;
}
bool rozpocznijStrzal(Polozenie& polozenie, Ruch& ruch, Polozenie kursor, int wymiar)
{
    if (kursor.w == -1)
    {
        polozenie.w = 0;
        polozenie.k = kursor.k;
        ruch = Ruch::dol;
        return true;
    }
    if (kursor.w == wymiar)
    {
        polozenie.w = wymiar - 1;
        polozenie.k = kursor.k;
        ruch = Ruch::gora;
        return true;
    }
    if (kursor.k == -1)
    {
        polozenie.w = kursor.w;
        polozenie.k = 0;
        ruch = Ruch::prawo;
        return true;
    }
    if (kursor.k == wymiar)
    {
        polozenie.w = kursor.w;
        polozenie.k = wymiar - 1;
        ruch = Ruch::lewo;
        return true;
    }
    return false;
}

int dajIndexInfo(int w, int k, int wymiar)
{
    if (w == -1)
        return k;
    if (w == wymiar)
        return wymiar * 3 - 1 - k;
    if (k == -1)
        return wymiar * 4 - 1 - w;
    if (k == wymiar)
        return wymiar + w;
}
Ruch wyznaczNowyRuch(char pole, Ruch ruch)
{
    if (pole == '1' && ruch == Ruch::prawo)
        return Ruch::gora;
    if (pole == '1' && ruch == Ruch::dol)
        return Ruch::lewo;
    if (pole == '2' && ruch == Ruch::lewo)
        return Ruch::gora;
    if (pole == '2' && ruch == Ruch::dol)
        ruch = Ruch::prawo;
    if (pole == '3' && ruch == Ruch::lewo)
        return Ruch::dol;
    if (pole == '3' && ruch == Ruch::gora)
        return Ruch::prawo;
    if (pole == '4' && ruch == Ruch::prawo)
        return Ruch::dol;
    if (pole == '4' && ruch == Ruch::gora)
        return Ruch::lewo;
    return ruch;
}

Polozenie zmienPolozenie(Polozenie polozenie, Ruch ruch)
{
    Polozenie nowe = polozenie;

    switch (ruch)
    {
    case gora:
        nowe.w--;
        break;
    case dol:
        nowe.w++;
        break;
    case lewo:
        nowe.k--;
        break;
    case prawo:
        nowe.k++;
        break;
    }
    return nowe;
}

void strzal(Plansza& plansza)
{
    Polozenie polozenie;

    Ruch ruch;
    int wymiar = plansza.wymiar;
    bool poczatek = true;
    if (!rozpocznijStrzal(polozenie, ruch, plansza.kursor, wymiar))
    {

        return;
    }
    plansza.ruch++;

    int indexPoczatekInfo = dajIndexInfo(plansza.kursor.w, plansza.kursor.k, wymiar);

    while (naPlanszy(polozenie.w, polozenie.k, wymiar))
    {
        char pole = plansza.atomy[polozenie.w][polozenie.k];
        if (pole == 'A')
        {
            dodajHistoriePrzed(indexPoczatekInfo, -1, plansza);
            plansza.informacje[indexPoczatekInfo].numer = plansza.ruch;
            plansza.informacje[indexPoczatekInfo].odbicie = 'H';
            dodajHistoriePo(indexPoczatekInfo, -1, plansza);
            return;
        }
        if (pole == 'x')
        {
            dodajHistoriePrzed(indexPoczatekInfo, -1, plansza);
            plansza.informacje[indexPoczatekInfo].numer = plansza.ruch;
            if (poczatek)
            {
                Polozenie kolejnyRuch = zmienPolozenie(polozenie, ruch);
                if (plansza.atomy[kolejnyRuch.w][kolejnyRuch.k] == 'A')
                    plansza.informacje[indexPoczatekInfo].odbicie = 'H';
                else
                    plansza.informacje[indexPoczatekInfo].odbicie = 'R';
            }
            else
            {
                plansza.informacje[indexPoczatekInfo].odbicie = 'H';
            }
            dodajHistoriePo(indexPoczatekInfo, -1, plansza);
            return;
        }
        if (pole == '|')
        {
            dodajHistoriePrzed(indexPoczatekInfo, -1, plansza);
            plansza.informacje[indexPoczatekInfo].numer = plansza.ruch;
            plansza.informacje[indexPoczatekInfo].odbicie = 'R';
            dodajHistoriePo(indexPoczatekInfo, -1, plansza);
            return;
        }

        ruch = wyznaczNowyRuch(pole, ruch);
        polozenie = zmienPolozenie(polozenie, ruch);

        poczatek = false;
    }
    int indexKoniecInfo = dajIndexInfo(polozenie.w, polozenie.k, wymiar);

    dodajHistoriePrzed(indexPoczatekInfo, indexKoniecInfo, plansza);
    plansza.informacje[indexPoczatekInfo].numer = plansza.ruch;
    plansza.informacje[indexKoniecInfo].numer = plansza.ruch;
    dodajHistoriePo(indexPoczatekInfo, indexKoniecInfo, plansza);
}

void dodajPrzypuszczalnyAtom(Plansza& plansza)
{
    int w = plansza.kursor.w;
    int k = plansza.kursor.k;
    if (naPlanszy(w, k, plansza.wymiar))
    {
        if (plansza.przypuszczalne[w][k])
        {
            plansza.przypuszczalne[w][k] = false;
            plansza.iloscWolnychPrzypuszczalnych++;
        }
        else if (plansza.iloscWolnychPrzypuszczalnych > 0)
        {
            plansza.przypuszczalne[w][k] = true;
            plansza.iloscWolnychPrzypuszczalnych--;
        }
    }
}

int zliczPunkty(const Plansza& plansza)
{
    int punkty = 0;
    for (int w = 0; w < plansza.wymiar; w++)
    {
        for (int k = 0; k < plansza.wymiar; k++)
        {
            if (plansza.atomy[w][k] == 'A' && plansza.przypuszczalne[w][k])
            {
                punkty++;
            }
        }
    }
    return punkty;
}

void restart(Plansza& plansza)
{
    int wymiar = plansza.wymiar;
    int iloscMin = plansza.iloscMin;
    skasujPlansze(plansza);
    plansza = stworzPlansze(wymiar, iloscMin);
}

bool obslugaPolecen(char polecenie, Plansza& plansza)
{
    switch (polecenie)
    {
    case 'w':
    case 'a':
    case 's':
    case 'd':
    case 'W':
    case 'A':
    case 'S':
    case 'D':
        przemiescKursor(polecenie, plansza.kursor, plansza.wymiar);
        wypiszPlansze(plansza, false);
        return true;
    case ' ':
        strzal(plansza);
        wypiszPlansze(plansza, false);
        return true;
    case 'q':
    case 'Q':
        return false;
    case 'u':
    case 'U':
        cofnijHistorie(plansza);
        wypiszPlansze(plansza, false);
        return true;
    case 'r':
    case 'R':
        powtorzHistorie(plansza);
        wypiszPlansze(plansza, false);
        return true;
    case 'o':
        dodajPrzypuszczalnyAtom(plansza);
        wypiszPlansze(plansza, false);
        return true;
    case 'k':
        wypiszPlansze(plansza, true);
        cout << "ilosc puntkow:" << zliczPunkty(plansza) << endl;
        return false;
    case 'p':
        wypiszPlansze(plansza, true);
        return false;
    case 'n':
        restart(plansza);
        wypiszPlansze(plansza, false);
        return true;
    case 'H':
        wypiszPlansze(plansza, false, true);
        this_thread::sleep_for(chrono::milliseconds(500));
        wypiszPlansze(plansza, false);
        return true;

    }
}

void graj(int wymiar, int iloscMin)
{
    Plansza plansza = stworzPlansze(wymiar, iloscMin);
    wypiszPlansze(plansza, false);

    char polecenie;
    do
    {
        cout << "podaj polecenie:";
        cin.get(polecenie);
    } while (obslugaPolecen(polecenie, plansza));
    skasujPlansze(plansza);
}

int main()
{
    srand(time(NULL));
    const int koniec = 4;
    int wybor = 0;
    while (wybor != koniec)
    {
        wyswietlLogo();
        cout << "MENU" << endl;
        cout << "1 - plansza latwa (5x5) 3 atomy" << endl;
        cout << "2 - plansza srednia (8x8) 5 atomy" << endl;
        cout << "3 - plansza trudna (10x10) 8 atomy" << endl;
        cout << "4 - koniec gry" << endl;
        cout << "wybor:";
        cin >> wybor;
        switch (wybor)
        {
        case 1: graj(5, 3);
            break;
        case 2: graj(8, 5);
            break;
        case 3: graj(10, 8);
            break;
        }
    }
}