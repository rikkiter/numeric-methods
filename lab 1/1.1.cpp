#include <iostream>
#include <cmath>
using namespace std;

double compare_accuracy(double a_numerator, double a_denominator, double a, double b_radicand, double b) {
    if(abs(a_numerator/a_denominator - a)/a > abs(sqrt(b_radicand)-b)/b) return b;
    return a;
}

int main() {
    double a_numerator, a_denominator, a, b_radicand, b;
    cout << "Введите числитель дроби" << endl;
    cin >> a_numerator;
    cout << "Введите знаменатель дроби" << endl;
    cin >> a_denominator;
    cout << "Введите приблеженное значение дроби" << endl;
    cin >> a;
    cout << "Введите подкоренное выражение" << endl;
    cin >> b_radicand;
    cout << "Введите приблеженное значение корня" << endl;
    cin >> b;
    cout << "Точнее " << compare_accuracy(a_numerator, a_denominator, a, b_radicand, b) << endl;
}