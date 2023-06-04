#pragma once
#include <iostream>
#include <ctime>
#include <cmath>

template <class T>
class Rendezes
{
protected:
    virtual bool kisebb(T a, T b) = 0;
    virtual void csere(T &a, T &b) = 0;

public:
    virtual void rendez(T *tomb, int n) = 0;
};

class Stat
{
private:
    unsigned int ido, nHasonlit, nCsere;
    std::clock_t c;

protected:
    void kezd();
    void vege();
    void init();
    void incHasonlit();
    void incCsere();

public:
    Stat();
    unsigned int getIdo();
    unsigned int getHasonlit();
    unsigned int getCsere();
};

template <class T>
class BuborekosRendezes : public Rendezes<T>
{
protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

template <class T>
class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat
{
protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

template <class T>
class QuickSort : public Rendezes<T>
{
private:
    void qsort(T *a, int bal, int jobb);
    int particional(T *a, int bal, int jobb);

protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

template <class T>
class QuickSortT : public QuickSort<T>, public Stat
{

protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

//////////////Stat osztály:///////////////////////////////////////////////////////////////////////////////
Stat::Stat() : ido(0), nHasonlit(0), nCsere(0) {}

void Stat::init()
{
    ido = nHasonlit = nCsere = 0;
}

void Stat::kezd()
{
    c = std::clock();
}

void Stat::vege()
{
    ido = (unsigned int)((std::clock() - c) * 1000.0 / CLOCKS_PER_SEC);
}

void Stat::incHasonlit()
{
    nHasonlit++;
}

void Stat::incCsere()
{
    nCsere++;
}

unsigned int Stat::getIdo()
{
    return ido;
}

unsigned int Stat::getHasonlit()
{
    return nHasonlit;
}

unsigned int Stat::getCsere()
{
    return nCsere;
}
/// BuborekosRendezes és BuborekosRendezesT osztályok://///////////////////////////////////////////////////////
template <class T>
bool BuborekosRendezes<T>::kisebb(T a, T b)
{
    return a < b;
}

template <class T>
void BuborekosRendezes<T>::csere(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void BuborekosRendezes<T>::rendez(T *tomb, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (!kisebb(tomb[j], tomb[j + 1]))
            {
                csere(tomb[j], tomb[j + 1]);
            }
        }
    }
}

template <class T>
bool BuborekosRendezesT<T>::kisebb(T a, T b)
{
    this->incHasonlit();
    return BuborekosRendezes<T>::kisebb(a, b);
}

template <class T>
void BuborekosRendezesT<T>::csere(T &a, T &b)
{
    this->incCsere();
    BuborekosRendezes<T>::csere(a, b);
}

template <class T>
void BuborekosRendezesT<T>::rendez(T *tomb, int n)
{
    this->init();
    this->kezd();
    BuborekosRendezes<T>::rendez(tomb, n);
    this->vege();
}

/// QuickSort és QuickSortT osztályok:////////////////////////////////////////////////////////////////
template <class T>
bool QuickSort<T>::kisebb(T a, T b)
{
    return a < b;
}

template <class T>
void QuickSort<T>::csere(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int QuickSort<T>::particional(T *a, int bal, int jobb)
{
    T pivot = a[jobb];
    int i = bal - 1;

    for (int j = bal; j <= jobb - 1; j++)
    {
        if (kisebb(a[j], pivot))
        {
            i++;
            csere(a[i], a[j]);
        }
    }
    csere(a[i + 1], a[jobb]);
    return i + 1;
}

template <class T>
void QuickSort<T>::qsort(T *a, int bal, int jobb)
{
    if (bal < jobb)
    {
        int pi = particional(a, bal, jobb);
        qsort(a, bal, pi - 1);
        qsort(a, pi + 1, jobb);
    }
}

template <class T>
void QuickSort<T>::rendez(T *tomb, int n)
{
    qsort(tomb, 0, n - 1);
}

template <class T>
bool QuickSortT<T>::kisebb(T a, T b)
{
    this->incHasonlit();
    return QuickSort<T>::kisebb(a, b);
}

template <class T>
void QuickSortT<T>::csere(T &a, T &b)
{
    this->incCsere();
    QuickSort<T>::csere(a, b);
}

template <class T>
void QuickSortT<T>::rendez(T *tomb, int n)
{
    this->init();
    this->kezd();
    QuickSort<T>::rendez(tomb, n);
    this->vege();
}