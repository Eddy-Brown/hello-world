#include<iostream>
#include <graphics.h>                        //ͼ�ο� 
#include<math.h>
#define N 19
using namespace std;

double x[19]={0.520,3.1,8.0,17.95,28.65,39.62,50.65,78.0,104.6,156.6,
	          208.6,260.7,312.5,364.4,416.3,468.0,494.0,507.0,520.0};
	                                        //������ 
double y[19]={5.288,9.4,13.84,20.20,24.90,28.44,31.10,35.0,36.9,36.6,
	          34.6,31.0,26.34,20.9,14.8,7.8,3.7,1.5,0.2};
	                                        //������ 
double h[18]={0};                           //����                  
double m[18]={0};                           //��
double n[18]={0};                           //��
double one[18]={0};                         //һ�ײ��� 
double two[18]={0};                         //���ײ��� 
double c[19]={0};
double M[19]={0};
double A[19][19]={0};                       //���� 

//�����ſɱȵ������ⷽ�������M
double NF2(double *x,double *y)            //������������Ķ��������� 
{
    int i;
    float z,sum1=0;
    for(i=0;i<N;i++){
	    sum1=sum1+pow(y[i]-x[i],2);
    }
    z=sqrt(sum1);	
    return z;
}

void jac(double A[19][19],double b[19])    //�����ſɱȵ�����������Է����� 
{
	double sum=0;
    double x[N]={0},M[N]={0};
	int i,j,n=0;
	for(int i=0;i<N;i++)
		x[i]=0;
	for(n=0;;n++)
	{
	    for(int i=0;i<N;i++)
		{
		    sum=0;
		    for(int j=0;j<N;j++)
			{
			    if(j!=i)
				    sum=sum+A[i][j]*x[j];
		    }                               
		    M[i]=(1/A[i][i])*(b[i]-sum);
	    }
		if(NF2(x,M)>0.01)
		{
			for(int i=0;i<N;i++)
			{
		        x[i]=M[i];
	        }
	    } 
		else
			break;
	} 
}

//������������ֵ 
double ccc(double a)
{
	int i;
	double s=0;
	for(i=0;i<18;i++)
	    h[i] = x[i+1] - x[i];                // �󲽳�   
	    
	for(i=1;i<18;i++)
	    m[i] = h[i-1]/(h[i-1]+h[i]);         //���
	    
	for(i=1;i<18;i++)                        //��
	    n[i]=1-m[i];
	    
	for(i=0;i<18;i++)
	    one[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);  //��һ�ײ��� 
	    
	for(i=0;i<17;i++)
	    two[i]=(one[i+1]-one[i])/(x[i+2]-x[i]);  //����ײ��� 
	    
	for(i=1;i<=17;i++)
	    c[i]=6*two[i-1];
	c[0]=6*(one[0]-1.86548)/h[0];
    c[18]=6*(-0.046115-one[17])/h[17];            //��c 
	
	for(i=1;i<=17;i++)
	{
		A[i][i-1] = m[i];
		A[i][i+1] = n[i];
	}
	for(i=0;i<19;i++)
	    A[i][i] = 2;
	A[0][1] = A[18][17] = 1;                      //�����Է�������� 
	
	jac(A,c);                                     //�����ſɱȵ������ⷽ������M
	
	int g;
	for(i=0;i<18;i++)
	{
		if(a>x[i] && a<x[i+1])                    //ȷ��δ֪������ 
		    g = i; 
	}
	s = (M[g+1]*pow(a-x[g],3)) / (6*h[g]) - (M[g]*pow(a-x[g+1],3))/(6*h[g])
	    - (y[g]-(h[g]*h[g]*M[g])/6)*(a-x[g+1])/h[g] + (y[g+1]-(h[g]*h[g]*M[g+1])/6)*(a-x[g])/h[g];
	                                              //������������ֵ 
	return s;
}

//��ͼ���� 
void draw()
{
    initgraph(640, 480);                          //���廭���ߴ� 
    double x,y,cx = 100,cy = 400;                 // cx,cy ����ԭ������
    double normal = 10;                            //���嵥λ���� 
    setcolor(RGB(0xff,0xff,0xff));                //������������ɫ 
    line(0,int(cy),getwidth(),int(cy));           //����X�� 
    line(int(cx),0,int(cx),getheight());          //����Y��
	 
    setcolor(RGB(0,0xff,0xff));                   //���庯��������ɫ 
    moveto(cx,cy);                                //������ƶ���ԭ�� 

    for (x =0.521;x<= 520;x+=0.001)
    {
        y = ccc(x);                               //��X��Ӧ��������
        lineto(x+cx,cy-y*normal);                 //���������� 
    }
    getch();
}

int main()
{
    cout<<"������x=2.30�ϵ�ֵΪ"<<ccc(2.3)<<endl;
    cout<<"������x=130�ϵ�ֵΪ"<<ccc(130)<<endl;
    cout<<"������x=350�ϵ�ֵΪ"<<ccc(350)<<endl;
    cout<<"������x=515�ϵ�ֵΪ"<<ccc(515)<<endl;
    
    draw();
}
