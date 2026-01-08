#include <iostream>
#include <cmath>
using namespace std;

struct Number {
    float number;
    float accuracy;
};

float expression_value(Number num1, Number num2, Number num3, Number num4) {
    return pow(num1.number - num2.number, 1.0/3)/num3.number/(num4.number - num1.number);
}

float relative_accuracy_value(Number num1, Number num2, Number num3, Number num4) {
    float number1 = num1.number - num2.number;
    float accuracy1 = num1.accuracy + num2.accuracy;
    float number2 = num4.number - num1.number;
    float accuracy2 = num4.accuracy + num1.accuracy;
    return (accuracy1/number1)/3 + accuracy2/number2 + num3.accuracy/num3.number;
}

float absolute_accuracy_value(Number num1, Number num2, Number num3, Number num4) {
    return expression_value(num1, num2, num3, num4) * relative_accuracy_value(num1, num2, num3, num4);
}

int main() {
    cout << "Решение для выражения типа √(c*d/b)" << endl;
    Number a = {10.82, 0.03}, b= {2.786, 0.0006}, m = {0.28, 0.006}, n = {14.7, 0.06};
    cout << "∛("<< a.number << "-" << b.number << ")/(" << m.number;
    cout << "*(" << n.number << "-" << a.number << "))=" << expression_value(a, b, m, n) << endl;
    cout << "Относительная погрешность:" << relative_accuracy_value(a, b, m, n) << endl;
    cout << "Абсолютная погрешность:" << absolute_accuracy_value(a, b, m, n) << endl;