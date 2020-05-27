#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;
struct student
{
    string fio = "";
    int m = 0, n = 0, a = 0, b = 0, c = 0, d = 0;
    double srball = 0;
}humen[100];
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
void end(int p)
{
    ofstream file;
    file.open("file.txt");
    for (int i = 0; i < p; i++) {
        file << humen[i].fio << endl
            << humen[i].m << endl
            << humen[i].n << endl
            << humen[i].a << endl
            << humen[i].b << endl
            << humen[i].c << endl
            << humen[i].d << endl;
    }
    file.close();
    exit(0);
}
void view(int p)
{
    for (int i = 0; i < p; i++) {
        cout << "Студент : " << humen[i].fio << endl
            << "Номер группы : " << humen[i].m << endl
            << "Год рождения : " << humen[i].n << endl
            << "Математика : " << humen[i].a << endl
            << "Физика : " << humen[i].b << endl
            << "Информатика : " << humen[i].c << endl
            << "Химия : " << humen[i].d << endl
            << "Средний балл : " << humen[i].srball << endl
            << endl << "----------------------" << endl << endl;
    }
}
int correction(int p)
{
    cout << "Добавить студента : a\nУдалить студента : b\n";
    char fan;
    cin >> fan;
    if (fan == 'a') {
        cout << "ФИО : ";
        SetConsoleCP(1251);
        cin.ignore();
        getline(cin, humen[p].fio);
        SetConsoleCP(866);
        cout << "Номер группы : ";
        cin >> humen[p].m;
        cout << "Год рождения : ";
        cin >> humen[p].n;
        cout << "Оценка по математике : ";
        cin >> humen[p].a;
        cout << "Оценка по физике : ";
        cin >> humen[p].b;
        cout << "Оценка по информатике : ";
        cin >> humen[p].c;
        cout << "Оценка по химии : ";
        cin >> humen[p].d;
        humen[p].srball = (humen[p].a + humen[p].b + humen[p].c + humen[p].d) / 4.;
        p++;
    }
    if (fan == 'b') {
        string name;
        int k = 100;
        cout << "Введите имя человека которого хотите удалить : ";
        SetConsoleCP(1251);
        cin.ignore();
        getline(cin, name);
        SetConsoleCP(866);
        for (int i = 0; i < p; i++) {
            if (humen[i].fio == name) {
                k = i; break;
            }
        }
        for (int i = k; i < p - 1; i++)
            humen[i] = humen[i + 1];
        p--;
    }
    return p;
}
void Rating(int p)
{
    int group;
    double x = 0;
    cout << "Введите номер интересующей группы : ";
    cin >> group;
    for (int i = 0; i < p; i++) {
        x += humen[i].srball;
    }
    x = x / p;
    cout << "Общий средний балл : " << x << endl;
    for (int i = 0; i < p; i++) {
        if (humen[i].srball >= x && humen[i].m == group) {
            cout << "Студент : " << humen[i].fio << endl
                << "Номер группы : " << humen[i].m << endl
                << "Год рождения : " << humen[i].n << endl
                << "Математика : " << humen[i].a << endl
                << "Физика : " << humen[i].b << endl
                << "Информатика : " << humen[i].c << endl
                << "Химия : " << humen[i].d << endl
                << "Средний балл : " << humen[i].srball << endl
                << endl << "----------------------" << endl << endl;
        }
    }
}
char Function() {
    char fun;
    cout << "Просмотреть файл : a\nОтредактировать файл : b\nСоставить рейтинг : c\nЗавешить работу : x\n";
    cout << "--------------------------" << endl;
    cin >> fun;
    return fun;
}
void logics(int p)
{
    while (true) {
        switch (Function())
        {
        case 'a':view(p); break;
        case 'b':p = correction(p); break;
        case 'c':Rating(p); break;
        case 'x':end(p);
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
    int p = 0;
    file.open("file.txt");
    for (int i = 0; i < 100 && !file.eof(); i++)
    {
        SetConsoleCP(1251);
        getline(file, str);
        humen[i].fio = str;
        SetConsoleCP(866);
        getline(file, str);
        humen[i].m = transfer(str);
        getline(file, str);
        humen[i].n = transfer(str);
        getline(file, str);
        humen[i].a = transfer(str);
        getline(file, str);
        humen[i].b = transfer(str);
        getline(file, str);
        humen[i].c = transfer(str);
        getline(file, str);
        humen[i].d = transfer(str);
        humen[i].srball = (humen[i].a + humen[i].b + humen[i].c + humen[i].d) / 4.;
        if (humen[i].fio != "")
            p++;
    }
    file.close();
    logics(p);
}