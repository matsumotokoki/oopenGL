#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define rd 40.0
#define mx 1000.0
#define my 600.0
#define m_box 50 //グラムi
#define m_sphere 5

float xsve,ysve,xsb,ysb=0,cpu_x=0,cpu_y,wall=0;
float xsve=9.8;
double vertices[][3]={//四角形
	{0.0-200, 0.0, 0.0},
	{0.0-200, 110, 0.0},
	{110-200, 110, 0.0},
	{110-200, 0.0, 0.0}
};
double cpu[][3]={//四角形
	{0.0+800,0.0, 0.0},
	{0.0+800,90, 0.0},
	{90+800, 90, 0.0},
	{90+800, 0.0, 0.0}
};
double outflame[][3]={//四角形
	{-mx-rd, -my-rd, 0.0},
	{mx+rd, -my-rd, 0.0},
	{mx+rd, my+rd, 0.0},
	{-mx-rd,my+rd, 0.0}
};
double L_goleline[][3]={//ペナルティエリア(L)
    {-1000-40,-300,0.0},
    {-950,-300,0.0},
    {-950,300,0.0},
    {-1000-40,300,0.0}
};
double R_goleline[][3]={//  //   (R)
    {1000+40,300,0.0},
    {950,300,0.0},
    {950,-300,0.0},
    {1000+40,-300,0.0}
};
double centerline[][3]={//センターライン
    {0,my+rd,0.0},
    {0,-my-rd,0.0},
    {mx+rd,-my-rd,0.0},
    {mx+rd,my+rd,0.0}
};
double wall_z[][3]={//四角形
	{-790-45, -600-44, 0.0},
	{-760-45, -600-44, 0.0},
	{-760-45, 600+44, 0.0},
	{-790-45, 600+44, 0.0}
};

int flg=0;
int c_flg=0;
float tx = 0.0;
float ty = 0.0;
float tz = 0.0;
float rx = 0.0;
float ry = 0.0;
float rz = 0.0;

float rox = 0.0; //移動量
float roy = 0.0; //移動量
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

	//ここからモデリング変換
	glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    if(wall){
    for(int i=0; i < 4; i++)
		glVertex3dv(wall_z[i]);
    }
    glEnd();
    glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	for(int i=0; i < 4; i++)
		glVertex3dv(outflame[i]); //2dではなく3d
    glEnd();
    glBegin(GL_LINE_LOOP);
	for(int i=0; i < 4; i++)
		glVertex3dv(L_goleline[i]); //2dではなく3d
    glEnd();
    glBegin(GL_LINE_LOOP);
	for(int i=0; i < 4; i++)
		glVertex3dv(R_goleline[i]); //2dではなく3d
    glEnd();
    glBegin(GL_LINE_LOOP);
	for(int i=0; i < 4; i++)
		glVertex3dv(centerline[i]); //2dではなく3d
    glEnd();
	glutWireSphere(rd+25,360,360);
    glBegin(GL_LINE_LOOP);
    glEnd();
	glTranslated(tx, ty, tz); //平行移動
	glRotated(rx, 1.0, 0.0, 0.0); //X軸回転
	glRotated(ry, 0.0, 1.0, 0.0); //Y軸回転
	glRotated(rz, 0.0, 0.0, 1.0); //Z軸回転
	//ここからモデリング座標系i
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	glutWireSphere(rd-10,50,50);
    glEnd();
    glColor3f(0.0,1.0,0.6);
	glTranslated(-tx, -ty,- tz); //平行移動
	glTranslated(rox, roy, tz);  //平行移動
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	for(int i=0; i < 4; i++)
		glVertex3dv(vertices[i]); //2dではなく3d
//	glutWireSphere(rd+15,tx+55,ty+55);
	glEnd();
    glColor3f(0.7,0.2,0.4);
	//glTranslated(-tx, -ty,- tz); //平行移動
	glTranslated(-rox,-roy,-tz);  //平行移動
    glTranslated(cpu_x,cpu_y-45,0.0);
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	for(int i=0; i < 4; i++)
		glVertex3dv(cpu[i]); //2dではなく3d
