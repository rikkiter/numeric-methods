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

void gauss_method(double (*a)[N], double (*b), double (*ans), int size)
{
    double delitel;
    double mnogitel;
    double temp_a[N][N];

    for(int i=0; i<size; i++) {
        ans[i] = b[i];
        for(int j=0; j<size; j++)
            temp_a[i][j] = a[i][j];
    }

    for(int i = 0; i < size; i++)
    {
        delitel = temp_a[i][i];
        ans[i] /= delitel;
        for(int t = 0; t < size; t++)
        {
            temp_a[i][t] /= delitel;
        }
        for(int k=i+1; k < size; k++)
        {
            mnogitel = temp_a[k][i];
            ans[k] -= ans[i]*mnogitel;
            for(int j=i; j < size; j++)
            {
                temp_a[k][j] -=  temp_a[i][j]*mnogitel;
            }
        }
    }

    // print_matrix(temp_a, 4);
    // cout << endl;

    for(int i=size-1; i>=0; i--) {
        for(int j=size-1; j>i; j--) {
            ans[i] -= temp_a[i][j]*ans[j];
        }
    }

    cout << "Решение СЛАУ:" << endl;
    for(int i=0; i<size; i++) {
        cout << 'x' << i+1 << '=' << ans[i] << " ";
    }
}

/*
int main() {
    double a[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double b[4] {6, 8, 4, -8};
    double res[4];
    cout << fixed << setprecision(2);
    cout << "Решение Методом Гаусса: " << endl;
    gauss_method(a, b, res, 4);
}
*/
int main() {

    double a[N][N];
    double b[N];
    double res[N];
    int n;
    do {
        cout << "Введите размерность матрицы" << endl;
        cin >> n;

        if(cin.fail()) {
            cout << "Введен неправильный тип данных! Ожидалось целое число." << endl;
            cout << "Чтобы ввести заново нажмите Enter" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while(cin.fail());

    for(int i=0; i<n; i++) {
        cout << "Введите значения " << i+1  << " строки через пробел"<< endl;
        for(int j=0; j<n; j++) {
            cin >> a[i][j];
            if(cin.fail()) {
                cout << "Введен неправильный тип данных! Ожидалось число." << endl;
                cout << "Чтобы ввести заново нажмите Enter" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i--;
                
                break;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
    }
    for(int i=0; i<1; i++) {
    cout << "Введите значения столбца свободных членов через пробел" << endl;
        for(int j=0; j<n; j++) {
            cin >> b[j];
            if(cin.fail()) {
                cout << "Введен неправильный тип данных! Ожидалось число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i--;
                break;
            }
        }
    }
    cout << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(a[i][j] >= 0) cout << " " << a[i][j] << " ";
            else  cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << fixed << setprecision(3);
    cout << endl << "Решение методом Гаусса:" << endl;
    gauss_method(a, b, res, 4);
} 
