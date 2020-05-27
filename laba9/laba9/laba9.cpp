#include <math.h>
#include <iostream>
using namespace std;
double f(double x) {
    return pow(x, 3) + 10 * pow(x, 2) - 50;
}
double vegstain(double x1, double x2) {
    double y1, y2, x3, eps = 0.00000000001;
    y1 = f(x1); y2 = f(x2);
    do {
        x3 = x2 - y2 * (x2 - x1) / (y2 - y1);
        x1 = x2;
        x2 = x3;
        y1 = y2;
        y2 = f(x3);
    } while (fabs(x1 - x2) > eps);
    return x3;
}
int main()
{
    setlocale(LC_ALL, "ru");
    double a = -12, b = 5,c;
    for (double x = a; x < b; x++) {
        if (f(x) * f(x + 1) < 0) {
            cout << "Значение корня :\n";
            c = vegstain(x, x + 1);
            cout << c << endl;
            cout << "Значение функции :\n";
            cout << f(c)<<endl;
        }
    }
    
}
