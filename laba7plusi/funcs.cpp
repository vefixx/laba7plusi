#include "funcs.h"
#include <iostream>
#include <vector>
#include "structs.h"
#include <vector>
#include <fstream>
#include <string>
#include "merge_sort.h"
#include <iomanip>

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

    for (int i = 0; i < n - 1; i++) {   // для сортировки достаточно n-1 проходов
        int start = n - 1 - i;
        for (int j = 0; j < start; j++) { // т.к. сравниваем с j+1, то чтобы не выйти за границу берем n - 1 - i элементов (start)
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

void Zadacha2ExamTaskC14()
{
    using namespace std;

    int k, n;
    cout << "Введите код клиента K: ";
    cin >> k;

    if (cin.fail() || k < 10 || k > 99) {
        cout << "Неверный ввод кода" << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        return;
    }
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    cout << "Введите количество клиентов: ";
    cin >> n;

    if (cin.fail() || n < 0) {
        cout << "Неверный ввод количества" << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        return;
    }
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    vector<Client> clients;
    Client client;
    for (int i = 0; i < n; i++) {
        while (true) {
            cout << "Введите данные о клиенте (год месяц код продолжительность): ";
            cin >> client.year >> client.month >> client.code >> client.duration;

            if (cin.fail() || client.year < 2000 || client.year > 2010
                || client.month < 1 || client.month > 12
                || client.code < 10 || client.code > 99
                || client.duration < 1 || client.duration > 30) {
                cout << "Неверный ввод" << endl;
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                continue;
            }
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            break;
        }

        clients.push_back(client);
    }

    // Находим нашего клиента среди списка
    bool has_client_with_code_k = false;
    for (const Client& client : clients) {
        if (client.code == k) {
            has_client_with_code_k = true;
            break;
        }
    }

    if (!has_client_with_code_k) {
        cout << "Нет данных" << endl;
        return;
    }

    // Собираем массив из уникальных годов, чтобы далее находить по ним мин. продолжительность
    int years[11];
    int years_result_count = 0;
    for (const Client& client : clients) {
        if (client.code == k) {
            bool found_this_year = false;
            for (int year : years) {
                if (year == client.year) {
                    found_this_year = true;
                    break;
                }
            }

            if (!found_this_year) {
                years[years_result_count] = client.year;
                years_result_count++;
            }
        }
    }

    vector<Result> results;
    // Находим для каждого такого года месяц с минимальной продолжительностью
    for (int year : years) {
        int min_duration_for_this_year = 31;
        int best_month_number = 0;

        for (const Client& client : clients) {
            if (client.code == k && client.year == year) {
                if (client.duration < min_duration_for_this_year) {
                    min_duration_for_this_year = client.duration;
                    best_month_number = client.month;
                }
                else 
                    // если таких месяцев несколько, то выбирать 
                    // месяц с наибольшим номером
                    if (client.duration == min_duration_for_this_year) {
                        if (client.month > best_month_number) {
                            best_month_number = client.month;
                        }
                }
            }
        }

        if (best_month_number > 0) {
            Result result;
            result.year = year;
            result.month = best_month_number;
            result.duration = min_duration_for_this_year;

            results.push_back(result);
        }
    }

    if (results.size() == 0) {
        cout << "Нет данных" << endl;
        return;
    }

    // Сортируем пузырьком по годам
    for (int i = 0; i < results.size() - 1; i++) {
        for (int j = 0; j < results.size() - i - 1; j++) {
            if (results[j].year > results[j + 1].year) {
                Result temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }

    for (const Result& result : results) {
        cout << result.year << " "
            << result.month << " " <<
            result.duration << endl;
    }
}

void Zadacha3Five12()
{
    using namespace std;

    vector<Student> students;

    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Файл input.txt не найден" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Парсим строку, идем до первого пробела. Все что перед пробелом - имя фамилия, а после - балл
        int space = -1;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || line[i] == '\t') {
                space = i;
                break;
            }
        }

        if (space == -1 || space == line.length() - 1) {
            cout << "Некорректный формат строки" << endl;
            continue;
        }

        string surname = line.substr(0, space);
        if (surname.length() > 15) {
            cout << "Строка имеет некорректный формат (длина фамилии > 15)" << endl;
            continue;
        }

        // Доходим до первого символа (баллы), чтобы пропустить все пробелы
        int start = space;
        while (line[start] == ' ') {
            start++;
        }

        int score = 0;
        for (int i = start; i < line.length(); i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                score = score * 10 + (line[i] - '0');
            }
            else {
                cout << "Некорректны формат баллов для строки" << endl;
                score = -1;
                break;
            }
        }

        if (score == -1) {
            continue;
        }

        Student student;
        student.surname = surname;
        student.score = score;
        students.push_back(student);
    }

    file.close();

    cout << "Получено " << students.size() << " учеников" << endl;
    
    if (students.size() == 0) {
        return;
    }

    MergeSortStudents(students, 0, students.size() - 1);

    // Запись в файл
    ofstream out_file("output.txt");

    for (const Student& student : students) {
        out_file << left << setw(15) << student.surname
            << right << setw(3) << student.score
            << endl;
    }

    cout << "Данные отсортированы и записаны в файл output.txt" << endl;

}
