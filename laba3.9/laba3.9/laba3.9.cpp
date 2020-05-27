#include <iostream>
#include<math.h>
using namespace std;
double fan(int n, int a)
{
	if (a == n)
		return pow(n, 1 / 2.);
	return pow(a + fan(n, a + 1), 1 / 2.);
}
int main()
{
	setlocale(LC_ALL, "ru");
	double n, x, a = 1;
	cout << "Введите n : ";
	cin >> n;
	cout << "Значение рекурсивной функции : " << fan(n, a) << endl;
	x = pow(n, 1 / 2.);
	a = n - 1;
	for (int i = 0; i < n - 1; i++)
	{
		x = pow(a + x, 1 / 2.);
		a--;
	}
	cout << "Значение обычной функции : " << x;
}