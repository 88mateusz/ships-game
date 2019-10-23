#ifndef POLE_H
#define POLE_H
#include<iostream>
using namespace std;

/*
 * S:
 * 1. Nie powinienes wszedzie powtarzac tej liczby 10. Najlepiej byloby, gdyby byla ona podawana w konstruktorze klasy pole,
 * zapisywana w obiekcie tej klase i uzywana w jego metodach. No bo popatrz, co bedzie, jesli w ktoryms momencie bedziesz
 * chcial zagrac w statki na planszy np. 12 x 12 - wtedy w kazdym miejscu, w ktorym wystepuje liczba 10, bedziesz... zmienial ja na 12,
 * i dodatkowo jeszcze kompilowal projekt od nowa. Tak wiec to 10 powinno byc zapisane jako jakies pole w obiekcie klasy: albo pole
 * prywatne i jakis geter do niego, albo publiczne, ale wtedy koniecznie jako "const" (enkapsulacja). Wtedy tez oczywiscie
 * tablica TAB bedzie tworzona dynamicznie w konstruktorze za pomoca operatora new. Pamietaj, zeby ja w destruktorze usunac operatorem delete.
 *
 * 2. TAB powinno byc prywatne lub protected. Jesli potrzebujesz do niego dostepu publicznego, to powinienes to zrobic poprzez odpowiednie metody.
 * Wewnatrz funkcji main() w ogole nie powinienes sie odwolywac bezposrednio do skladnika TAB.
 *
 * 3. Zawartosc metody start_1 powinna znalezc sie w konstruktorze klasy - to jest po prostu inicjalizacja skladnika TAB. Jej wirtualnosc nie jest nigdzie wykorzystywana.
 *
 * 4. Piszac petle for lepiej dawac odstepy: for (int i = 0; i < 10; i++) - kod jest wtedy czytelniejszy. Tak samo pisalbym cout << costam zamiast cout<<costam.
 */


/*
 * S2:
 *
 * Notka: czasem na okreslenie funkcji z rozpedu uzywam slowa "metoda". Nie musisz sie tym na razie przejmowac, ale zwyczajowo "metodami" nazywa sie funkcje bedace skladowymi
 * jakich klas, natomiast "funkcjami" nazywa sie funkcje luzno umieszczone w kodzie (jak np. "main").
 *
 * 1. Oba konstruktory klasy pole roznia sie tylko tym, ze jeden przyjmuje parametr, a drugi dziala dla tego parametru rownego 10. Wydaje mi sie, ze
 * da sie w jednym konstruktorze wywolac inny, a wiec ten, ktory ma domyslnie parametr rowny 10 powinien tylko wywolywac ten drugi dla parametru rownego 10.
 * Dzieki temu nie bedziesz powtarzal kodu. Nawiasem mowiac, mozesz tez nadac parametrowi wartosc domyslna (chyba jest w c++ cos takiego),
 * ale i tak polecam sprawdzic, jak z jednego konstruktorza wywolywac inny.
 *
 * 2. Skladnik "pole_gry" nie powinien sie tak nazywac - no bo czy ten int jest polem gry? On tak naprawde jest rozmiarem pola gry. Tak wiec powinien sie nazywac "rozmiar_pola_gry".
 *
 * 3. Skladnik "tablicowy" tez ma kiepska nazwe. Powinna to byc nazwa w rodzaju... "pole_gry" :-) Nie chce, zebys myslal, ze sie czepiam nazw, ale dobor nazw jest bardzo wazny.
 * Dobrze dobrane nazwy bardzo zwiekszaja czytelnosc kodu, natomiast nazwy gloszace cos innego niz to, czy faktycznie jest nazwany obiekt, mocno utrudniaja zrozumienie kodu.
 *
 * 4. Parametr przyjmowany przez konstruktor nazywa sie "pole_gracz". Nadaj mu jakas nazwe, ktora lepiej go opisuje [pewnie tez cos z rozmiarem pola gry]
 *
 */

class pole
{
    protected:
    int **tablicowy;
    int pole_gry;
    public:
    pole()                  //konstruktor domniemany
    {
        pole_gry = 10;
        tablicowy = new int * [pole_gry];
        for(int i = 0; i < pole_gry; i++)
            {
                tablicowy[i] = new int [pole_gry];
                for(int y = 0; y < pole_gry; y++)       //wypelnianie zerami
                    {
                        tablicowy[i][y]=0;
                    }
            }
    }
    pole(int pole_gracz)        //konstruktor
    {
        pole_gry = pole_gracz;
        tablicowy = new int * [pole_gry];
        for(int i = 0; i < pole_gry; i++)
            {
                tablicowy[i] = new int [pole_gry];
                for(int y = 0; y < pole_gry; y++)       //wypelnianie zerami
                    {
                        tablicowy[i][y]=0;
                    }
            }
    }
    
    
    virtual void start()
    {
        char litera = 0;
        cout << "\n";
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

    
   virtual ~pole()
    {
        for(int i = 0; i < pole_gry; i++)
            {
                delete [] tablicowy[i];
            }
                delete [] tablicowy;
    }


};


#endif // POLE_H
