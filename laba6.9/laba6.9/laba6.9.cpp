#include <iostream>
using namespace std;
struct set {
    int info;
    set* next, * prev;
}*head,*tail;
void end() {
    exit(0);
}
set* push_head(set* p, int x) {
    set* t = new set;
    if (head == NULL) {
        t->next = t->prev = NULL;
        t->info = x;
        head = tail = t;
    }
    else {
        t->prev = NULL;
        t->next = p;
        t->info = x;
        p->prev = t;
    }
    return t;
}
set* push_tail(set* p, int x) {
    set* t = new set;
    if (tail == NULL) {
        t->next = t->prev = NULL;
        t->info = x;
        head = tail = t;
    }
    else {
        t->next = NULL;
        t->prev = p;
        t->info = x;
        p->next = t;
    }
    return t;
}
void del(set* p, int* out) {
    set* MIN = NULL, * MAX = NULL, * t;
    int min = 100, max = 0, a = 0, a1, a2, z = 0;
    for (; p != NULL; p = p->next) {
        a++;
        if (min > p->info) {
            min = p->info;
            MIN = p;
            a1 = a;
        }
    }
    p = head;
    a = 0;
    for (p; p != NULL; p = p->next) {
        a++;
        if (max < p->info) {
            max = p->info;
            MAX = p;
            a2 = a;
        }
    }
    if (a1 > a2) {
        auto k = MIN;
        MIN = MAX;
        MAX = k;
    }
    p = MIN->next;
    while (p != MAX) {
        z++;
        t = p;
        p = p->next;
        MIN->next = p;
        p->prev = MIN;
        delete t;
    }
    *out = z;
}
void view_head(set* p) {
    while (p != NULL) {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;
}
void view_tail(set* p) {
    while (p != NULL) {
        cout << p->info << " ";
        p = p->prev;
    }
    cout << endl;
}
void logics() {
    char fun;
    cout << "Введите нужную букву : ";
    cin >> fun;
    int x, a;
    switch (fun) {
    case 'a':view_head(head); break;
    case 'b':view_tail(tail); break;
    case 'c':cout << "Введите число : "; cin >> x; head = push_head(head, x); break;
    case 'd':cout << "Введите число : "; cin >> x; tail = push_tail(tail, x); break;
    case 'e':del(head, &a); cout << endl << "Удалено " << a << " элеметов" << endl; break;
    case 'x':end();
    }
    logics();
}
int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Просмотр с начала : a\nПросмотр с конца : b\nДобавление в начало : c\nДобавление в конец : d\nУдаление элементов : e\nЗавершение работы : x\n";
    logics();
}