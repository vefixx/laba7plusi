#include <iostream>
#include "windows.h"
#include "funcs.h"

int main()
{
    using namespace std;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    do {
        cout << "Введите номер задачи:\n";
        cout << "0) Выход\n";
        cout << "1) Сортровка простых обменов\n";
        cin >> n;
        cin.ignore();

        switch (n) {
        case 1:
            Zadacha1Sort2();
            break;
        case 2:
            break;
        case 3:
            break;
        case 0:
            break;
        default:
            cout << "Неверный номер задачи" << endl;
        }
    } while (n != 0);
}