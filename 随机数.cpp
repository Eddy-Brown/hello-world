#include <iostream>
#include   <stdlib.h>    
#include   <time.h> 
#define MIN 0    //����������ķ�Χ    
#define MAX 99

using namespace std;

int main()   
{ 
	int i; 
	srand((unsigned)time(0));
	cout<<"Ten random numbers from "<<MIN<<
	      " to "<<MAX<<" :\n"<<endl;   
	for(i=0; i<10; i++)          //���������
	{
		cout<<MIN + rand() % (MAX + MIN - 1)<<"   "; 
	}
	cout<<endl;
	return   0;   
} 
