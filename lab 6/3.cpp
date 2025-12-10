#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

const int N = 4;

void print_matrix(double (*a)[N], int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(a[i][j] >= 0) cout << " " << a[i][j] << " ";
            else cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void single_division(double (*a)[N], double (*b)[N], int size) {
    double temp[N][N];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++) {
            temp[i][j] = a[i][j];
            b[i][j] = (i==j);
        }
    
    for(int i=0; i<size; i++) {
        double x = temp[i][i];
        for(int j=i+1; j<size; j++) {
            double y = temp[j][i];
            double d = y/x;
            for(int k=0; k<size; k++) {
                temp[j][k] -= temp[i][k]*d;
                b[j][k] -= b[i][k]*d;
            }
        }
        for(int j=0; j<size; j++) {
            temp[i][j] /= x;
            b[i][j] /= x;
        }
    }

    
    for(int i=size-1; i>=0; i--) {
        double x = temp[i][i];
        for(int j=i-1; j>=0; j--) {
            double y = temp[j][i];
            double d = y/x;
            for(int k=size-1; k>=0; k--) {
                temp[j][k] -= temp[i][k]*d;
                b[j][k] -= b[i][k]*d;
            }
        }
    }
    print_matrix(b, size);
    cout << endl;
    print_matrix(temp, size);
    cout << endl;
}

int main() {
    double a[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double b[4][4];
    double res[4];
    cout << fixed << setprecision(2);
    cout << "Решение Методом Гаусса: " << endl;
    single_division(a, b, 4);
}