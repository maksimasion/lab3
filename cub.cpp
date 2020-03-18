#include <iostream>
#include <fstream> 
#include <conio.h>
#include <cmath>
#include <cstring>
#include <string>

double *CubicInterpolation(double *src_x, double *src_y, double *new_x);
double *Jordan(double **a, double **b, int N);
using namespace std;
int GetI() {
fstream fin; 
string line_a; 
int i = 0;
fin.open("data_real.txt", ios::in); 
getline(fin, line_a);
while (!fin.eof()) {
    getline(fin, line_a);
    i++;
}
fin.close();
return i;
}
int k = GetI();
int N = k; // розбиение ф-ии
int K = 10; // дополнительное розбиение для "гладкости"
int main() {
    int a = 0;
    int b = k-1;
    double h;

    std::string path1 = "data_inter.txt";
    std::fstream pol;
    pol.open("data_real.txt", std::ios::in);
    string stroke;

    double *x = new double[N];
    double *y = new double[N];

    double *x1 = new double[(N - 1) * K + N];

    h = (b - a) / (double)(N - 1);

    for (int i = 0; i < N; i++)
    {
        getline(pol, stroke);
        x[i] = i;
        y[i] = stod(stroke);
    }
    pol.close();
    for (int i = 0; i < ((N - 1) * K + N); i++) {
        x1[i] = a + (i * h) / (K + 1);
    }

    std::ofstream outfile(path1);

    double *y1 = CubicInterpolation(x, y, x1);

    int k = 1;
    for (int i = 1; i < (N - 1) * K + N; i++) {
        if (i == k * (K + N)) {
            k++;
        }
        else {
            outfile << x1[i] << " " << y1[i] << "\n";
        }
    }

    outfile.close();

    _getch();

}

double *CubicInterpolation(double *src_x, double *src_y, double *new_x) { // src_x - начальные х, src_y - начальные у, new_x - новые х для нахождения у

    double *H = new double[N - 1];  
    double **gamma = new double*[1];
    *gamma = new double[N - 2];
    double **matrix = new double*[N - 2];
    double *c = new double[N - 2]; // кооф с
    double *d = new double[N - 1]; // кооф d
    double *b = new double[N - 1]; // кооф b
    double *new_y = new double[(N - 1) * K + N]; // массив с выходными значениями
    double *ci = new double[N - 1]; // массив для хранения 0 + все кооф с
    double *a = new double[N - 1]; // кооф а

    for (int i = 0; i < N - 2; i++) {
        matrix[i] = new double[N - 2];
    }

    for (int i = 0; i < N - 1; i++) // находим H
    {
        H[i] = src_x[i + 1] - src_x[i];
    }

    for (int i = 0; i < N - 2; i++)  // Находим гамму
    {
        gamma[0][i] = 3*((src_y[i + 2] - src_y[i + 1])/(H[i + 1]) - (src_y[i + 1] - src_y[i]) / (H[i]));
    }

    for (int i = 0; i < N - 2; i++) {
        for (int j = 0; j < N - 2; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < N - 2; i++) {   // строим матрицу из которой будем находить кооф с
        matrix[i][i] = 2 * (H[i] + H[i + 1]);
        if (i == 0) {
            matrix[i][i + 1] = H[i + 1];
        }
        else {
            if (i + 1 == N - 2) {
                matrix[i][i - 1] = H[i];
            }
            else {
                matrix[i][i + 1] = H[i + 1];
                matrix[i][i - 1] = H[i];
            }
        }
    }

    c = Jordan(matrix, gamma, N - 2); // Решаем матрицу методом Жордана и получаем наши кооф с

    for (int i = 0; i < N - 1; i++) { // переписываем кооф с в другой массив с добавлнием первого нулевого елемента
        if (i == 0) {
            ci[0] = 0;
        }
        else {
            ci[i] = c[i - 1];
        }
    }

for (int i = 0; i < N - 2; i++) {  // находим кооф d
    d[i] = ((ci[i + 1] - ci[i]) / (3.0 * H[i]));    
}
    d[N - 2] = (-1 * ci[N - 2]) / (3.0 * H[N - 2]);

for (int i = 0; i < N - 2; i++) { // находим кооф b
    b[i] = ((src_y[i + 1] - src_y[i]) / H[i]) - (((ci[i + 1] + 2 * ci[i] )/ 3.0))* H[i];   
}
    b[N - 2] = ((src_y[N - 1] - src_y[N - 2] ) / H[N - 2] ) - (2.0 / 3.0)*(ci[N - 2] * H[N - 2]);

    for (int i = 0; i < N - 1; i++) { // записываем знач а
        a[i] = src_y[i];
    }

    // ф-ия которая проводит интерполяцию, я считаю что проблема где-то в ней 
    for (int k = 0; k < N - 1; k++) {
        for (int i = 1 + k * (K + 1); i < K + 2 + k * (K + 1); i++) {
            new_y[i] = a[k] + (b[k] * (new_x[i] - src_x[k])) + (ci[k] * pow((new_x[i] - src_x[k]), 2)) + (d[k] * pow((new_x[i] - src_x[k]),3));
        }
    }
    int k = 0;
    for (int i = 0; i < ((K + 1) * N - 1); i += K + 1) {
        new_y[i] = src_y[k];
        k++;
    }

    return new_y;
}

double *Jordan(double **a, double **b, int N) {

    double *x = new double[N];

    float R;
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            if (i != k)
            {
                R = a[i][k] / a[k][k];
                for (int j = k; j < N; j++)
                {
                    a[i][j] -= a[k][j] * R;
                }
                b[0][i] -= b[0][k] * R;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        x[i] = b[0][i] / a[i][i];   
    }

    return x;
}