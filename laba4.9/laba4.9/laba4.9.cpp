#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;
struct production
{
    string name;
    int x;
};
struct shop
{
    int n;
    production p[3];
}plant[100];
void sort(production* p, int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = i + 1; j < x; j++)
            if (p[i].x < p[j].x)
            {
                production z = p[i];
                p[i] = p[j];
                p[j] = z;
            }
    }
}
void Qsort(production* arr, int begin, int end)
{
    int i, j, x;
    i = begin;
    j = end;
    x = arr[(i + j) / 2].x;
    do
    {
        while (arr[i].x > x)i++;
        while (arr[j].x < x)j--;
        if (i <= j)
        {
            auto k = arr[i];
            arr[i] = arr[j];
            arr[j] = k;
            i++;
            j--;
        }
    } while (i <= j);
    if (begin < j)Qsort(arr, begin, j);
    if (end > i)Qsort(arr, i, end);
    /*Qsort(arr, 0, x - 1); - Обращение к этой функции */
}
int transfer(string str)
{
    int x, y = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        x = (int)str[i] - (int)'0';
        y = y * 10 + x;
    }
    return y;
}
void end(shop* plant, int q)
{
    ofstream file;
    file.open("file.txt");
    for (int i = 0; i < q; i++) {
        file << plant[i].n << endl;
        for (int j = 0; j < 3; j++) {
            file << plant[i].p[j].name << endl
                << plant[i].p[j].x << endl;
        }
    }
    file.close();
    exit(0);
}
void view(shop* plant, int q)
{
    cout << "Просмотреть весь список : a\nПросмотреть конкретный цех : b\n";
    char fan;
    cin >> fan;
    if (fan == 'a') {
        for (int i = 0; i < q; i++) {
            cout << "Номер цеха : " << plant[i].n << endl;
            sort(plant[i].p, 3);
            /*Qsort(plant[i].p, 0, q - 1);*/
            for (int j = 0; j < 3; j++) {
                cout << plant[i].p[j].name << " : "
                    << plant[i].p[j].x << endl;
            }
            cout << endl << "-----------------------" << endl << endl;
        }
    }
    if (fan == 'b') {
        int n;
        cout << "Введите номер интересующего цеха : ";
        cin >> n;
        for (int i = 0; i < q; i++) {
            if (plant[i].n == n) {
                cout << "Номер цеха : " << plant[i].n << endl;
                sort(plant[i].p, 3);
                /* Qsort(plant[i].p, 0, q - 1);*/
                for (int j = 0; j < 3; j++) {
                    cout << plant[i].p[j].name << " : "
                        << plant[i].p[j].x << endl;
                }
                break;
            }
        }
    }
}
int correction(shop* plant, int q)
{
    cout << "Добавить цех : a\nУдалить цех : b\n";
    char fan;
    cin >> fan;
    if (fan == 'a')
    {
        cout << "Номер цеха : ";
        cin >> plant[q].n;
        for (int i = 0; i < 3; i++) {
            cout << "Продукция номер " << i + 1 << " : ";
            SetConsoleCP(1251);
            cin.ignore();
            getline(cin, plant[q].p[i].name);
            SetConsoleCP(866);
            cout << "Количество : ";
            cin >> plant[q].p[i].x;
        }
        q++;
    }
    if (fan == 'b')
    {
        int n, k = 100;
        cout << "Введите номер цеха, который хотите удалить : ";
        cin >> n;
        for (int i = 0; i < q; i++) {
            if (plant[i].n == n) {
                k = i; break;
            }
        }
        for (int i = k; i < q; i++)
            plant[i] = plant[i + 1];
        q--;
    }
    return q;
}
char Function() {
    char fun;
    cout << "Просмотреть файл : a\nОткорректировать файл : b\nЗавешить работу : c\n";
    cout << "--------------------------" << endl;
    cin >> fun;
    return fun;
}
void logics(shop* plant, int q)
{
    while (true) {
        switch (Function()) {
        case 'a':view(plant, q); break;
        case 'b':q = correction(plant, q); break;
        case 'c':end(plant, q);
        default:cout << "Некоректный ввод данных, повторите попытку: ";
        }puts("\nНажмите любую клавишу чтобы продолжить...");
        _getch(); system("cls");
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    ifstream file;
    string str;
    int q = 0;
    file.open("file.txt");
    for (int i = 0; i < 100 && !file.eof(); i++)
    {
        getline(file, str);
        plant[i].n = transfer(str);
        for (int j = 0; j < 3; j++) {
            SetConsoleCP(1251);
            getline(file, str);
            plant[i].p[j].name = str;
            SetConsoleCP(866);
            getline(file, str);
            plant[i].p[j].x = transfer(str);
        }
        if (plant[i].n != 0)
            q++;
    }
    file.close();
    logics(plant, q);
}