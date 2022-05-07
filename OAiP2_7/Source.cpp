#include <iostream>
#include <conio.h>

using namespace std;

const double A = 1.;
const double B = 4.;
const int M = 11;
const int N = 12;

void createTable(double a, int m, double h, double* arr);
void calculateApprox(double a, int n, double h_approx, int m, double*& arr, double* arr_approx);
double calculateH(double a, double b, int m);
double linearInterpoliation(double x, double*& arr, int m);
double calculateLinearInterpoliation(double x, double*& arr, int i);
double function(double x);
int correctInputInt();
double correctInputDouble();

int main()
{
	char code;
	double a, b, h, h_approx;
	int n, m;
	cout << "Function: x - 5(sinx)^2" << endl;
	cout << "------------------------------------------" << endl;
	do
	{
		cout << "Do you want to use default values(a = " << A << ", b = " << B << ", m = " << M << ", n = " << N << ")? (Y/N)" << endl;
		code = (char)_getch();
		if (code == 'Y' || code == 'y')
		{
			a = A;
			b = B;
			m = M;
			n = N;
		}
		else
		{
			cout << "Enter a: ";
			a = correctInputDouble();
			cout << "Enter b: ";
			b = correctInputDouble();
			if (b < a)
			{
				cout << "b < a, swap them!" << endl;
				double temp = a;
				a = b;
				b = temp;
			}
			do
			{
				cout << "Enter m: ";
				m = correctInputInt();
			} while (m < 4);
			do
			{
				cout << "Enter n: ";
				n = correctInputInt();
			} while (n < m);
		}
		h = calculateH(a, b, m);
		h_approx = calculateH(a, b, n);
		double* arr = new double[m];
		double* arr_approx = new double[n];
		createTable(a, m, h, arr);
		calculateApprox(a, n, h_approx, m, arr, arr_approx);
		cout << "\nDo you want to continue?(Y/N)" << endl;
		code = (char)_getch();
		delete[]arr;
		delete[]arr_approx;
	} while (code == 'Y' || code == 'y');
	system("pause");
	return 0;
}

void calculateApprox(double a, int n, double h_approx, int m, double*& arr, double* arr_approx)
{
	double original, delta, max_fault = 0., x = a;
	for (int i = 0; i < n; i++, x += h_approx)
	{
		cout << "\n-> " << i + 1 << endl;
		cout << "Xt = " << x << endl;
		if (arr[0] < x && x < arr[m - 1])
		{
			arr_approx[i] = linearInterpoliation(x, arr, m);
			cout << "Approx Yt = " << arr_approx[i] << endl;
			original = function(x);
			cout << "Original Yt = " << original << endl;
			delta = fabs(arr_approx[i] - original);
			if (delta > max_fault)
			{
				max_fault = delta;
			}
		}
		else
		{
			cout << "Error! Xt is out of range!" << endl;
		}
	}
	cout << "\nMax fault: " << max_fault << endl;
}

double linearInterpoliation(double x, double*& arr, int m)
{
	for (int i = 0; i < m; i++)
	{
		if (x < arr[i])
		{
			return calculateLinearInterpoliation(x, arr, i);
		}
	}
}

double calculateLinearInterpoliation(double x, double*& arr, int i)
{
	double y = function(arr[i]);
	double y_prev = function(arr[i - 1]);
	return y_prev + (x - arr[i - 1]) * (y - y_prev) / (arr[i] - arr[i - 1]);
}

void createTable(double a, int m, double h, double* arr)
{
	double x = a;
	for (int i = 0; i < m; i++, x += h)
	{
		arr[i] = x;
	}
}

double calculateH(double a, double b, int m)
{
	return (b - a) / (m - 1.);
}

double function(double x)
{
	//return x - 5 * sin(x) * sin(x);
	return 0.1 * x * x * x + x * x - 10 * sin(x);
}

double correctInputDouble()
{
	double a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please write numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}

int correctInputInt()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please write numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}