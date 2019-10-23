#ifndef GRACZ_H
#define GRACZ_H
#include<string.h>
#include <pole.h>

#include <cstdlib>
#include <ctime>

using namespace std;

/*
 * S:
 * 1. Ten plik i odpowiedni .cpp nie zostaly dodane do projektu - nie ma ich w statki.pro.
 *
 * 2. A co, gdybysmy chcieli gre w ktorej mam wiecej niz 4 statki? W tym momencie byloby sporo przerobek, zeby to uzyskac.
 * Konsturktor tej klasy powinien przyjmowac jako argument liczbe statkow. Same pozycje statkow musialbys wtedy
 * przechowywac w tablicy/ach tworzonych za pomoca new w konstruktorze.
 *
 * 3. Odnosnie tych switch'y ponizej - jesli chcesz przeliczac litery A, B, ... na liczby, to chyba mozna zerobic zwykle odejmowanie:
 * np. 'E'-'A' daje chyba w wyniku 4 (z tego, co kojarze, kompilator potrafi traktowac char jako typ liczbowy - ale moge sie mylic...).
 *
 */

/*
 * S2: (najpierw przeczytaj uwagi w pole.h)
 *
 * 1. Tak jak w pole.h - nazwy skladnikow i parametrow przyjmowanych przez funkcje powinny byc bardziej opisowe.
 *
 * 2. Pole "maksymalna" tak naprawde duplikuje rozmiar pola gry zapisany w klasie pole. Z tego, co widze, poza konstruktorem jedynie odczytujesz te wartosc.
 * Zamiast duplikowac, powinienes w klasie pole dac tzw. getter - funkcje o nazwie np. get_rozmiar_pola_gry,
 * ktora bedzie tylko zwracala tego inta, i ten getter wywolywac tutaj. A skladnik "maksymlana" bylby wtedy do usuniecia.
 * Nawiasem mowiac, tutaj wychodzi nam bokiem uzywanie polskojezycznych nazw - getSomething lub get_something to
 * zwyczajowo uzywane nazwy na funkcje, ktore po prostu zwracaja wartosc skladnika something - z polskojezyczna nazwa skladnika to "get" brzmi slabo.
 * Podobnie, dla funkcji, ktore ustawiaja skladnik something, stosuje sie zazwyczaj nazwy setSomething lub set_something.
 * To ktora z nich wybrac, zalezy od konwencji stosowanej w projekcie, tzn. od tego, czy wieloczlonowe nazwy piszesz jako jakasDlugaNazwa (tzw. camelcase), czy jakas_dluga_nazwa;
 * z tego, co widze, Ty chyba wszedzie uzywasz drugiej wersji.
 *
 * 3. Skladniki "torpeda_1" i "torpeda_2" sa wykorzystywane tylko w jednej funkcji (nadajesz im tam na wstepie nowe wartosci, stare nie sa juz nigdy potem uzywane),
 * a wiec nie powinny byc skladnikami klasy, a zmiennymi lokalnymi w tej funkcji. Generalnie wszystkie skladniki zapisane w obiekcie skladaja sie na cos, co nazywamy "stanem" obiektu,
 * no i na ogol jest tak, ze im "mniejszy" jest stan obiektu (im bardziej bezstanowy obiekt), tym lepiej, bo latwiej go testowac, uzywac i kontrolowac.
 *
 * 4. Odnosnie publicznego skladnika "koniec" - powinien byc prywatny i udostepniany przez jakas publiczna metode, nazwana np. "sprawdz_koniec_gry", ktora po prostu bedzie go zwracac.
 * To, ze jest on publiczny, ma te wade, ze teraz kazdy moze go sobie zmienic - np. w funkcji main moge go zmienic, a nie powinienem miec takiej mozliwosci, bo jest on czescia implementacji tej klasy.
 * Bardziej odpowiednim typem dla skladnika koniec bylby bool.
 *
 * 5. Teraz, na koniec, najgrubszy problem: na pewno wiesz, ze klasy komp i gracz sa... niemal identyczne. Mnostwo kodu jest skopiowanego i powielonego. Jesli teraz zechcesz wprowadzic
 * np. wyzej wymienione zmiany do klasy komp, to bedziesz musial zrobic identyczne zmiany w klasie gracz. I tak za kazdym razem - a to tylko jeden z problemow.... tak wiec koniecznie trzeba to przerobic.
 * Mozesz sprobowac mniej wiecej czegos takiego:
 *
 * 5a) Struktura klas musi zostac poprawiona - wszak, na dobra sprawe, komputer tez jest graczem. Powinienes miec taka strukture: klase gracz, ktora zawiera mniej wiecej ten kod, co teraz
 * (oczywiscie poprawiony j.w.), i dwie klasy z niej dziedziczace, o nazwach np. gracz_czlowiek i gracz_komputer (albo cos w ten desen - mozesz pomyslec nad czyms lepszym :P).
 * Zarowno czlowiek, jak i komputer, sa tutaj graczami - tak wiec dziedziczenie dobrze oddaje rzeczywiste relacje.
 * [Nawiasem mowiac, klasa gracz nie powinna dziedziczyc z klasy pole (nie mozesz powiedziec, ze "gracz JEST polem", a co najwyzej, ze "gracz POSIADA pole"
 * - tak wiec pole powinno byc skladnikiem wewnatrz klasy gracz, a nie klasa bazowa) - ale tej ostatniej zmiany na razie nie rob, zeby nie komplikowac; zostaw to na sam koniec.]
 *
 * 5b) W klasie gracz powinienes miec funkcje wirtualna (najlepiej protected) o nazwie np. wczytaj_wspolrzedne_statku, ktora zajmie sie wczytaniem
 * (w jakis tam abstrakcyjny sposob - w tej klasie nie bedziesz go definiowal) wspolrzednych pojedynczego statku.
 * W tej klasie nie bedziesz pisal ciala tej metody, a zamiast tego zdefiniujesz ja w klasach gracz_czlowiek i gracz_komputer (na rozne sposoby oczywiscie).
 * Funkcja ta powinna zwracac pare wspolrzednych (na razie chyba moze to byc tablica dlugosci 2 albo cos w ten desen). Tej abstrakcyjnej metody uzyjesz w ciele funkcji nadaj w klasie gracz (koniecznie!)
 * za kazdym razem, kiedy bedziesz chcial wczytac wspolrzedne kolejnego statku (robisz to na poczatku i potem przy testowaniu).
 * Metoda nadaj bedzie zaimplementowana tylko w klasie gracz - nie w jej klasach pochodnych. W klasach pochodnych dodasz tylko metody dostarczajace wspolrzedne statkow.
 * Nawiasem mowiac, z tego, co kojarze, kiedy w klasie masz choc jedna wirtualna metode, powinienes juz dac wirtualny destruktor - upewnij sie co do tego, bo nie pamietam juz tego dobrze.
 *
 * 5c) Funkcja start tez jest niemal identyczna - rozni sie tylko tekstem wypisywanym na konsole. To tez trzeba zmienic. To samo w pokaz.
 *
 * 5d) Funkcja graj - ta sama historia, co w przypadku funkcji nadaj. W jakis abstrakcyjny sposob (ktory zdefiniujesz dopiero w klasach pochodnych) bedziesz wczytywal wspolrzedne kolejnego strzalu,
 * a potem juz postepuejsz tak samo. Tak wiec w klasie gracz powinna byc metoda wirtualna wczytaj_wspolrzedne_strzalu, ktora zdefiniujesz w obu klasach dziedziczacych.
 * Przestrzegam przed wykorzystaniem tutaj ponownie metody, o ktorej pisalem w 5b - ale sprobuj sam zastanowic sie, dlaczego :-) [nie chodzi tu oczywiscie o jej nazwe]
 *
 * Generalnie dokonujac tych zmian, o ktorych pisalem, poloz nacisk na to, zeby nie duplikowac kodu i zeby nazwy dobrze nazywaly to, co sie pod nimi kryje. Nazwy metod klasy gracz:
 * nadaj, pokaz, itd. tez sa dosc skryte.
 *
 */

