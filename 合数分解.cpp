#include<iostream>
using namespace std;

int main()
{
	aaa:
	int n = 0;
	cin>>n;
	int i = 2;
	
	for(;i<=n;)
	{
		if(n%i == 0)
		{
			n/=i;
			cout<<i<<" ";
		}
		else
		{
			i++;
		}
	}
	cout<<endl<<endl;
	goto aaa;
	return 0;
}
