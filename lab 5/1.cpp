#include <iostream>
#include <cmath>
#include <random>
using namespace std;

double f1(double x) {
    return sqrt(0.6*x+1.7)/(2.1*x+sqrt(0.7*x*x+1));
}

double f2(double x) {
    return sin(1.5*x+0.3)/(2.3+cos(0.4*x*x+1));
}

double d_rand(double mi, double ma)
{
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_real_distribution<> dis(mi, ma);
    return dis(gen);
}

double mid_method(double(*func) (double), double x1, double x2, double ma, int n) {
    double h = (x2-x1)/n;
    double res=0;
    for(int i=0; i<n; i++) {
        res += h*func(x1+h/2+h*i);
    }
    return res;
}

double left_method(double(*func) (double), double x1, double x2, double ma, int n) {
    double h = (x2-x1)/n;
    double res=0;
    for(int i=0; i<n; i++) {
        res += h*func(x1+h*i);
    }
    return res;
}

double right_method(double(*func) (double), double x1, double x2, double ma, int n) {
    double h = (x2-x1)/n;
    double res=0;
    for(int i=1; i<=n; i++) {
        res += h*func(x1+h*i);
    }
    return res;
}

double monte_carlo_method(double(*func) (double), double x1, double x2, double ma, int n) {
    double base_square = abs(x2-x1)*ma;
    int inside_func_counter = 0;
    int counter = 0;
    for(int i=0; i<n; i++) {
        double x = d_rand(x1, x2);
        double y = d_rand(0, ma);
        double f = func(x);
        if(y<f) inside_func_counter++;
        counter++;
    }
    return (double)inside_func_counter/counter*base_square;

}

double accuracy_check(double(*func) (double),
                     double(*method) (double(*func) (double), double, double, double, int),
                     double x1, double x2, double ma) {
    double eps = 0.0001;
    int n = 10;
    float s1, s2;
    do {
        s1=method(func, x1, x2, ma, n);
        s2=method(func, x1, x2, ma, 2*n);
        n *= 2;
    } while (abs(s2-s1) > eps && abs(s2-s1)/(s1+s2)/2 > eps);
        return s2;
}

int main() {
    cout << accuracy_check(f1, mid_method, 1.2, 2, 0.395128) << endl;
    cout << accuracy_check(f1, left_method, 1.2, 2, 0.395128) << endl;
    cout << accuracy_check(f1, right_method, 1.2, 2, 0.395128) << endl;
    // cout << accuracy_check(f2, 0.4, 1.2); 
    //f1 max = 0.395128
    // for(int i=0; i<100; i++) cout << d_rand(1.2, 2) << endl;
    cout << accuracy_check(f1, monte_carlo_method, 1.2, 2, 0.395128); 
}
