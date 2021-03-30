#include "gl/glut.h"
#include <math.h> 
#include <stack>
using namespace std;
#define PI 3.1415926

struct Point
{
    int x;
    int y;
};

int halfWidth, halfHeight;
GLubyte iPixel[3];
GLubyte borderColor[3] = { 0,0,0 };

//传入两个颜色的RGB值，比较是否相同，容差为dis
bool sameColor(int r1, int g1, int b1, int r2, int g2, int b2)
{
    //容差度
    int dis = 10;
    if (abs(r1 - r2) <= dis && abs(g1 - g2) <= dis && abs(b1 - b2) <= dis) {
        return true;
    }
    else {
        return false;
    }
}


//画点
void glPoint(int x, int y, int r, int g, int b) {
    glColor3ub(r, g, b);
    glPointSize(1);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


//种子填充算法
void zzFill(int startX, int startY, int r, int g, int b) {
    stack<Point> pixelStack;
    //x,y是给定的种子像素点，rgb就是要填充的颜色的RGB值
    Point point = { startX,startY };
    pixelStack.push(point);
    int saveX;
    int xRight, xLeft;
    int x, y;
    //如果栈不为空
    while (!pixelStack.empty()) {
        //获取最顶端的元素
        Point tempPoint = pixelStack.top();
        //删除最顶端的元素
        pixelStack.pop();
        saveX = tempPoint.x;
        x = tempPoint.x;
        y = tempPoint.y;
        glReadPixels(x + halfWidth, y + halfHeight, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        //如果没有到达右边界，就填充
        while (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]))
        {
            glPoint(x, y, r, g, b);
            x = x + 1;
            glReadPixels(x + halfWidth, y + halfHeight, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        }
        xRight = x - 1;
        x = saveX - 1;
        glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        //如果没有到达左边界，就填充
        while (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2])) {
            glPoint(x, y, r, g, b);
            x = x - 1;
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        }
        //保存左端点
        xLeft = x + 1;
        //从右边的点开始
        x = xRight;
        //检查上端的扫描线
        y = y + 1;
        while (x >= xLeft) {
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            if (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]) && !sameColor(iPixel[0], iPixel[1], iPixel[2], r, g, b)) {
                //如果上方的点不是边界点，直接压入
                Point p = { x,y };
                pixelStack.push(p);
                //压入之后停止循环
                break;
            }
            else {
                x--;
                glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            }
        }
        //检查下端的扫描线
        y = y - 2;
        //从右边的点开始
        x = xRight;
        while (x >= xLeft) {
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            if (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]) && !sameColor(iPixel[0], iPixel[1], iPixel[2], r, g, b)) {
                //如果上方的点不是边界点，直接压入
                Point p = { x,y };
                //压入之后停止循环
                pixelStack.push(p);
                break;
            }
            else {
                x--;
                glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            }
        }
    }
}


//画矩形，传入的是左下角XY坐标和右上角XY坐标
void glRect(int leftX, int leftY, int rightX, int rightY) {
    //画封闭曲线
    glBegin(GL_LINE_LOOP);
    //左下角
    glVertex2d(leftX, leftY);
    //右下角
    glVertex2d(rightX, leftY);
    //右上角
    glVertex2d(rightX, rightY);
    //左上角
    glVertex2d(leftX, rightY);
    //结束画线
    glEnd();
}

//画圆角矩形，传入矩形宽高，角半径，矩形中心点坐标
void glRoundRec(int centerX, int centerY, int width, int height, float cirR)
{
    //计算内矩形宽高一半的数值
    int w = width / 2 - cirR;
    int h = height / 2 - cirR;

    //二分之PI，一个象限的角度
    float PI_HALF = PI / 2;
    //圆角矩形的坐标
    float tx, ty;
    //圆角弧度，ts开始弧度，te结束弧度，dt增加的弧度
    double t, ts, te;
    double dt = 1 / cirR;
    //四个象限，圆弧与w、h有不同操作，定义四个象限的操作操作符
    int opX[4] = { 1,-1,-1,1 };
    int opY[4] = { 1,1,-1,-1 };
    //画线
    glBegin(GL_LINE_LOOP);
    //用来计数，从第一象限到第四象限
    int x, y;
    for (x = 0; x < 4; x = x + 1)
    {
        ts = PI_HALF * x;
        te = PI_HALF * (x + 1);
        for (t = ts; t <= te; t += dt)
        {
            tx = cirR * cos(t) + opX[x] * w + centerX;
            ty = cirR * sin(t) + opY[x] * h + centerY;
            glVertex2f(tx, ty);
        }
    }
    glEnd();
}

//画弧线，相对偏移量XY，开始的弧度，结束的弧度，半径
void glArc(double x, double y, double start_angle, double end_angle, double radius)
{
    //开始绘制曲线
    glBegin(GL_LINE_STRIP);
    //每次画增加的弧度
    double delta_angle = PI / 180;
    //画圆弧
    for (double i = start_angle; i <= end_angle; i += delta_angle)
    {
        //绝对定位加三角函数值
        double vx = x + radius * cos(i);
        double vy = y + radius * sin(i);
        glVertex2d(vx, vy);
    }
    //结束绘画
    glEnd();
}


//画圆
void glCircle(double x, double y, double radius)
{
    //画全圆
    glArc(x, y, 0, 2 * PI, radius);
}

