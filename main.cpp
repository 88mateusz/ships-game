#include <iostream>

using namespace std;

class Example {
    public:
        void foo() { cout << "zwykla metoda\n"; }
         void vFoo() { cout << "metoda wirtualna klasa Example\n"; }
};

class Example2 : public Example {
    public:
        void foo() { cout << "zwykla metoda2\n"; }
        void vFoo() { cout << "metoda wirtualna klasa Example2\n"; }
};

int main()
{
    Example *p = new Example;
    p->foo();
    p->vFoo();
    delete p;

    p = new Example2;
    p->foo();
    p->vFoo();
    delete p;

    cin.sync();
    cin.get();

    return 0;
}
