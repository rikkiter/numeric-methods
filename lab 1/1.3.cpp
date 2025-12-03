#include <iostream>
#include <cmath>
#include <string>
using namespace std;

double narrow_accuracy(string num) {
    int after_dot = 0;
    for(int i=0; i < num.length(); i++) {
        if(num[i] == '.') after_dot = num.length() - i;
    }
    return 5*pow(10, -after_dot);
}

double wide_accuracy(string num) {
        int after_dot = 0;
    for(int i=0; i < num.length(); i++) {
        if(num[i] == '.') after_dot = num.length() - i - 1;
    }
    return pow(10, -after_dot);
}

float absolute_accuracy(string num, bool is_nar) {
    double num_double = stod(num);
    if(is_nar) return narrow_accuracy(num);
    return wide_accuracy(num);
}

float relative_accuracy(string num, bool is_nar) {
    double num_double = stod(num);
    if(is_nar) return narrow_accuracy(num)/num_double;
    return wide_accuracy(num)/num_double;
}

int main() {
    string num;
    short mode;
    bool is_nar;
    while(true) {
        is_nar = false;
        cout << "Введите число " << endl;
        cin >> num;
        cout << "В узком смылсе - 1, в широком смысле - 0 " << endl;
        cin >> mode;
        if(mode == 1) is_nar = true;
        cout << "Абсолютная погрешность " << absolute_accuracy(num, is_nar) << endl;
        cout << "Относительная погрешность " << relative_accuracy(num, is_nar) << endl;
        cout << "Продолжить - 1, выйти - 0 " << endl;
        cin >> mode;
        if(mode == 0) break;
    }
}