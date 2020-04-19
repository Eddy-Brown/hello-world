#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c,i,t;
	for(i=100;i<1000;i++)
	{
		t=i;
		a=t%10;
		t/=10;
		b=t%10;
		c=t/10;
		if(pow(a,3)+pow(b,3)+pow(c,3)==i)
		printf("%d\n",i);
	}
	
		return 0;
}
