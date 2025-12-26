#include "funcs.h"
#include <iostream>
#include <vector>

void Swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void Zadacha1Sort2()
{
    using namespace std;

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    while (n < 0) {
        cout << "Некорректный размер" << endl;
        cout << "Введите размер массива: ";
        cin >> n;
    }


    vector<int> array(n);

    cout << "Введите элементы: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    // Гарантируется, что первый элемент всегда будет наименьшим, поэтому его не берем (n - 1)
    for (int i = 0; i < n - 1; i++) {   // для сортировки достаточно n-1 проходов
        int start = n - 1 - i;
        for (int j = 0; j < start; j++) { // т.к. берем элемент j+1, то чтобы не выйти за границу берет n - 1 - i элементов
            if (array[j] > array[j + 1]) {
                Swap(array[j], array[j + 1]);
            }
        }

        for (int k = 0; k < n; k++) {
            cout << array[k] << " ";

            if (k == start - 1) {
                cout << "| ";
            }
        }

        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}