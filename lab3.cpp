#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double l(int index, double X[12], double x);
double GetValue(double X[12], double Y[12], double x);
void read_record() 
{ 
    fstream fin; 
    ofstream fout;
    vector<string> row; 
    string line, line_a, word, temp; 
    int i = 0;
    fin.open("lol.csv", ios::in); 
    getline(fin, line_a);
    while (!fin.eof()) {
    getline(fin, line_a);
    i++;
    }
    fin.close();
    fin.open("lol.csv", ios::in); 
    fout.open("lol.txt");
    int roll2, count = 0; 
    getline(fin, line); 
    string matrix[i][14];
    for(int k = 0; k < i-1; k++) { 
        row.clear(); 
        getline(fin, line); 
        stringstream s(line); 
        while (getline(s, word, ',')) { 
            row.push_back(word); 
        } 
        roll2 = stoi(row[0]); 
            count = 1; 
            fout << "Year: " << row[0] << "\n"; 
            fout << "Jenuary: " << row[1] << "\n"; 
            fout << "February: " << row[2] << "\n"; 
            fout << "Marth: " << row[3] << "\n"; 
            fout << "April: " << row[4] << "\n"; 
            fout << "May: " << row[5] << "\n";
			fout << "June: " << row[6] << "\n";
			fout << "Jule: " << row[7] << "\n";
			fout << "August: " << row[8] << "\n";
			fout << "September: " << row[9] << "\n";
			fout << "October: " << row[10] << "\n";
			fout << "November: " << row[11] << "\n";
			fout << "December: " << row[12] << "\n";
			fout << "Middle: " << row[13] << "\n\n";

            matrix[k][0] = row[0];
            matrix[k][1] = row[1];
            matrix[k][2] = row[2];
            matrix[k][3] = row[3];
            matrix[k][4] = row[4];
            matrix[k][5] = row[5];
            matrix[k][6] = row[6];
            matrix[k][7] = row[7];
            matrix[k][8] = row[8];
            matrix[k][9] = row[9];
            matrix[k][10] = row[10];
            matrix[k][11] = row[11];
            matrix[k][12] = row[12];
            matrix[k][13] = row[13];
    } 
    if (count == 0) {
        cout << "Record not found\n"; 
    }
cout << "Enter start point of interval: ";
int point1, point;
cin >> point1;
point = point1 - 1875;
if(point+12 < i) {
cout << "Selected interval [" << point << "; " << point+12 << "]." << endl;
system("pause");
} else {
    cout << "ERR: Incorect interval (exit code)";
    system("exit");
}

double X[12];
double Y[12];
// Создаём файлы для графика
ofstream data_real;
ofstream data_inter;
data_real.open("data_real.txt");
data_inter.open("data_inter.txt");

for(int m = 0; m<=11; m++) {
    X[m] = m;
}
for(int m = point; m<point+12; m++) {
    Y[m-point] = stod(matrix[m][1]);
    cout << matrix[m][0] << endl;
    if(Y[m-point] != 999.9) {
    data_real << m-point << " " << Y[m-point] << endl;
    }
}
double x;
for(double m = 0; m<=11; m+=0.1) {
// Пропуск неизвестных данных НАЧ
if(m + 0.01 > int(m+0.1) && m - 0.01 < int(m+0.1)) {
    if(Y[int(m+0.1)] > 999) {} else {
        double y = GetValue(X, Y, m);
        //cout << "Y = " << y << "; X = " << m << " " << int(m+0.1) << endl; 
        data_inter << m << " " << y << endl; 
    }
} else {
// КОН
// Вывод НАЧ
double y = GetValue(X, Y, m);
//cout << "Y = " << y << "; X = " << m << " " << int(m+0.1) << endl;
data_inter << m << " " << y << endl; 
// КОН  
}
}
data_real.close();
data_inter.close();
system("python data.py");
fout.close();
// Вторая интерполяционная формула Ньютона
system("cls");
cout << "Enter start point of interval: ";
cin >> point1;
point = point1 - 1875;
if(point+12 > i) {
    cout << "ERR: Incorrect interval (exit code)";
    system("exit");
}
cout << "Selected interval [" << point << "; " << point+6 << "]." << endl;
system("pause");
double X_1[6];
double Y_1[6];
for(int z = 0; z<6; z++) {
X_1[z] = z;
}
fout.open("args.txt");
for(int z = point; z<point+6; z++) {
    Y_1[z-point] = stod(matrix[z][1]);   
    if(Y_1[z-point] < 998) {
    fout << Y_1[z-point] << endl;
    cout << matrix[z+1][0] << endl;
    }
}
fout.close();
system("newton1.exe");
system("python data.py");
// Первая интерполяционная формула Ньютона
point = point + 6;
cout << "Selected interval [" << point << "; " << point+6 << "]." << endl;
system("pause");
double X_2[6];
double Y_2[6];
for(int z = 0; z<6; z++) {
X_1[z] = z;
}
fout.open("args.txt");
for(int z = point; z<point+6; z++) {
    Y_1[z-point] = stod(matrix[z][1]);   
    if(Y_1[z-point] < 998) {
    fout << Y_1[z-point] << endl;
    cout << matrix[z+1][0] << endl;
    }
}
fout.close();
system("newton.exe");
system("python data.py");
// Интерполяция полиномом
point = point + 6;
i = i-1;
cout << "Selected interval [" << 1 << "; " << i << "]." << endl;
system("pause");
double X_3[i];
double Y_3[i];
fout.open("data_real.txt");
for(int z = 0; z<i; z++) {
    X_3[z] = stod(matrix[z][0]);
    Y_3[z] = stod(matrix[z][1]);   
    if(Y_3[z] < 998) {
    fout << z << " " << Y_3[z] << endl;
    }
}
fout.close();
system("polinom.o");
fout.open("data_real.txt");
for(int z = 0; z<i; z++) {
    X_3[z] = stod(matrix[z][0]);
    Y_3[z] = stod(matrix[z][1]);   
    if(Y_3[z] < 998) {
    fout << z+1875 << " " << Y_3[z] << endl;
    }
}
fout.close();
fstream pol;
pol.open("polinom.txt", ios::in);
double a[6];
string stroke;
for(int nm = 0; nm <= 5; nm++) {
    getline(pol, stroke);
    a[nm] = stod(stroke);
}
pol.close();
system("pause");
for(int nm = 0; nm <= 5; nm++) {
    cout << a[nm] << endl;
}
fout.open("data_inter.txt");
for(double x = 0; x<i; x=x+0.1) {
    fout << x+1875 << " " << a[0]+a[1]*x+a[2]*x*x+a[3]*x*x*x+a[4]*x*x*x*x+a[5]*x*x*x*x*x -7 << endl;
}
fout.close();
system("python data.py");
system("exit");

//Кубический сплайн
system("pause");
system("cls");
cout << "Enter start point of interval: ";
cin >> point;
point -= 1875;
if (point + 12 > i) {
	cout << "ERR: Incorrect interval (exit code)" << endl;
	system("exit");
}
cout << "Selected interval [" << point + 1875 << "; " << point + 12 + 1875 << "]." << endl;
system("pause");
fout.open("data_real.txt");
for (int z = point; z < point + 12; z++) {
	X_3[z - point] = stod(matrix[z][0]);
	Y_3[z - point] = stod(matrix[z][1]);
	if (Y_3[z - point] < 998) {
		fout << Y_3[z - point] << endl;
	}
}
fout.close();
system("cub.o");
fout.open("data_real.txt");
for (int z = point; z < point + 12; z++) {
	X_3[z - point] = stod(matrix[z][0]);
	Y_3[z - point] = stod(matrix[z][1]);
	if (Y_3[z - point] < 998) {
		fout << z - point << " " << Y_3[z - point] << endl;
		cout << matrix[z][0] << endl;
	}
}
fout.close();
system("pause");
system("python data.py");
}

int main (){
    
read_record();
return 0;
}

double l(int index, double X[12], double x) {
    double l = 1;
    for (int i = 0; i < 12; i++) {
        if(i != index) {
            l *= (x-X[i])/(X[index] - X[i]);
        }
    }
    return l;
}

double GetValue(double X[12], double Y[12], double x) {
    double y = 0;
    for (int i = 0; i < 12; i++) {
        if(Y[i] == 999.9) {
        } else {
        y += Y[i]*l(i, X, x);
        }
    }

    return y;
}