//	glutWireSphere(rd+15,tx+55,ty+55);
	glEnd();
	glFlush();

    ysve -=0;
    ysb -=0;
        if(flg<=0&&sqrt((ty-55-roy)*(ty-55-roy)+(tx-55-rox+200)*(tx-55-rox+200)) <= 100){
           if(xsb<=0&&xsve<=0&&xsb>=xsve) 
           xsve = -1*(xsve*m_sphere+xsb*m_box)*1/100;
           else
           xsve = (xsve*m_sphere+xsb*m_box)*1/10;
           if(ysb<=0&&ysve<=0&&ysve>=ysb)
           ysve = -1*(ysve*m_sphere+ysb*m_box)*1/100;
           else    
           ysve = (ysve*m_sphere+ysb*m_box)*1/10;
           xsb =  -1*xsve/10;
           ysb =  -1*ysve/10;
           flg=10;
        }else{
            flg--;}
        if(flg<=0&&sqrt((ty-cpu_y-45)*(ty-cpu_y-45)+(tx-845)*(tx-845)) <= 95){
           
           xsve = -1.5*xsve-3;
           ysve = 1.7*ysve;
           //xsb = -1 * xsve/3;
           //ysb = -1 * ysve/3;
           c_flg=10;
        }else{
           c_flg--;}
    if(cpu_y>=-700&&cpu_y<=700){
           if(cpu_y!=ty+45&&cpu_y+45>ty) cpu_y-=10;
           if(cpu_y!=ty+45&&cpu_y+45<=ty)cpu_y+=10;
    }
/********/
    if(tx>=1000&&xsve>=0){
        xsve = -1*xsve*0.4;
    }
    if(wall==1&&tx<=-750-10&&xsve<=0){
        xsve=-1*xsve*0.75;
    }
    else if(tx<=-1000-10&&xsve<=0){
        xsve = -1*xsve*0.4;
    }
    if(ty>=600&&ysve>=0){
        ysve = -1*ysve*0.7;
    }else if(ty<=-600&&ysve<=0){
        ysve = -1*ysve*0.7;
        if(ysve >=-0.003&&ysve<=0.003){
        }
    }
    if(ty<=-600&&ysve>=-0.0072&&ysve<=0.0072){
        ysve *=0.7;}
    if(ty<=-600&&ysve>=-0.0002&&ysve<=0.0002){
           // ysve =0;
    }
/********/

/********/
    if(rox>=1000-75+200&&xsb>=0){
        xsb = -1*xsb*0.2;
    }
    else if(rox<=-1000-35+200&&xsb<=0){
        xsb = -1*xsb*0.2;
    }
    if(roy>=600-70&&ysb>=0){
        ysb = -1*ysb*0.2;
    }else if(roy<=-600-40&&ysb<=0){
        ysb = -1*ysb*0.2;
        if(ysb >=-0.003&&ysb<=0.003){
        }
    }
    if(roy<=-600&&ysb>=-0.0072&&ysb<=0.0072){
        ysve *=0.3;}
    if(roy<=-600&&ysb>=-0.0002&&ysb<=0.0002){
           // ysb =0;
    }
/********/
       if(xsve>=20)xsve=20;
       if(ysve>=20)ysve=20;
        tx +=xsve; 
        ty +=ysve;
        rox +=xsb;
        roy +=ysb;
    if(tx>=950&&ty<=300&&ty>=-300){
        flg=500;
        while(flg){
            flg--;
        }
        ty=0;
        tx=0;
        xsve=-3;
        ysve=-3;
    }
    if(tx<=-950&&ty<=300&&ty>=-300){
        flg=500;
        while(flg){
            flg--;
        }
        ty=0;
        tx=0;
        xsve=3;
        ysve=3;
    }
    xsve*=0.9999;
    ysve*=0.9999;
    
	glutPostRedisplay();
}
void resize(int w, int h) 
{
	glViewport(0, 0, w, h); //ウインドウ全体に表示
	glMatrixMode(GL_PROJECTION); //投影変換モードへ
	glLoadIdentity(); //投影変換の変換行列を単位行列で初期化
	glOrtho(-1200.0, 1200.0, -744.0, 744.0, 1.0, -1.0); //各軸-1.0～1.0で囲まれる立方体の範囲を並行投影
    glMatrixMode(GL_MODELVIEW); //視野変換・モデリング変換モードへ
	glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
        case'k':
            tx=0;
            ty=0;
            xsve=0;
            ysve=0;
            break;
        case'b':
            ty=-600;
            tx=0;
            break;
        case't':
            ty=600;
            tx=0;
            break;
        case'u':
            xsve=10;
            ysve=10;
            break;
        case'j':
            ty=0;
            tx=0;
            break;
        case '\033':
            exit(0);
		case'a':
            if(xsb>=-20)
			xsb  -= 3;
		break;
		case'd':
            if(xsb<=20)
			xsb  += 3;
		break;
		case 's':
            if(ysb>=-20)
			ysb -= 3;
		break;
		case 'w':
            if(ysb<=20)
			ysb += 3;
		break;
        case'q':
        if(wall==0)
        wall=1;
        else wall=0;
        break;
		default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitWindowPosition(0, 0); //ウインドウを表示する画面上の左上の位置
	glutInitWindowSize(3000, 2000); //ウインドウのサイズ
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize); //関数resizeをコールバックに設定
	glutKeyboardFunc(keyboard);
   	glClearColor(0.0, 0.0, 0.0, 0.0);
        glutMainLoop();
    return 0;
}