//画三角形，传入三个点的坐标
void glTri(int x1, int y1, int x2, int y2, int x3, int y3) {
    //画封闭线
    glBegin(GL_LINE_LOOP);
    //一点
    glVertex2d(x1, y1);
    //二点
    glVertex2d(x2, y2);
    //三点
    glVertex2d(x3, y3);
    //结束画线
    glEnd();
}

//画线，传入两点坐标
void glLine(int x1, int y1, int x2, int y2) {
    //画线
    glBegin(GL_LINES);
    //一点
    glVertex2d(x1, y1);
    //二点
    glVertex2d(x2, y2);
    //结束画线
    glEnd();
}

//函数用来画图
void display(void)
{
    //GL_COLOR_BUFFER_BIT表示清除颜色
    glClear(GL_COLOR_BUFFER_BIT);
    //设置画线颜色
    glColor3f(0.0, 0.0, 0.0);
    //设置画线宽度
    glLineWidth(2);

    //画圆角矩形，大肚子
    glRoundRec(0, 0, 146, 120, 15);
    //画圆角矩形，大脸
    glRoundRec(0, 113, 128, 74, 10);
    //圆角矩形，两个耳朵
    glRoundRec(81, 115, 20, 34, 5);
    glRoundRec(-81, 115, 20, 34, 5);
    //画圆角矩形，大长腿
    glRoundRec(-32, -92, 38, 52, 10);
    glRoundRec(32, -92, 38, 52, 10);

    //两个眼睛
    glCircle(-30, 111, 10);
    glCircle(30, 111, 10);
    //画圆形，手掌
    glCircle(-95, -47, 10);
    glCircle(95, -47, 10);
    //圆弧，画嘴
    glArc(0, 133, 11 * PI / 8, 13 * PI / 8, 45);

    //画矩形，脖子
    glRect(-25, 60, 25, 76);
    //画矩形，胳膊连接处
    glRect(-81, 43, -73, 25);
    glRect(81, 43, 73, 25);
    //画矩形，上臂
    glRect(-108, 45, -81, 0);
    glRect(108, 45, 81, 0);
    //画矩形，中臂
    glRect(-101, 0, -88, -4);
    glRect(101, 0, 88, -4);
    //画矩形，下臂
    glRect(-108, -4, -81, -37);
    glRect(108, -4, 81, -37);
    //画腿连接处
    glRect(-41, -62, -21, -66);
    glRect(41, -62, 21, -66);
    //画矩形，脚踝
    glRect(-41, -125, -21, -117);
    glRect(41, -125, 21, -117);
    //画矩形，大脚掌
    glRect(-59, -125, -8, -137);
    glRect(59, -125, 8, -137);

    //两条天线
    glLine(-35, 150, -35, 173);
    glLine(35, 150, 35, 173);
 

    //画三角，肚子里的三角
    glTri(-30, -15, 30, -15, 0, 28);
    //画圆，中间小圈
    glCircle(0, 0, 10);


    //灰色:195,195,195
    //黄色:255,243,0
    //红色:237,28,36
    //深灰色:126,126,126
    //脖子
    zzFill(0, 70, 195, 195, 195);
    //头
    zzFill(-50, 110, 195, 195, 195);
    zzFill(0, 93, 195, 195, 195);
    //肚子
    zzFill(-50, 0, 195, 195, 195);
    //耳朵
    zzFill(-80, 115, 126, 126, 126);
    zzFill(80, 115, 126, 126, 126);
    //肚子三角
    zzFill(-20, -10, 255, 243, 0);
    //肚子红色圆
    zzFill(0, 0, 237, 28, 36);
    //zzFill(-50,0,128,255,33);
    //大臂
    zzFill(-90, 30, 126, 126, 126);
    zzFill(90, 30, 126, 126, 126);
    //小臂
    zzFill(-90, -20, 126, 126, 126);
    zzFill(90, -20, 126, 126, 126);
    //手
    zzFill(-75, 40, 195, 195, 195);
    zzFill(75, 40, 195, 195, 195);
    //手
    zzFill(-95, -47, 195, 195, 195);
    zzFill(95, -47, 195, 195, 195);
    //大腿连接处
    zzFill(-40, -64, 195, 195, 195);
    zzFill(40, -64, 195, 195, 195);
    //大腿
    zzFill(-40, -100, 126, 126, 126);
    zzFill(40, -100, 126, 126, 126);
    //脚踝
    zzFill(-40, -121, 195, 195, 195);
    zzFill(40, -121, 195, 195, 195);
    //脚掌
    zzFill(-40, -130, 126, 126, 126);
    zzFill(40, -130, 126, 126, 126);
    system("pause");



    glFlush();
}


//窗口大小变化时调用的函数
void ChangeSize(GLsizei w, GLsizei h)
{
    //避免高度为0
    if (h == 0) {
        h = 1;
    }
    //定义视口大小，宽高一致  
    glViewport(0, 0, w, h);
    int half = 200;
    //重置坐标系统，使投影变换复位
    glMatrixMode(GL_PROJECTION);
    //将当前的用户坐标系的原点移到了屏幕中心
    glLoadIdentity();
    //定义正交视域体  
    if (w < h) {
        //如果高度大于宽度，则将高度视角扩大，图形显示居中
        glOrtho(-half, half, -half * h / w, half * h / w, -half, half);
    }
    else {
        //如果宽度大于高度，则将宽度视角扩大，图形显示居中
        glOrtho(-half * w / h, half * w / h, -half, half, -half, half);
    }

    halfWidth = w / 2;
    halfHeight = h / 2;

}

//程序入口
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("线框robot");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(&display);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}

