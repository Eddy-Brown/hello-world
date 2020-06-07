#include<iostream>
#include <graphics.h>                        //图形库 
#include<math.h>
#define N 19
using namespace std;

double x[19]={0.520,3.1,8.0,17.95,28.65,39.62,50.65,78.0,104.6,156.6,
	          208.6,260.7,312.5,364.4,416.3,468.0,494.0,507.0,520.0};
	                                        //横坐标 
double y[19]={5.288,9.4,13.84,20.20,24.90,28.44,31.10,35.0,36.9,36.6,
	          34.6,31.0,26.34,20.9,14.8,7.8,3.7,1.5,0.2};
	                                        //纵坐标 
double h[18]={0};                           //步长                  
double m[18]={0};                           //λ
double n[18]={0};                           //μ
double one[18]={0};                         //一阶差商 
double two[18]={0};                         //二阶差商 
double c[19]={0};
double M[19]={0};
double A[19][19]={0};                       //矩阵 

//利用雅可比迭代法解方程组求得M
double NF2(double *x,double *y)            //求两个向量差的二范数函数 
{
    int i;
    float z,sum1=0;
    for(i=0;i<N;i++){
	    sum1=sum1+pow(y[i]-x[i],2);
    }
    z=sqrt(sum1);	
    return z;
}

void jac(double A[19][19],double b[19])    //利用雅可比迭代法求解线性方程组 
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

//求三次样条插值 
double ccc(double a)
{
	int i;
	double s=0;
	for(i=0;i<18;i++)
	    h[i] = x[i+1] - x[i];                // 求步长   
	    
	for(i=1;i<18;i++)
	    m[i] = h[i-1]/(h[i-1]+h[i]);         //求λ
	    
	for(i=1;i<18;i++)                        //μ
	    n[i]=1-m[i];
	    
	for(i=0;i<18;i++)
	    one[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);  //求一阶差商 
	    
	for(i=0;i<17;i++)
	    two[i]=(one[i+1]-one[i])/(x[i+2]-x[i]);  //求二阶差商 
	    
	for(i=1;i<=17;i++)
	    c[i]=6*two[i-1];
	c[0]=6*(one[0]-1.86548)/h[0];
    c[18]=6*(-0.046115-one[17])/h[17];            //求c 
	
	for(i=1;i<=17;i++)
	{
		A[i][i-1] = m[i];
		A[i][i+1] = n[i];
	}
	for(i=0;i<19;i++)
	    A[i][i] = 2;
	A[0][1] = A[18][17] = 1;                      //求线性方程组矩阵 
	
	jac(A,c);                                     //利用雅可比迭代法解方程组求M
	
	int g;
	for(i=0;i<18;i++)
	{
		if(a>x[i] && a<x[i+1])                    //确定未知数区间 
		    g = i; 
	}
	s = (M[g+1]*pow(a-x[g],3)) / (6*h[g]) - (M[g]*pow(a-x[g+1],3))/(6*h[g])
	    - (y[g]-(h[g]*h[g]*M[g])/6)*(a-x[g+1])/h[g] + (y[g+1]-(h[g]*h[g]*M[g+1])/6)*(a-x[g])/h[g];
	                                              //求三次样条插值 
	return s;
}

//绘图函数 
void draw()
{
    initgraph(640, 480);                          //定义画布尺寸 
    double x,y,cx = 100,cy = 400;                 // cx,cy 定义原点坐标
    double normal = 10;                            //定义单位长度 
    setcolor(RGB(0xff,0xff,0xff));                //定义坐标轴颜色 
    line(0,int(cy),getwidth(),int(cy));           //绘制X轴 
    line(int(cx),0,int(cx),getheight());          //绘制Y轴
	 
    setcolor(RGB(0,0xff,0xff));                   //定义函数曲线颜色 
    moveto(cx,cy);                                //将起点移动到原点 

    for (x =0.521;x<= 520;x+=0.001)
    {
        y = ccc(x);                               //求X对应的纵坐标
        lineto(x+cx,cy-y*normal);                 //将两点相连 
    }
    getch();
}

int main()
{
    cout<<"函数在x=2.30上的值为"<<ccc(2.3)<<endl;
    cout<<"函数在x=130上的值为"<<ccc(130)<<endl;
    cout<<"函数在x=350上的值为"<<ccc(350)<<endl;
    cout<<"函数在x=515上的值为"<<ccc(515)<<endl;
    
    draw();
}
