#ifndef CZLOWIEK_H
#define CZLOWIEK_H
#include <gracz.h>


class czlowiek: public gracz
{
public:
    czlowiek(int rozmiar, int ilosc) : gracz (rozmiar, ilosc)
    {}


    void nadawanie_pozycji(int i = 0)
    {
        char litera = 0;
        cout << "\nPodaj pozycje swoich statkow. \n Masz " << liczba_statkow << " jednomasztowce:\n";
        for ( i; i < liczba_statkow; i++)
        {
            cout << (i+1) << " statek: \n"<<endl;
            cin >> litera >> tablica_wspol_statkow[i][1];
            tablica_wspol_statkow[i][0] = litera - 65;
        }
    }

    int zaznacz_na_planszy(int b)
    {
            b = 88;
            for(int i = 0; i < liczba_statkow; i++)
            plansza[tablica_wspol_statkow[i][1]-1][tablica_wspol_statkow[i][0]] = b;
    }

    void wczytaj_wspol_strzalu()
    {
        cout << "\nAtak: ";
        srand(time(NULL));
        torpeda_1 = (rand()%(wielkosc_pola_gracza)-0) + 65;
        torpeda_2 = (rand()%(wielkosc_pola_gracza)-0) +1;
        cout << "\n "<<torpeda_1<<torpeda_2 ;

    }

    int kto_wygral()
    {
        if( pozostala_liczba_statkow == 0)
        {
            cout << "\nWygral komputer!";

            return 1;
        }
        else
        {
            return 0;
        }
    }


    ~czlowiek()
    {}

};

#endif // CZLOWIEK_H
