#include <iostream>
#include <czlowiek.h>
#include <komputer.h>

using namespace std;
    int max_liczba_statkow, liczba_pol;

int menu_startowe()
{
    cout << "\t\tWitaj w grze\n Podaj dlugosc planszy na jakiej chcesz grac: " << endl;
    cin >> liczba_pol;
    char litera = 0;
    cout << "\nTwoja plansza: \n";
    for(int i = 0; i < liczba_pol; i++)           //petla naglowkowego wiersza
        {
            litera = i + 65;
            cout << "\t|"<<litera;
        }
    for(int i = 0; i < liczba_pol; i++)           //petla rysowania tabeli
        {
            cout << "\n";
                for(int z = 0; z < liczba_pol; z++)           //petla do poziomych kresek
                cout << "---------";
            cout <<"\n  "<<i+1<<"\t|";
        for(int y = 0; y < liczba_pol; y++)
            {
                cout << "   0"  << " \t|";
            }
         }
    if(liczba_pol <= 2)
        {
            max_liczba_statkow = 1;
        }
    if(liczba_pol > 2 && liczba_pol <= 5)
        {
            max_liczba_statkow = liczba_pol;
        }
    if(liczba_pol > 5)
        {
            max_liczba_statkow = liczba_pol + liczba_pol/3;
        }
    cout << "\nMaksymalna liczba statkow wynosi: " << max_liczba_statkow<<endl;

    cout << " \nIle chcesz miec statkow?\n";
    cin >> max_liczba_statkow;
    return liczba_pol, max_liczba_statkow;
}



int main()
{
    menu_startowe();

    czlowiek M(liczba_pol, max_liczba_statkow);
    komputer C(liczba_pol, max_liczba_statkow);

    gracz *poszczegole_kroki_gry;
    poszczegole_kroki_gry = &M;
    poszczegole_kroki_gry -> nadawanie_pozycji();
    poszczegole_kroki_gry -> zaznacz_na_planszy();
    poszczegole_kroki_gry -> rysowanie_planszy();

    poszczegole_kroki_gry = &C;
    poszczegole_kroki_gry -> nadawanie_pozycji();
    poszczegole_kroki_gry -> sprawdzanie_pozycji();
    poszczegole_kroki_gry -> rysowanie_planszy();

    while( (M.kto_wygral() != 1)  && (C.kto_wygral() != 1))
    {
        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\nStrzal komputera na Twojej planszy: \n";
        poszczegole_kroki_gry = &M;
        poszczegole_kroki_gry -> wczytaj_wspol_strzalu();
        poszczegole_kroki_gry -> graj();
        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\nTwoj ruch na planszy komputera: \n";
        poszczegole_kroki_gry = &C;
        poszczegole_kroki_gry -> wczytaj_wspol_strzalu();
        poszczegole_kroki_gry -> graj();
    };
};
