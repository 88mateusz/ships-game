#ifndef KOMPUTER_H
#define KOMPUTER_H
#include <gracz.h>

class komputer : public gracz
{

public:
    komputer(int rozmiar, int ilosc) : gracz (rozmiar, ilosc)
    {}

    void wczytaj_wspol_strzalu()
    {
        cout << "\nPodaj wspolrzedne statku ktory chcesz zniszczyc: ";
        cin >> torpeda_1 >> torpeda_2;
        torpeda_1-=65;
    }

    int kto_wygral()
    {
        if( pozostala_liczba_statkow == 0)
        {
            cout << "\nWygral gracz!";            
            return 1;
        }
        else
        {
            return 0;
        }
    }



    ~komputer()
    {}

};
#endif // KOMPUTER_H
