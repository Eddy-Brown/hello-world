//将b表示的二进制数增1
#include<iostream>
#include<math.h>
#define N 3
using namespace std; 

void inc(int b[],int n)
{
	for(int i=N-1;i>=0;i--)
	{
		if(b[i])
		    b[i] = 0;
		else
		{
			b[i] = 1;
			break;
		}
	}
}

int main()
{
	int pw = (int)pow(2,N);
	int b[N]={0};
	for(int i=0;i<pw;i++)
	{
		inc(b,N);
		for(int j=0;j<N;j++)
		    cout<<b[j];
		cout<<"  ";
	}
}
