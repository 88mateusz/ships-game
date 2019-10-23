#ifndef KOMP_H
#define KOMP_H
#include <pole.h>

#include <cstdlib>
#include <ctime>


/*
 * S:
 * 1. Skoro komp dziedziczy z pole, to po co dubluje skladnik TAB?
 */

class komp : public pole
{
private:
    int ** statkowy;
    int ilosc;
    int maksymalna;
    char torpeda_1;
    int torpeda_2;
    int szansa;
public:
    int koniec;

public:
    komp(int zadana, int plansza) : pole(plansza)       //konstruktor budujacy tablice wspolrzednych statkow z lista inicjalizacyjną obiektu dziedziczonego,
    {
        maksymalna = plansza;
        ilosc = zadana;
        szansa = zadana;
        statkowy = new int *[ilosc];
        for (int i = 0; i < ilosc; i++)
        {
            statkowy[i] = new int [2];
        }
    }

    void nadaj()                //funkcja nadawania pozycji
    {

        int liczba;
        srand(time(NULL));
        for ( int i = 0; i < ilosc; i++)
        {
           statkowy[i][0] = rand()%(maksymalna)-0;          //pierwsza wspolrzedna statku
        }
        for ( int i = 0; i < ilosc; i++)
        {
           statkowy[i][1] = rand()%(maksymalna)-0;          //druga wspolrzedna statku
        }
                      //test poprawnosci wsplrzednych

        char litera = 0;
        for ( int i = 0; i < (ilosc); i++)
        {
            for ( int y = i + 1 ; y < ilosc; y++)               //wartosc inicjalizujaca: warunek wykluczajacy sprawdzanie tych samych statkow np 2 z 2...
            {
                if ( ( ( abs ( statkowy[i][0] - statkowy[y][0] ) ) < 2 ) && ( ( abs ( statkowy[i][1] - statkowy[y][1] ) ) < 2 ) )
                {
                    statkowy[y][0] =  rand()%(maksymalna)-0;
                    statkowy[y][1] =  rand()%(maksymalna)-0;
                    i=0;        //niech sprawdza od nowa
                    y=1;
                }
               // cout << "\nPetla for z y\n";
            }
           // cout << "\nPetla for z i\n";
        }
        for(int i = 0; i < ilosc; i++)
            tablicowy[statkowy[i][1]][statkowy[i][0]] = 0;
    }

    void pokaz()
    {
        char litera = 0;
        for ( int i = 0; i < ilosc; i++)
        {
            litera = statkowy[i][0] + 65;
           cout << litera << " " << statkowy[i][1]+1 << endl;
        }
    }

    void start()
    {
            char litera = 0;
            cout << "\n\nPlansza komputera: \n";
            for(int i = 0; i < pole_gry; i++)           //petla naglowkowego wiersza
                {
                    litera = i + 65;
                    cout << "\t|"<<litera;
                }
            for(int i = 0; i < pole_gry; i++)           //petla rysowania tabeli
                {
                    cout << "\n";
                        for(int z = 0; z < pole_gry; z++)           //petla do poziomych kresek
                        cout << "---------";
                    cout <<"\n  "<<i+1<<"\t|";
                for(int y = 0; y < pole_gry; y++)
                    {
                        cout << "   " << tablicowy[i][y] << " \t|";
                    }
                }
    }

    int graj()          //czlowiek atakuje komputer
    {
        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        int pomocnicza =1;
        cout << "\nPodaj wspolrzedne statku ktory chcesz zniszczyc: ";
        cin >> torpeda_1 >> torpeda_2;
        torpeda_1-=65;


            for( int i = 0; i < ilosc; i++)
            {
                if( ( statkowy[i][0] == (torpeda_1) ) && (statkowy[i][1] == torpeda_2-1) )
                {
                    cout << "\n Trafiony!";
                    szansa-=1;
                    cout << "\nLiczba pozostalych jednomasztowcow : "<<szansa<<endl;
                    tablicowy[torpeda_2-1][torpeda_1] = 11 ;
                    start();
                    pomocnicza = 0;
                }
            }
        if( pomocnicza == 1)
        {
            cout << "\nPudlo!";
            tablicowy[torpeda_2-1][torpeda_1] = 1 ;
            start();
        }
        if( szansa == 0)
        {
            cout << "\nWygral gracz!";
            return  koniec = 1;
        }
    }

    ~komp()
    {
        for(int i = 0; i < ilosc; i++)
        {
            delete []statkowy[i];
        }
        delete [] statkowy;
    }



};

#endif // KOMP_H
