#include <stdio.h>
#include <process.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
float *a, *b, *x, *y, **sums;
int N, K;
//N - number of data points
//K - polinom power
//K<=N
char filename[256];
FILE* InFile=NULL;
void count_num_lines(){
   //count number of lines in input file - number of equations
   int nelf=0;       //non empty line flag
   do{
       nelf = 0;
       while(fgetc(InFile)!='\n' && !feof(InFile)) nelf=1;
       if(nelf) N++;
   }while(!feof(InFile));
}

void freematrix(){
   //free memory for matrixes
   int i;
   for(i=0; i<K+1; i++){
       delete [] sums[i];
   }
   delete [] a;
   delete [] b;
   delete [] x;
   delete [] y;
   delete [] sums;
}

void allocmatrix(){
   //allocate memory for matrixes
   int i,j,k;
   a = new float[K+1];
   b = new float[K+1];
   x = new float[N];
   y = new float[N];
   sums = new float*[K+1];
   if(x==NULL || y==NULL || a==NULL || sums==NULL){
       printf("\nNot enough memory to allocate. N=%d, K=%d\n", N, K);
       exit(-1);
   }
   for(i=0; i<K+1; i++){
       sums[i] = new float[K+1];
       if(sums[i]==NULL){
	   printf("\nNot enough memory to allocate for %d equations.\n", K+1);
       }
   }
   for(i=0; i<K+1; i++){
       a[i]=0;
       b[i]=0;
       for(j=0; j<K+1; j++){
	   sums[i][j] = 0;
       }
   }
   for(k=0; k<N; k++){
       x[k]=0;
       y[k]=0;
   }
}

void readmatrix(){
   int i=0,j=0, k=0;
   //read x, y matrixes from input file
   for(k=0; k<N; k++){
       fscanf(InFile, "%f", &x[k]);
       fscanf(InFile, "%f", &y[k]);
   }
   //init square sums matrix
   for(i=0; i<K+1; i++){
       for(j=0; j<K+1; j++){
	   sums[i][j] = 0;
	   for(k=0; k<N; k++){
	       sums[i][j] += pow(x[k], i+j);
	   }
       }
   }
   //init free coefficients column
   for(i=0; i<K+1; i++){
       for(k=0; k<N; k++){
	   b[i] += pow(x[k], i) * y[k];
       }
   }
}

void printresult(){
   //print polynom parameters
   int i=0;
   printf("\n");
   for(i=0; i<K+1; i++){
       if(i == 0) {
           cout << a[0] << " + ";
       } else if(i == 1) {
           cout << a[1] << "*x + ";
       } else if (i == K) {
           cout << a[i] << "*x^" << i << endl;   
       } else {
           cout << a[i] << "*x^" << i << " + "; 
       }
   }
   for(double x = 0; x<=5; x++) {
   cout << a[0]+a[1]*x+a[2]*x*x+a[3]*x*x*x+a[4]*x*x*x*x+a[5]*x*x*x*x*x << endl;
   }
   ofstream fout;
   fout.open("polinom.txt");
   for(int x = 0; x<=5; x++) {
       fout << a[x] << endl;
   }
   fout.close();
}
void diagonal(){
   int i, j, k;
   float temp=0;
   for(i=0; i<K+1; i++){
       if(sums[i][i]==0){
	   for(j=0; j<K+1; j++){
	       if(j==i) continue;
	       if(sums[j][i] !=0 && sums[i][j]!=0){
		   for(k=0; k<K+1; k++){
		       temp = sums[j][k];
		       sums[j][k] = sums[i][k];
		       sums[i][k] = temp;
		   }
		   temp = b[j];
		   b[j] = b[i];
		   b[i] = temp;
		   break;
	       }
	   }
       }
   }
}
void cls(){
   for(int i=0; i<25; i++) printf("\n");
}
int main(){
   int i=0,j=0, k=0;
   cls();
   do{
       InFile = fopen("data_real.txt", "rt");
   }while(InFile==NULL);
   count_num_lines();
   printf("\nNumber of points: N=%d", N);
   do{
       K = 5;
   }while(K>=N);
   allocmatrix();
   rewind(InFile);
   //read data from file
   readmatrix();
   //check if there are 0 on main diagonal and exchange rows in that case
   diagonal();
   fclose(InFile);
   //printmatrix();
   //process rows
   for(k=0; k<K+1; k++){
       for(i=k+1; i<K+1; i++){
	   if(sums[k][k]==0){
	       printf("\nSolution is not exist.\n");
	       return 0;
	   }
	   float M = sums[i][k] / sums[k][k];
	   for(j=k; j<K+1; j++){
	       sums[i][j] -= M * sums[k][j];
	   }
	   b[i] -= M*b[k];
       }
   }
   //printmatrix();
   for(i=(K+1)-1; i>=0; i--){
       float s = 0;
       for(j = i; j<K+1; j++){
	   s = s + sums[i][j]*a[j];
       }
       a[i] = (b[i] - s) / sums[i][i];
   }
   printresult();
   freematrix();
}