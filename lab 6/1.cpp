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

double lower_triangle_method(double (*a)[N], int size) {
    double temp[N][N];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            temp[i][j] = a[i][j];
    for(int i=0; i<size; i++) {
        double x = temp[i][i];
        for(int j=i+1; j<size; j++) {
            double y = temp[j][i];
            double d = y/x;
            for(int k=i; k<size; k++) {
                temp[j][k] -= temp[i][k]*d;
            }
        }
    }

    // print_matrix(temp, size);
    // cout << endl;

    double ans = 1;
    for(int i=0; i<size; i++) {
        ans *= temp[i][i];
    }
    return ans;
}

double diagonal_method(double (*a)[N], int size) {
    double temp[N][N];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            temp[i][j] = a[i][j];
    
    for(int i=0; i<size; i++) {
        double x = temp[i][i];
        for(int j=i+1; j<size; j++) {
            double y = temp[j][i];
            double d = y/x;
            for(int k=i; k<size; k++) {
                temp[j][k] -= temp[i][k]*d;
            }
        }
    }

    for(int i=size-1; i>=0; i--) {
        double x = temp[i][i];
        for(int j=i-1; j>=0; j--) {
            double y = temp[j][i];
            double d = y/x;
            for(int k=i; k>=0; k--) {
                temp[j][k] -= temp[i][k]*d;
            }
        }
    }

    // print_matrix(temp, size);
    // cout << endl;


    double ans = 1;
    for(int i=0; i<size; i++) {
        ans *= temp[i][i];
    }

    return ans;
}

double comp_kramer_opred(double (*a)[N], double (*b), int iter, int size) {
    double temp[N][N];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            temp[i][j] = a[i][j];
    for(int i=0; i<size; i++) 
        temp[i][iter] = b[i];
    return lower_triangle_method(temp, size);
}

void kramer_method(double (*a)[N], double (*b), double (*ans), int size) {
    double A = lower_triangle_method(a, size);
    if(!A) {
        cout << "Решение не может быть найдено. Главный определитель равен нулю" << endl;
        return;
    }
    for(int i=0; i<size; i++) {
        ans[i] = comp_kramer_opred(a, b, i, size)/A;
    }

    cout << "Решение СЛАУ:" << endl;
    for(int i=0; i<size; i++) {
        cout << 'x' << i+1 << '=' << ans[i] << " ";
    }
}

double comp_minor(double (*a)[N], int m_i, int m_j, int size) {
    double temp[N][N];
    int local_i=0, local_j=0;
    for(int i=0; i<size; i++) {
        if(i==m_i) continue;
        local_j = 0;
        for(int j=0; j<size; j++) {
            if(j==m_j) continue;
            temp[local_i][local_j] = a[i][j];
            local_j++;
        }
        local_i++;
    }
    return lower_triangle_method(temp, size-1);
}

void back_matrix(double (*a)[N], double (*res)[N], int size) {
    double A = lower_triangle_method(a, size);
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            res[j][i] = (1/A)*pow(-1, i+j)*comp_minor(a, i, j, size);
}

void back_matrix_method(double (*a)[N], double (*b), double (*ans), int size) {
    double this_back_matrix[N][N];
    back_matrix(a, this_back_matrix, size);
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            ans[i] += this_back_matrix[i][j]*b[j];

    cout << "Решение СЛАУ:" << endl;
    for(int i=0; i<size; i++) {
        cout << 'x' << i+1 << '=' << ans[i] << " ";
    }
}

int main() {
    double a[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double b[4] {6, 8, 4, -8};
    double res[4];
    cout << fixed << setprecision(2);
    back_matrix_method(a, b, res, 4);
    cout << endl;
    kramer_method(a, b, res, 4);
    // kramer_method(a, b, ans, 4);
}

/*
int main() {
    double a[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double b[4] {6, 8, 4, -8};
    double res[4][4];
    double ans[4];
    cout << fixed << setprecision(2);
    back_matrix(a, res, 4);
    print_matrix(res, 4);
    // kramer_method(a, b, ans, 4);
}
*/

/*
int main() {
    double a1[4][4] {{1, 2, -1, 1}, {2, 1, 1, 1}, {1, -1, 2, 1}, {1, 1, -1, 3}};
    double a3[4][4] {{1, 2, 3, -2}, {1, -1, -2, -3}, {3, 2, -1, 2}, {2, -3, 2, 1}};
    double b[4] {6, 8, 4, -8};
    cout << fixed << setprecision(2);
    print_matrix(a3, 4);
    cout << endl;
    cout << diagonal_method(a3, 4) << endl;
    cout << endl;
    print_matrix(a3, 4);
}
*/

/*
int main() {

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
*/