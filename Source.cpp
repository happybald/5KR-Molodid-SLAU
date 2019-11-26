#include <iostream>
#include<iomanip>
#include <vector>
using namespace std;
// Вывод системы уравнений

void sysout(double **a, double *y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout <<setw(10)<< a[i][j] << "*x" << j;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	return;
};

double * gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.00000000001;  // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}


double templ(double** X, double **A, double *B, int N, int iter) {
	double temp;
	if (N == 0) {
		return temp = (-1)*(A[N][1] / A[N][0])*X[iter][1] + (-1)*(A[N][2] / A[N][0])*X[iter][2] + (-1)*(A[N][3] / A[N][0])*X[iter][3] + (B[N] / A[N][0]);
	}
	if (N == 1) {
		return temp = (-1)*(A[N][0] / A[N][1])*X[iter][0] + (-1)*(A[N][2] / A[N][1])*X[iter][2] + (-1)*(A[N][3] / A[N][1])*X[iter][3] + (B[N] / A[N][1]);
	}
	if (N == 2) {
		return temp = (-1)*(A[N][0] / A[N][2])*X[iter][0] + (-1)*(A[N][1] / A[N][2])*X[iter][1] + (-1)*(A[N][3] / A[N][2])*X[iter][3] + (B[N] / A[N][2]);
	}
	if (N == 3) {
		return temp = (-1)*(A[N][0] / A[N][3])*X[iter][0] + (-1)*(A[N][1] / A[N][3])*X[iter][1] + (-1)*(A[N][2] / A[N][3])*X[iter][2] + (B[N] / A[N][3]);
	}
}

double **iter(double**A, double*B) {
	int S = 10;
	double **X = new double*[S];
	X[0] = new double[4];
	X[0][0] = 1;
	X[0][1] = 1;
	X[0][2] = 1;
	X[0][3] = 1;
	for (int i = 1; i < S; i++) {
		X[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			X[i][j] = templ(X, A, B, j, i-1);
		}
		cout <<"N="<<i<<" "<<setprecision(5)<<"x1="<< X[i][0] << " " <<"x2="<< X[i][1] << " " <<"x3="<< X[i][2] << " " <<"x4="<< X[i][3] << endl;
	}
	return X;
}
	
int main()
{
	int N = 32;
	double **M = new double*[N + 1];
	for (int i = 0; i <= N; i++) {
		M[i] = new double[N + 1];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//формула
			M[i][j] = sin(pow((i-15), 2) + pow((j-15), 2) + sqrt(i*j));
		}
	}


	int iA = 10;
	int jA = 5;


	double **a, *y, *x;
	int n = 4;
	system("cls");
	cout << "Count of nevidomyh : " << n;

	a = new double*[n];
	a = new double*[n];
	y = new double[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = M[iA + i][jA + j];
		}
	}	for (int i = 0; i < n; i++)
	{
		y[i] = M[i + 1][jA + 4];
	}

	for (int i = 0; i < n; i++) {
		a[i][i] *= n;
	}

	cout << endl;
	sysout(a, y, n);
	x = gauss(a, y, n);
	for (int i = 0; i < n; i++) {
		cout << "x[" << i << "]=" << x[i] << endl;
	}
//--------------------------------
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = M[iA + i][jA + j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		y[i] = M[i + 1][jA + 4];
	}
	for (int i = 0; i < n; i++) {
		a[i][i] *= 4;
	}
//---------------------------------
	double** IterMet = iter(a, y);
	system("pause");
	return 0;
}