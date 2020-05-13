#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	int a[1005];
	cin>>n;
	for(int i=0;i<n;i++)
	    cin>>a[i];
	    
	sort(a,a+n);      //©ЛкыеепР 
	
	for(int j=0;j<n;j++)
	    cout<<a[j]<<" ";
	return 0;
} 
