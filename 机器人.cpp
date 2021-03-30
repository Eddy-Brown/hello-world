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

//����������ɫ��RGBֵ���Ƚ��Ƿ���ͬ���ݲ�Ϊdis
bool sameColor(int r1, int g1, int b1, int r2, int g2, int b2)
{
    //�ݲ��
    int dis = 10;
    if (abs(r1 - r2) <= dis && abs(g1 - g2) <= dis && abs(b1 - b2) <= dis) {
        return true;
    }
    else {
        return false;
    }
}


//����
void glPoint(int x, int y, int r, int g, int b) {
    glColor3ub(r, g, b);
    glPointSize(1);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


//��������㷨
void zzFill(int startX, int startY, int r, int g, int b) {
    stack<Point> pixelStack;
    //x,y�Ǹ������������ص㣬rgb����Ҫ������ɫ��RGBֵ
    Point point = { startX,startY };
    pixelStack.push(point);
    int saveX;
    int xRight, xLeft;
    int x, y;
    //���ջ��Ϊ��
    while (!pixelStack.empty()) {
        //��ȡ��˵�Ԫ��
        Point tempPoint = pixelStack.top();
        //ɾ����˵�Ԫ��
        pixelStack.pop();
        saveX = tempPoint.x;
        x = tempPoint.x;
        y = tempPoint.y;
        glReadPixels(x + halfWidth, y + halfHeight, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        //���û�е����ұ߽磬�����
        while (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]))
        {
            glPoint(x, y, r, g, b);
            x = x + 1;
            glReadPixels(x + halfWidth, y + halfHeight, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        }
        xRight = x - 1;
        x = saveX - 1;
        glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        //���û�е�����߽磬�����
        while (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2])) {
            glPoint(x, y, r, g, b);
            x = x - 1;
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
        }
        //������˵�
        xLeft = x + 1;
        //���ұߵĵ㿪ʼ
        x = xRight;
        //����϶˵�ɨ����
        y = y + 1;
        while (x >= xLeft) {
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            if (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]) && !sameColor(iPixel[0], iPixel[1], iPixel[2], r, g, b)) {
                //����Ϸ��ĵ㲻�Ǳ߽�㣬ֱ��ѹ��
                Point p = { x,y };
                pixelStack.push(p);
                //ѹ��֮��ֹͣѭ��
                break;
            }
            else {
                x--;
                glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            }
        }
        //����¶˵�ɨ����
        y = y - 2;
        //���ұߵĵ㿪ʼ
        x = xRight;
        while (x >= xLeft) {
            glReadPixels(x + halfWidth, y + halfWidth, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &iPixel);
            if (!sameColor(iPixel[0], iPixel[1], iPixel[2], borderColor[0], borderColor[1], borderColor[2]) && !sameColor(iPixel[0], iPixel[1], iPixel[2], r, g, b)) {
                //����Ϸ��ĵ㲻�Ǳ߽�㣬ֱ��ѹ��
                Point p = { x,y };
                //ѹ��֮��ֹͣѭ��
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


//�����Σ�����������½�XY��������Ͻ�XY����
void glRect(int leftX, int leftY, int rightX, int rightY) {
    //���������
    glBegin(GL_LINE_LOOP);
    //���½�
    glVertex2d(leftX, leftY);
    //���½�
    glVertex2d(rightX, leftY);
    //���Ͻ�
    glVertex2d(rightX, rightY);
    //���Ͻ�
    glVertex2d(leftX, rightY);
    //��������
    glEnd();
}

//��Բ�Ǿ��Σ�������ο�ߣ��ǰ뾶���������ĵ�����
void glRoundRec(int centerX, int centerY, int width, int height, float cirR)
{
    //�����ھ��ο��һ�����ֵ
    int w = width / 2 - cirR;
    int h = height / 2 - cirR;

    //����֮PI��һ�����޵ĽǶ�
    float PI_HALF = PI / 2;
    //Բ�Ǿ��ε�����
    float tx, ty;
    //Բ�ǻ��ȣ�ts��ʼ���ȣ�te�������ȣ�dt���ӵĻ���
    double t, ts, te;
    double dt = 1 / cirR;
    //�ĸ����ޣ�Բ����w��h�в�ͬ�����������ĸ����޵Ĳ���������
    int opX[4] = { 1,-1,-1,1 };
    int opY[4] = { 1,1,-1,-1 };
    //����
    glBegin(GL_LINE_LOOP);
    //�����������ӵ�һ���޵���������
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

//�����ߣ����ƫ����XY����ʼ�Ļ��ȣ������Ļ��ȣ��뾶
void glArc(double x, double y, double start_angle, double end_angle, double radius)
{
    //��ʼ��������
    glBegin(GL_LINE_STRIP);
    //ÿ�λ����ӵĻ���
    double delta_angle = PI / 180;
    //��Բ��
    for (double i = start_angle; i <= end_angle; i += delta_angle)
    {
        //���Զ�λ�����Ǻ���ֵ
        double vx = x + radius * cos(i);
        double vy = y + radius * sin(i);
        glVertex2d(vx, vy);
    }
    //�����滭
    glEnd();
}


//��Բ
void glCircle(double x, double y, double radius)
{
    //��ȫԲ
    glArc(x, y, 0, 2 * PI, radius);
}

//�������Σ����������������
void glTri(int x1, int y1, int x2, int y2, int x3, int y3) {
    //�������
    glBegin(GL_LINE_LOOP);
    //һ��
    glVertex2d(x1, y1);
    //����
    glVertex2d(x2, y2);
    //����
    glVertex2d(x3, y3);
    //��������
    glEnd();
}

//���ߣ�������������
void glLine(int x1, int y1, int x2, int y2) {
    //����
    glBegin(GL_LINES);
    //һ��
    glVertex2d(x1, y1);
    //����
    glVertex2d(x2, y2);
    //��������
    glEnd();
}

//����������ͼ
void display(void)
{
    //GL_COLOR_BUFFER_BIT��ʾ�����ɫ
    glClear(GL_COLOR_BUFFER_BIT);
    //���û�����ɫ
    glColor3f(0.0, 0.0, 0.0);
    //���û��߿��
    glLineWidth(2);

    //��Բ�Ǿ��Σ������
    glRoundRec(0, 0, 146, 120, 15);
    //��Բ�Ǿ��Σ�����
    glRoundRec(0, 113, 128, 74, 10);
    //Բ�Ǿ��Σ���������
    glRoundRec(81, 115, 20, 34, 5);
    glRoundRec(-81, 115, 20, 34, 5);
    //��Բ�Ǿ��Σ�����
    glRoundRec(-32, -92, 38, 52, 10);
    glRoundRec(32, -92, 38, 52, 10);

    //�����۾�
    glCircle(-30, 111, 10);
    glCircle(30, 111, 10);
    //��Բ�Σ�����
    glCircle(-95, -47, 10);
    glCircle(95, -47, 10);
    //Բ��������
    glArc(0, 133, 11 * PI / 8, 13 * PI / 8, 45);

    //�����Σ�����
    glRect(-25, 60, 25, 76);
    //�����Σ��첲���Ӵ�
    glRect(-81, 43, -73, 25);
    glRect(81, 43, 73, 25);
    //�����Σ��ϱ�
    glRect(-108, 45, -81, 0);
    glRect(108, 45, 81, 0);
    //�����Σ��б�
    glRect(-101, 0, -88, -4);
    glRect(101, 0, 88, -4);
    //�����Σ��±�
    glRect(-108, -4, -81, -37);
    glRect(108, -4, 81, -37);
    //�������Ӵ�
    glRect(-41, -62, -21, -66);
    glRect(41, -62, 21, -66);
    //�����Σ�����
    glRect(-41, -125, -21, -117);
    glRect(41, -125, 21, -117);
    //�����Σ������
    glRect(-59, -125, -8, -137);
    glRect(59, -125, 8, -137);

    //��������
    glLine(-35, 150, -35, 173);
    glLine(35, 150, 35, 173);
 

    //�����ǣ������������
    glTri(-30, -15, 30, -15, 0, 28);
    //��Բ���м�СȦ
    glCircle(0, 0, 10);


    //��ɫ:195,195,195
    //��ɫ:255,243,0
    //��ɫ:237,28,36
    //���ɫ:126,126,126
    //����
    zzFill(0, 70, 195, 195, 195);
    //ͷ
    zzFill(-50, 110, 195, 195, 195);
    zzFill(0, 93, 195, 195, 195);
    //����
    zzFill(-50, 0, 195, 195, 195);
    //����
    zzFill(-80, 115, 126, 126, 126);
    zzFill(80, 115, 126, 126, 126);
    //��������
    zzFill(-20, -10, 255, 243, 0);
    //���Ӻ�ɫԲ
    zzFill(0, 0, 237, 28, 36);
    //zzFill(-50,0,128,255,33);
    //���
    zzFill(-90, 30, 126, 126, 126);
    zzFill(90, 30, 126, 126, 126);
    //С��
    zzFill(-90, -20, 126, 126, 126);
    zzFill(90, -20, 126, 126, 126);
    //��
    zzFill(-75, 40, 195, 195, 195);
    zzFill(75, 40, 195, 195, 195);
    //��
    zzFill(-95, -47, 195, 195, 195);
    zzFill(95, -47, 195, 195, 195);
    //�������Ӵ�
    zzFill(-40, -64, 195, 195, 195);
    zzFill(40, -64, 195, 195, 195);
    //����
    zzFill(-40, -100, 126, 126, 126);
    zzFill(40, -100, 126, 126, 126);
    //����
    zzFill(-40, -121, 195, 195, 195);
    zzFill(40, -121, 195, 195, 195);
    //����
    zzFill(-40, -130, 126, 126, 126);
    zzFill(40, -130, 126, 126, 126);
    system("pause");



    glFlush();
}


//���ڴ�С�仯ʱ���õĺ���
void ChangeSize(GLsizei w, GLsizei h)
{
    //����߶�Ϊ0
    if (h == 0) {
        h = 1;
    }
    //�����ӿڴ�С�����һ��  
    glViewport(0, 0, w, h);
    int half = 200;
    //��������ϵͳ��ʹͶӰ�任��λ
    glMatrixMode(GL_PROJECTION);
    //����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
    glLoadIdentity();
    //��������������  
    if (w < h) {
        //����߶ȴ��ڿ�ȣ��򽫸߶��ӽ�����ͼ����ʾ����
        glOrtho(-half, half, -half * h / w, half * h / w, -half, half);
    }
    else {
        //�����ȴ��ڸ߶ȣ��򽫿���ӽ�����ͼ����ʾ����
        glOrtho(-half * w / h, half * w / h, -half, half, -half, half);
    }

    halfWidth = w / 2;
    halfHeight = h / 2;

}

//�������
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("�߿�robot");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(&display);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}

