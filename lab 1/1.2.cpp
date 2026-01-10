#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

// Функция для получения шага округления
double get_round_pattern(double absolute_accuracy, bool is_nar) {
    // Преобразуем абсолютную погрешность в строку для анализа
    stringstream ss;
    ss << fixed << setprecision(15) << absolute_accuracy;
    string acc_str = ss.str();
    
    // Если есть точка в числе
    size_t dot_pos = acc_str.find('.');
    if (dot_pos != string::npos) {
        // Получаем дробную часть
        string fractional = acc_str.substr(dot_pos + 1);
        
        int place = 0;
        for (size_t i = 0; i < fractional.length(); i++) {
            int num = fractional[i] - '0';
            if (num != 0) {
                if (is_nar) {
                    if (num < 5) {
                        place = i + 1;
                    } else {
                        place = i - 1;
                    }
                } else {
                    place = i;
                }
                break;
            }
        }
        return pow(10.0, -place);
    }
    return 10.0;
}

// Функция для обновления шага округления
double update_round_pattern(double round_pattern) {
    stringstream ss;
    ss << fixed << setprecision(15) << round_pattern;
    string pattern_str = ss.str();
    
    // Убираем лишние нули в конце
    size_t dot_pos = pattern_str.find('.');
    if (dot_pos != string::npos) {
        while (pattern_str.back() == '0' && pattern_str.length() > dot_pos + 2) {
            pattern_str.pop_back();
        }
    }
    
    if (pattern_str.length() <= 3) {
        return 1.0;
    }
    
    // Преобразуем для изменения шага
    double new_pattern = round_pattern / 10;
    return new_pattern;
}

// Функция для округления числа
double round_num(double num, double absolute_accuracy = -1.0, double relative_accuracy = -1.0, bool is_nar = true) {
    // Если задана относительная погрешность, вычисляем абсолютную
    if (absolute_accuracy < 0 && relative_accuracy >= 0) {
        absolute_accuracy = relative_accuracy * num;
    } else if (absolute_accuracy < 0) {
        return num; // Без точности возвращаем исходное число
    }
    
    double round_pattern = get_round_pattern(absolute_accuracy, is_nar);
    
    while (true) {
        // Округляем до заданного шага
        double new_num = round(num / round_pattern) * round_pattern;
        
        double new_absolute_accuracy = absolute_accuracy + abs(new_num - num);
        
        if (is_nar) {
            if (new_absolute_accuracy < round_pattern / 2.0) {
                return new_num;
            }
        } else {
            if (new_absolute_accuracy < round_pattern) {
                return new_num;
            }
        }
        
        round_pattern = update_round_pattern(round_pattern);
        
        // Защита от бесконечного цикла
        if (round_pattern <= 0.0000000001) {
            return new_num;
        }
    }
}

int main() {
    double num1, num2;
    double relative_acc1, absolute_acc2;
    
    cout << "Введите число в формате 0.0: ";
    cin >> num1;
    cout << "Введите относительную погрешность в процентах: ";
    cin >> relative_acc1;
    relative_acc1 /= 100.0;
    
    cout << "Ответ: " << fixed << setprecision(10) 
              << round_num(num1, -1.0, relative_acc1, true) << endl;
    
    cout << "Введите число в формате 0.0: ";
    cin >> num2;
    cout << "Введите абсолютную погрешность в формате 0.0: ";
    cin >> absolute_acc2;
    
    cout << "Ответ: " << fixed << setprecision(10) 
              << round_num(num2, absolute_acc2, -1.0, false) << endl;
    
    return 0;
}