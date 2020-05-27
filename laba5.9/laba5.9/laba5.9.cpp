#include <iostream>
#include <ctime>
using namespace std;
struct set {
    int info;
    set* next;
}*head;
set* push(set* p, int a) {
    set* t = new set;
    t->info = a;
    t->next = p;
    return t;
}
void fun(set* p, int* out) {
    set* MIN = NULL, * MAX = NULL, * t;
    int min = 100, max = 0, a = 0, a1, a2, z=0;
    for (; p!=NULL; p = p->next) {
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
        delete t;
    }
    *out = z;
}
void view(set* p) {
    while (p != NULL) {
        cout << p->info << " ";
        p = p->next;
    }
}
int main(){
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int a, x;
    cout << "Введете количество элементов в стеке : ";
    cin >> x;
    for (int i = 0; i < x; i++) {
        a = rand()%51;
        head = push(head, a);
    }
    view(head);
    fun(head,&a);
    cout << endl << "Удалено " << a << " элеметов" << endl;
    view(head);
}