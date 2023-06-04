#include <iostream>
#include "header.h"
using namespace std;

int main()
{
    int t1[1000], t2[1000];
    for (int i = 0; i < 1000; i++)
    {
        t1[i] = 1000 - i;
        t2[i] = 1000 - i;
    }
    Rendezes<int> *r[] = {new BuborekosRendezesT<int>, new QuickSortT<int>};
    r[0]->rendez(t1, 1000);
    cout << "Buborekos rendezes:" << endl;
    cout << "===================" << endl;
    cout << "Osszehasonlitasok szama: " << (dynamic_cast<BuborekosRendezesT<int> *>(r[0]))->getHasonlit() << endl;
    cout << "Cserek szama: " << (dynamic_cast<BuborekosRendezesT<int> *>(r[0]))->getCsere() << endl;
    cout << "Ido (ms): " << (dynamic_cast<BuborekosRendezesT<int> *>(r[0]))->getIdo() << endl;
    cout << endl;
    cout << "QuickSort:" << endl;
    cout << "==========" << endl;
    r[1]->rendez(t2, 1000);
    cout << "Osszehasonlitasok szama: " << (dynamic_cast<QuickSortT<int> *>(r[1]))->getHasonlit() << endl;
    cout << "Cserek szama: " << (dynamic_cast<QuickSortT<int> *>(r[1]))->getCsere() << endl;
    cout << "Ido (ms): " << (dynamic_cast<QuickSortT<int> *>(r[1]))->getIdo() << endl;
}