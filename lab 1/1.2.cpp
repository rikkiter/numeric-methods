#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Имеется баг когда число дробная часть числа начинается на 0...

class Number {
public:
    int integer_part;
    int fractional_part;
    // int zeros_quantity_in_fp = 0;

    Number(string num) {
        bool dot = true;
        string integer_part_s;
        string fractional_part_s;
        for(int i=0; i<num.size(); i++) {
            if(num[i] == '.') dot = false;
            else if(dot) integer_part_s.push_back(num[i]);
            else fractional_part_s.push_back(num[i]);
        }
        // for(int i=0; i<fractional_part_s.size(); i++) {
        //     if(fractional_part_s[i] != '0') break;
        //     zeros_quantity_in_fp++;
        // }
        integer_part = stoi(integer_part_s);
        fractional_part = stoi(fractional_part_s);
    }

    void num_round(int n) {
        float new_fractional = fractional_part;

        if(n==0) {
            while(new_fractional > 1) new_fractional /= 10;
            integer_part = (int) round(integer_part + new_fractional);
            fractional_part = 0;
            return;
        }

        float round_pattern = pow(10, n);
        cout << round_pattern << endl;
        while(new_fractional > round_pattern) new_fractional /= 10;
        cout << new_fractional << endl;
        fractional_part = (int) round(new_fractional);
        
    }

    string toString() {
        // if(fractional_part==0) return to_string(integer_part);
        // string zeros(zeros_quantity_in_fp, '0');
        return to_string(integer_part) + "." + to_string(fractional_part);
    }

    float toFloat() {
        return stof(toString());
    }

};

Number round_number(Number num, float absolute_accurancy, bool is_nar) {

}

int main() {
    Number num("123.005");
    cout << num.toString() << endl;
    cout << num.toFloat() << endl;
    num.num_round(1);
    cout << num.toString() << endl;
    cout << num.toFloat() << endl;

}