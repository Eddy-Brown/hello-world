#include<iostream>
#include<iomanip>
using namespace std;

int a[5][5];
int b[10][10];

int ccc() 
{
	for (int i = 0; i < 5; i++) //初始化原数组
	{
		for (int j = 0; j < 5; j++) {
			a[i][j] = 0;
		}
	}

	a[0][1] = a[0][2] = a[0][3] = 111;
	a[1][1] =					  111;
	a[2][1] = a[2][2] = a[2][3] = 111;
	a[3][1] =			a[3][3] = 111;
	a[4][1] = a[4][2] = a[4][3] = 111;
	for (int i = 0; i < 10; i++) //初始化目的数组
	{
		for (int j = 0; j < 10; j++) {
			b[i][j] = -1;
		}
	}

	
	for (int i = 0; i < 5; i++)  //将原数组扩展
	{
		for (int j = 0; j < 5; j++) {
			b[i *2][j*2] = a[i][j];
		}
	}
}


int La(int x, int x0, int x1, int y0, int y1)  //拉格朗日插值函数 
{
	return (double)(x - x1) / (double)(x0 - x1) * y0 + (double)(x - x0) / (double)(x1 - x0) * y1;
}


void La() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) 
		{
			if (b[i][j] == -1) {
				int y0 = b[i][j - 1];
				int y1 = b[i][j + 1];
				b[i][j] = La(j, j - 1, j + 1, y0, y1);
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) 
		{
			if (b[j][i] == -1) 
			{
			    int y0 = b[j - 1][i];
			    int y1 = b[j + 1][i];
			    b[j][i] = La(j, j - 1, j + 1, y0, y1);
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		b[i][9] = b[i][8];
		b[9][i] = b[8][i];
	}
}
 int ddd() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << setw(3)<< setfill('0')<<b[i][j] << " ";
		}
		cout << endl;
	}
}

int main() 
{
	ccc();
	La();
	ddd();
	return 0;
}

