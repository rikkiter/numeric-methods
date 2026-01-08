#include <iostream>
#include <cmath>
using namespace std;

float expression_value(float num1, float num2, float num3) {
    return sqrt(num1 * num2 / num3);
}

float relative_accuracy_value(
    float num1, float num2, float num3,
    float acr1, float acr2, float acr3) {
    return (acr1/num1 + acr2/num2 + acr3/num3)/2;
}

float absolute_accuracy_value(
    float num1, float num2, float num3,
    float acr1, float acr2, float acr3) {
    return expression_value(num1, num2, num3) 
    * relative_accuracy_value(num1, num2, num3,acr1, acr2, acr3);
}

int main() {
    cout << "Решение для выражения типа √(c*d/b)" << endl;
    float c=0.7568, d=21.7, b=2.65;
    float c_acr=0.0002, d_acr=0.02, b_acr=0.01;
    cout << "√("<< c << "*" << d << "/" << b << ")=" << expression_value(c, d, b) << endl;
    cout << "Относительная погрешность:" << relative_accuracy_value(c, d, b, c_acr, d_acr, b_acr) << endl;
    cout << "Абсолютная погрешность:" << absolute_accuracy_value(c, d, b, c_acr, d_acr, b_acr) << endl;
}