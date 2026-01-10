#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iomanip>

using namespace std;

// Функция для округления до заданного количества знаков после запятой
double round_to(double value, int decimal_places) {
    if (decimal_places < 0) return value;
    
    double factor = pow(10, decimal_places);
    return round(value * factor) / factor;
}

// Функция для определения минимального количества знаков после запятой
int accuracy(const vector<string>& args) {
    int decimal_place = 0;
    bool first = true;
    
    for (const string& arg : args) {
        size_t dot_pos = arg.find('.');
        int current_decimal_place = 0;
        
        if (dot_pos != string::npos) {
            current_decimal_place = arg.length() - dot_pos - 1;
        }
        
        if (first) {
            decimal_place = current_decimal_place;
            first = false;
        } else if (decimal_place > current_decimal_place) {
            decimal_place = current_decimal_place;
        }
    }
    
    return decimal_place;
}

// Функция для преобразования строк в числа с округлением
vector<double> str_to_double_and_round(const vector<string>& args, int round_decimal_places) {
    vector<double> res;
    
    for (const string& arg : args) {
        double val = stod(arg);
        res.push_back(round_to(val, round_decimal_places));
    }
    
    return res;
}

// Функция для вычисления площади по формуле Герона с точным округлением
double compute_expression(const string& a_str, const string& b_str, const string& c_str) {
    vector<string> args = {a_str, b_str, c_str};
    
    // Определяем минимальное количество знаков после запятой
    int decimal_place = accuracy(args);
    
    // Округляем до одного знака больше, чем минимальный (как в Python)
    int intermediate_decimal_places = decimal_place + 1;
    
    // Преобразуем строки в числа и округляем
    vector<double> sides = str_to_double_and_round(args, intermediate_decimal_places);
    double a = sides[0];
    double b = sides[1];
    double c = sides[2];
    
    // Вычисляем полупериметр с промежуточным округлением
    double p = (a + b + c) / 2.0;
    p = round_to(p, intermediate_decimal_places);
    
    // Вычисляем произведение (p-a), (p-b), (p-c) с округлением каждого множителя
    double p_minus_a = round_to(p - a, intermediate_decimal_places);
    double p_minus_b = round_to(p - b, intermediate_decimal_places);
    double p_minus_c = round_to(p - c, intermediate_decimal_places);
    
    double product = p;
    product = round_to(product * p_minus_a, intermediate_decimal_places);
    product = round_to(product * p_minus_b, intermediate_decimal_places);
    product = round_to(product * p_minus_c, intermediate_decimal_places);
    
    // Проверяем, чтобы подкоренное выражение было неотрицательным
    if (product < 0) {
        // Для треугольника с заданными сторонами подкоренное выражение должно быть >= 0
        // Если оно отрицательное, значит стороны не образуют треугольник
        product = 0;
    }
    
    // Извлекаем корень и округляем до исходной точности
    double s = sqrt(product);
    s = round_to(s, decimal_place);
    
    return s;
}

double compute_expression_exact(const string& a_str, const string& b_str, const string& c_str) {
    vector<string> args = {a_str, b_str, c_str};
    
    // Определяем минимальное количество знаков после запятой
    int decimal_place = accuracy(args);
    
    // Округляем до одного знака больше, чем минимальный
    int intermediate_decimal_places = decimal_place + 1;
    
    // Преобразуем строки в числа и округляем
    vector<double> sides = str_to_double_and_round(args, intermediate_decimal_places);
    double a = sides[0];
    double b = sides[1];
    double c = sides[2];
    
    // Вычисляем полупериметр с округлением
    double p = (a + b + c) / 2.0;
    p = round_to(p, intermediate_decimal_places);
    
    double product = p * (p - a) * (p - b) * (p - c);
    
    if (product < 0) {
        product = 0;
    }
    
    double s = sqrt(product);
    s = round_to(s, decimal_place);
    
    return s;
}

int main() {
    while (true) {
        cout << "Вычисление площади по формуле Герона. Рекомендуемый формат чисел 0.0" << endl;
        
        string a_input, b_input, c_input;
        cout << "Введите значения для a: ";
        cin >> a_input;
        cout << "Введите значения для b: ";
        cin >> b_input;
        cout << "Введите значения для c: ";
        cin >> c_input;
        
        double s = compute_expression(a_input, b_input, c_input);
        
        // Определяем точность для вывода результата
        vector<string> args = {a_input, b_input, c_input};
        int decimal_place = accuracy(args);
        
        // Выводим результат с соответствующей точностью
        cout << fixed << setprecision(decimal_place) << "S = " << s << endl;
        
        cout << "Чтобы выйти отправьте 0, чтобы продолжить - любой символ: ";
        string choice;
        cin >> choice;
        
        if (choice == "0") {
            break;
        }
    }
    
    return 0;
}