class gracz : public pole
{
private:
    int ** statkowy;
    int ilosc;      //zmienna okreslajaca ilosc statkow
    char torpeda_1;
    int torpeda_2;
    int szansa;
    int maksymalna;
public:
    int koniec;

public:
    gracz(int zadana, int plansza) : pole(plansza)       //konstruktor budujacy tablice wspolrzednych statkow z lista inicjalizacyjną obiektu dziedziczonego,
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
        char litera = 0;
        cout << "\nPodaj pozycje swoich statkow. \n Masz " << ilosc << " jednomasztowce:\n";
        for ( int i = 0; i < ilosc; i++)
        {
            cout << (i+1) << " statek: \n"<<endl;
            cin >> litera >> statkowy[i][1];
            statkowy[i][0] = litera - 65;
        };
                      //test poprawnosci wsplrzednych

        litera = 0;
        for ( int i = 0; i < (ilosc); i++)
        {
            for ( int y = i + 1 ; y < ilosc; y++)               //wartosc inicjalizujaca: warunek wykluczajacy sprawdzanie tych samych statkow np 2 z 2...
            {
                if ( ( ( abs ( statkowy[i][0] - statkowy[y][0] ) ) < 2 ) && ( ( abs ( statkowy[i][1] - statkowy[y][1] ) ) < 2 ) )
                {
                    cout << "\nProponowany statek " << statkowy[i][0]<<statkowy[i][1] << " jest za blisko istniejacego statku " << statkowy[y][0] << statkowy[y][1] << " Podaj prosze nowe wspolrzedne: \n";
                    cin >> litera >> statkowy[y][1];
                    statkowy[y][0] = litera - 65;
                    i=0;        //niech sprawdza od nowa
                    y=1;
                }
               // cout << "\nPetla for z y\n";
            }
           // cout << "\nPetla for z i\n";
        };
        for(int i = 0; i < ilosc; i++)
        tablicowy[statkowy[i][1]-1][statkowy[i][0]] = 'X';
    }

    void pokaz()
    {
        char litera = 0;
        for ( int i = 0; i < ilosc; i++)
        {
            litera = statkowy[i][0] + 65;
           cout << litera <<" "<< statkowy[i][1]<<endl;
        }
    }


    void start()
    {

            char litera = 0;
            cout << "\nTwoja plansza: \n";
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

    int graj()
    {
        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        int pomocnicza =1;
        cout << "\nKomputer atakuje: ";
        srand(time(NULL));
        torpeda_1 = (rand()%(maksymalna)-0) + 65;
        torpeda_2 = (rand()%(maksymalna)-0) +1;
        cout << "\n "<<torpeda_1<<torpeda_2 ;


            for( int i = 0; i < ilosc; i++)
            {
                if( ( statkowy[i][0] == (torpeda_1-65) ) && (statkowy[i][1] == torpeda_2) )
                {
                    cout << "\n Trafiony!";
                    szansa-=1;
                    cout << "\nPozostala liczba Twoich statkow: "<<szansa<<endl;
                    tablicowy[statkowy[i][1]-1][statkowy[i][0]] = 11 ;
                    start();
                    pomocnicza = 0;
                }
            }
        if( pomocnicza == 1)
        {
            cout << "\nPudlo!";
            tablicowy[torpeda_2-1][torpeda_1-65] = 1 ;
            start();
        }
        if( szansa == 0)
        {
            cout << "\nWygral komputer!";
            return  koniec = 1;
        }

    }



    ~gracz()
    {
        for(int i = 0; i < ilosc; i++)
        {
            delete []statkowy[i];
        }
        delete [] statkowy;
    }



};


#endif // GRACZ_H


