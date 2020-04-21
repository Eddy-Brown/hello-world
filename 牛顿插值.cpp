#include<iostream>  
#include<iomanip> 
#include<vector>  
using namespace std;
 
double ChaShang(int n, vector<double>&X, vector<double>&Y);
void Newton(int n1, vector<double>& xp, vector<double>&X, vector<double>&Y, vector<double> &result);
int NNN(double q,double w,double e,double r,double t);

int main()
{
	int a[5][5];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = 0;
		}
	}

	//画一个6
	a[0][1] = a[0][2] = a[0][3] = 123;
	a[1][1] =					  123;
	a[2][1] = a[2][2] = a[2][3] = 123;
	a[3][1] =			a[3][3] = 123;
	a[4][1] = a[4][2] = a[4][3] = 123;
	
	NNN(a[0][0],a[0][1],a[0][2],a[0][3],a[0][4]);
	NNN(a[1][0],a[1][1],a[1][2],a[1][3],a[1][4]);
	NNN(a[2][0],a[2][1],a[2][2],a[2][3],a[2][4]);
	NNN(a[3][0],a[3][1],a[3][2],a[3][3],a[3][4]);
	NNN(a[4][0],a[4][1],a[4][2],a[4][3],a[4][4]);
	return 0;
}
int NNN(double q,double w,double e,double r,double t)
{
	
	int n=5,n1=10;
	//cout << "请输入插值点的个数" << endl;
	
	vector<double>X(n, 0);
	vector<double>Y(n, 0);
	
	//cout << "请输入插值点X[i]的值" << endl;
	int o = 1;
	for (int i = 0; i<n; i++)
	{
		X[i] = o;
		o+=2;
	}
	//cout << "请输入插值点Y[i]的值" << endl;
     double A[5] = {q,w,e,r,t};
     for (int i = 0; i<n; i++)
	{
		Y[i] = A[i];
	}
	
	//cout << "请输入所求点的个数" << endl;
	
	vector<double> xp(n1, 0);
	vector<double> result(n1, 0);
	//cout << "请输入所求插值点xp[i]的值：" << endl;
	for (int i = 0; i<n1; i++)
	{
		xp[i] = i+1;
	}
	Newton(n1,xp, X, Y,result);
	//cout << "输出所求插值点的函数值：" << endl;
	for (int h = 0; h < n1; h++)
	{
		cout<< setw(3)<< setfill('0')<<result[h]<<"  ";
	}
	cout<<endl;
}
 
double ChaShang(int n, vector<double>&X, vector<double>&Y)
{
	double f = 0;
	double temp = 0;
	for (int i = 0; i<n + 1; i++)
	{
		temp = Y[i];
		for (int j = 0; j<n + 1; j++)
			if (i != j) temp /= (X[i] - X[j]);
		f += temp;
	}
	return f;
}
 
void Newton(int n1, vector<double>& xp, vector<double>&X, vector<double> &Y, vector<double> &result)
{
	double temp1 = 0;
	for (int h = 0; h < n1; h++)
	{
		for (int i = 0; i < X.size(); i++)
		{
			double temp = 1;
			double f = ChaShang(i, X, Y);
			for (int j = 0; j < i; j++)
			{
				temp = temp*(xp[h] - X[j]);
			}
			temp1 += f*temp;
		}
		result[h] = temp1;
		temp1 = 0;
	}
}

