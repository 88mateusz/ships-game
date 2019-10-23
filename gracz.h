#ifndef GRACZ_H
#define GRACZ_H

#include<iostream>
#include<string.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class gracz
{
    protected:
    int **plansza;
    int wielkosc_pola_gracza;
    int liczba_statkow;
    int **tablica_wspol_statkow;
    int pozostala_liczba_statkow;
    char torpeda_1;
    int torpeda_2;

    public:
    gracz(int rozmiar_planszy, int ilosc_statkow)
    {
        wielkosc_pola_gracza = rozmiar_planszy;          //konstruktor pola gry
        plansza = new int * [wielkosc_pola_gracza];
        for(int i = 0; i < wielkosc_pola_gracza; i++)
            {
                plansza[i] = new int [wielkosc_pola_gracza];
                for(int y = 0; y < wielkosc_pola_gracza; y++)       //wypelnianie zerami
                    {
                        plansza[i][y]=0;
                    }
            }
        pozostala_liczba_statkow = ilosc_statkow;       //konstruktor od ilosci statkow
        liczba_statkow = ilosc_statkow;
        tablica_wspol_statkow = new int *[liczba_statkow];
        for (int i = 0; i < liczba_statkow; i++)
            {
                tablica_wspol_statkow[i] = new int [2];
            }
    }


    virtual void nadawanie_pozycji(int i = 0)
    {
        srand(time(NULL));
        for ( i; i < liczba_statkow; i++)
        {
           tablica_wspol_statkow[i][0] = rand()%(wielkosc_pola_gracza)-0;          //pierwsza wspolrzedna statku
        }
        for ( i; i < liczba_statkow; i++)
        {
           tablica_wspol_statkow[i][1] = rand()%(wielkosc_pola_gracza)-0;          //druga wspolrzedna statku
        }
    }

//**************************************************************************************************************************************

    virtual void sprawdzanie_pozycji()
    {                  //test poprawnosci wsplrzednych
        for ( int i = 0; i < (liczba_statkow); i++)
        {
            for ( int y = i + 1 ; y < liczba_statkow; y++)               //wartosc inicjalizujaca: warunek wykluczajacy sprawdzanie tych samych statkow np 2 z 2...
            {
                if ( ( ( abs ( tablica_wspol_statkow[i][0] - tablica_wspol_statkow[y][0] ) ) < 2 ) && ( ( abs ( tablica_wspol_statkow[i][1] - tablica_wspol_statkow[y][1] ) ) < 2 ) )
                {
                    nadawanie_pozycji(i);

                    i=0;        //niech sprawdza od nowa
                    y=1;
                }
               // cout << "\nPetla for z y\n";
            }
           // cout << "\nPetla for z i\n";
        }
    }

//**************************************************************************************************************************************

    virtual int zaznacz_na_planszy(int a = 0)
    {
         for(int i = 0; i < liczba_statkow; i++)
         plansza[tablica_wspol_statkow[i][1]-1][tablica_wspol_statkow[i][0]] = a;
    }

//**************************************************************************************************************************************

    virtual void pokaz_wspolrzedne()
    {
        char litera = 0;
        for ( int i = 0; i < liczba_statkow; i++)
        {
            litera = tablica_wspol_statkow[i][0] + 65;
           cout << litera <<" "<< tablica_wspol_statkow[i][1]<<endl;
        }
    }

//**************************************************************************************************************************************

    virtual void rysowanie_planszy()
    {

            char litera = 0;
            for(int i = 0; i < wielkosc_pola_gracza; i++)           //petla naglowkowego wiersza
                {
                    litera = i + 65;
                    cout << "\t|"<<litera;
                }
            for(int i = 0; i < wielkosc_pola_gracza; i++)           //petla rysowania tabeli
                {
                    cout << "\n";
                        for(int z = 0; z < wielkosc_pola_gracza; z++)           //petla do poziomych kresek
                        cout << "---------";
                    cout <<"\n  "<<i+1<<"\t|";
                for(int y = 0; y < wielkosc_pola_gracza; y++)
                    {
                        cout << "   " << plansza[i][y] << " \t|";
                    }
                }
            cout << "\n\n";

    }

//**************************************************************************************************************************************

    virtual void wczytaj_wspol_strzalu() = 0;

//**************************************************************************************************************************************


   virtual int graj()
    {
        bool pomocnicza = 1;


            for( int i = 0; i < liczba_statkow; i++)
            {
                if( ( tablica_wspol_statkow[i][0] == (torpeda_1) ) && (tablica_wspol_statkow[i][1] == torpeda_2-1) )
                {
                    cout << "\n Trafiony!";
                    pozostala_liczba_statkow-=1;
                    cout << "\nLiczba pozostalych jednomasztowcow : "<<pozostala_liczba_statkow<<endl;
                    plansza[torpeda_2-1][torpeda_1] = 11 ;
                    rysowanie_planszy();
                    pomocnicza = 0;
                }
            }
        if( pomocnicza)
        {
            cout << "\nPudlo!";
            plansza[torpeda_2-1][torpeda_1] = 1 ;
            rysowanie_planszy();
        }
    }

//**************************************************************************************************************************************

//   virtual int kto_wygral() = 0;

//**************************************************************************************************************************************

   virtual ~ gracz()
    {
        for( int i = 0; i < wielkosc_pola_gracza; i++)
            {
                delete [] plansza[i];
            }
        delete [] plansza;

        for( int i = 0; i < liczba_statkow; i++)
            {
                delete [] tablica_wspol_statkow[i];
            }
        delete [] tablica_wspol_statkow;
    }
};

#endif // GRACZ_H
