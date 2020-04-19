#include<iostream>
#define N 100
using namespace std;

int FFF(int a)
{
    if(a == 0)
        return 0;
	else if(a == 1)
	    return 1;
	else
	    return FFF(a - 1) + FFF(a - 2);
}

int main()
{
	int i,j = 0;
	aaa:
	cin>>j;
	cout<<"瞅瞅"<<j<<"的结果\n\n";
	if(j == 0)
	{
		cout<<"你整的啥输入啊？\n\n";
		goto aaa;
	}
	else
	{
		for(i = 1;i<=j;i++)
	    {
		    cout<<FFF(i)<<"  ";
	    }
	}
	
}
