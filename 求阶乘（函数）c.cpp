#include<stdio.h>      //Çó½×³Ë
int JC(int n)
{
	if(n==1)
    return 1;
    return n*JC(n-1);
} 
int main()
{
	int n,a;
	while(printf("Input n=")!=EOF)
	{
	    scanf("%d",&n);
		if(n<=0)
		{
		    printf("n<=0,error input.\n");
		    printf("\n");
		}
		else
		{
		    a=JC(n);
	        printf("n!=%d\n",a);  
	        printf("\n");
		}

	}
	return 0;
}
