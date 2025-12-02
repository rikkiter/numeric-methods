#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

const int N = 100;

double lower_triangle_method(double (*a)[N], int size) {
    for(int i=0; i<size; i++) {
        double x = a[i][i];
        for(int j=i+1; j<size; j++) {
            double y = a[j][i];
            double d = y/x;
            for(int k=i; k<size; k++) {
                a[j][k] -= a[i][k]*d;
            }
        }
    }
    double ans = 1;
    for(int i=0; i<size; i++) {
        ans *= a[i][i];
    }
    return ans;
}

double diagonal_method(double (*a)[N], int size) {
    lower_triangle_method(a, size);
    for(int i=size-1; i>=0; i--) {
        double x = a[i][i];
        for(int j=i-1; j>=0; j--) {
            double y = a[j][i];
            double d = y/x;
            for(int k=i; k>=0; k--) {
                a[j][k] -= a[i][k]*d;
            }
        }
    }
    double ans = 1;
    for(int i=0; i<size; i++) {
        ans *= a[i][i];
    }
    return ans;

}


int main() {
    double a1[4][4] {{1, 2, -1, 1}, {2, 1, 1, 1}, {1, -1, 2, 1}, {1, 1, -1, 3}};
    double a3[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double a[N][N];
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
                cout << "Введен неправильный тип данных! Ожидалось целое число." << endl;
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
    cout << n << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(a[i][j] >= 0) cout << " " << a[i][j] << " ";
            else  cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << diagonal_method(a, n) << endl;
    cout << fixed << setprecision(2);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(a[i][j] >= 0) cout << " " << a[i][j] << " ";
            else  cout << a[i][j] << " ";
        }
        cout << endl;
    }
    
} 