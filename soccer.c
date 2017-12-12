#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define rd 40.0
#define mx 1000.0
#define my 600.0
#define m_box 500 //グラム

double xsve,ysve,xsb,ysb=0;
double xsve=9.8;
double vertices[][3]={//四角形
	{0.0, 110, 0.0},
	{0.0, 0.0, 0.0},
	{110, 0.0, 0.0},
	{110, 110, 0.0}
};
double outflame[][3]={//四角形
	{-mx-rd, -my-rd, 0.0},
	{mx+rd, -my-rd, 0.0},
	{mx+rd, my+rd, 0.0},
	{-mx-rd,my+rd, 0.0}
};
double L_goleline[][3]={//ペナルティエリア(L)
    {-mx-rd,-my+50,0.0},
    {-mx-rd,my-50,0.0},
    {-mx+50,my-50,0.0},
    {-mx+50,-my+50,0.0}
};
double R_goleline[][3]={//  //   (R)
    {mx+rd,-my+50,0.0},
    {mx+rd,my-50,0.0},
    {mx-50,my-50,0.0},
    {mx-50,-my+50,0.0}
};
double centerline[][3]={//センターライン
    {0,my+rd,0.0},
    {0,-my-rd,0.0},
    {mx+rd,-my-rd,0.0},
    {mx+rd,my+rd,0.0}
};

int flg=0;
double tx = 0.0;
double ty = 0.0;
double tz = 0.0;
double rx = 0.0;
double ry = 0.0;
double rz = 0.0;

double rox = 0.0; //移動量
double roy = 0.0; //移動量
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

	//ここからモデリング変換
	glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化
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
	glutWireSphere(rd+50,360,360);
    glBegin(GL_LINE_LOOP);
    glEnd();
	glTranslated(tx, ty, tz); //平行移動
	glRotated(rx, 1.0, 0.0, 0.0); //X軸回転
	glRotated(ry, 0.0, 1.0, 0.0); //Y軸回転
	glRotated(rz, 0.0, 0.0, 1.0); //Z軸回転
	//ここからモデリング座標系
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	glutWireSphere(rd,50,50);
    glEnd();

	glTranslated(-tx, -ty,- tz); //平行移動
	glTranslated(rox, roy, tz); //平行移動
	glBegin(GL_LINE_LOOP); //プリミティブの指定は2Dの時と同じ
	for(int i=0; i < 4; i++)
		glVertex3dv(vertices[i]); //2dではなく3d
	glEnd();

	glFlush();
    //xsve*=0.993;
    //xsb*=1;
    ysve -=0.062;
    ysb -=0.042;
        if(flg<=0&&sqrt((ty-roy)*(ty-roy)+(tx-rox-50)*(tx-rox-50)) <= 40){
           xsve =-1* ((xsve+xsb/3)*2+0.0);
           ysve =-1* (ysve+ysb/3)*2+(flg%9);
           xsb = -1 * xsve/3;
           ysb = -1 * ysve/3;
           flg=10;
        }else{
            flg--;}
/********/
    if(tx>=500&&xsve>=0){
        xsve = -1*xsve*0.4;
    }
    else if(tx<=-500&&xsve<=0){
        xsve = -1*xsve*0.7;
    }
    if(ty>=500&&ysve>=0){
        ysve = -1*ysve*0.7;
    }else if(ty<=-500&&ysve<=0){
        ysve = -1*ysve*0.7;
        if(ysve >=-0.003&&ysve<=0.003){
        }
    }
    if(ty<=-499&&ysve>=-0.0072&&ysve<=0.0072){
        ysve *=0.7;}
    if(ty<=-499&&ysve>=-0.0002&&ysve<=0.0002){
           // ysve =0;
    }
/********/
/********/
    if(rox>=500-70&&xsb>=0){
        xsb = -1*xsb*0.5;
    }
    else if(rox<=-500-40&&xsb<=0){
        xsb = -1*xsb*0.5;
    }
    if(roy>=500&&ysb>=0){
        ysb = -1*ysb*0.7;
    }else if(roy<=-500&&ysb<=0){
        ysb = -1*ysb*0.7;
        if(ysb >=-0.003&&ysb<=0.003){
        }
    }
    if(roy<=-499&&ysb>=-0.0072&&ysb<=0.0072){
        ysve *=0.7;}
    if(roy<=-499&&ysb>=-0.0002&&ysb<=0.0002){
           // ysb =0;
    }
/********/

        tx +=xsve; 
        ty +=ysve;
        rox +=xsb;
        roy +=ysb;

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
        case 'u':
            xsve=900;
        case'j':
            ty=0;
            break;
        case '\033':
            exit(0);
		case 'a':
			xsb  -= 1.001;
		break;
		case 'd':
			xsb  += 1.001;
		break;
		case 's':
			ysb -= 1.001;
		break;
		case 'w':
			ysb += 1.001;
		break;
		default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(800, 1000); //ウインドウを表示する画面上の左上の位置
	glutInitWindowSize(1295, 744); //ウインドウのサイズ
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize); //関数resizeをコールバックに設定
	glutKeyboardFunc(keyboard);
   	glClearColor(0.0, 0.0, 0.0, 0.0);
        glutMainLoop();
    return 0;
}
