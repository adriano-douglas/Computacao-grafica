#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float altura = 400, largura = 400;

int quadrante = 0;

float l2 = -1.0, r2 = 10.0, b2 = -1.0, t2 = 10.0;
float l3 = -10.0, r3 = 1.0, b3 = -10.0, t3 = 1.0;
float l4 = -1.0, r4 = 10.0, b4 = -10.0, t4 = 1.0;

// Inicializa opengl
void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
}

void DesenhaBorda1(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-9.99, 9.99, 0.0);
        glVertex3f(9.99, 9.99, 0.0);
        glVertex3f(9.99, -9.99, 0.0);
        glVertex3f(-9.99, -9.99, 0.0);
    glEnd();
}

void DesenhaBorda2(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.3, 9.99, 0.0);
        glVertex3f(9.99, 9.99, 0.0);
        glVertex3f(9.99, 0.3, 0.0);
        glVertex3f(0.3, 0.3, 0.0);
    glEnd();
}

void DesenhaBorda3(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-9.99, -0.3, 0.0);
        glVertex3f(-0.3, -0.3, 0.0);
        glVertex3f(-0.3, -9.99, 0.0);
        glVertex3f(-9.99, -9.99, 0.0);
    glEnd();
}

void DesenhaBorda4(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.3, -0.3, 0.0);
        glVertex3f(9.99, -0.3, 0.0);
        glVertex3f(9.99, -9.99, 0.0);
        glVertex3f(0.3, -9.99, 0.0);
    glEnd();
}

// Eixos coordenados
void DesenhaEixos(){
    glLineWidth(1.0);
    glBegin(GL_LINES);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(-10.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(0.0, -10.0, 0.0);
        glVertex3f(0.0,  10.0, 0.0);
    glEnd();
}

void DesenhaObjetos(){
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(2.0, 2.0, 0.0);
        glVertex3f(8.0, 2.0, 0.0);
        glVertex3f(2.0, 8.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(2.0, -2.0, 0.0);
        glVertex3f(8.0, -2.0, 0.0);
        glVertex3f(2.0, -8.0, 0.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-2.0, -2.0, 0.0);
        glVertex3f(-8.0, -2.0, 0.0);
        glVertex3f(-2.0, -8.0, 0.0);
        glVertex3f(-8.0, -8.0, 0.0);
    glEnd();
}

void desenha(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define viewport das bordas
    glViewport ((int) 10, (int) 10, (int) 370, (int) 370);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    // Define e carrega a matriz ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(quadrante == 2) DesenhaBorda2();
    if(quadrante == 3) DesenhaBorda3();
    if(quadrante == 4) DesenhaBorda4();

    // Define viewport do canto superior esquerdo
    glViewport ((int) 10, (int) 200, (int) 180, (int) 180);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    //define e carrega a matriz ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //desenha os eixos
    DesenhaEixos();
    //desenha os objetos
    DesenhaObjetos();
    if(quadrante == 1)DesenhaBorda1();

    // Define viewport do canto superior direito
    glViewport ((int) 200, (int) 200, (int) 180, (int) 180);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(l2, r2, b2, t2, -10.0, 10.0);
    //define e carrega a matriz ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //desenha os eixos
    DesenhaEixos();
    //desenha os objetos
    DesenhaObjetos();

    // Define viewport do canto inferior esquerdo
    glViewport ((int) 10, (int) 10, (int) 180, (int) 180);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(l3, r3, b3, t3, -10.0, 10.0);
    //define e carrega a matriz ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //desenha os eixos
    DesenhaEixos();
    //desenha os objetos
    DesenhaObjetos();

    // Define viewport do canto inferior direito
    glViewport ((int) 200, (int) 10, (int) 180, (int) 180);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(l4, r4, b4, t4, -10.0, 10.0);
    //define e carrega a matriz ModelView
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //desenha os eixos
    DesenhaEixos();
    //desenha os objetos
    DesenhaObjetos();

    glutSwapBuffers();
    glutPostRedisplay();
}

void keyboard(int key, int x, int y){
    switch(key){
        case GLUT_KEY_DOWN:
            if(quadrante == 2 && b2 > -10){
                b2--;
                t2--;
            }else if(quadrante == 3 && b3 > -10){
                b3--;
                t3--;
            }else if(quadrante == 4 && b4 > -10){
                b4--;
                t4--;
            }
            break;
        case GLUT_KEY_UP:
            if(quadrante == 2 && t2 < 10){
                b2++;
                t2++;
            }else if(quadrante == 3 && t3 < 10){
                b3++;
                t3++;
            }else if(quadrante == 4 && t4 < 10){
                 b4++;
                 t4++;
            }
            break;
        case GLUT_KEY_LEFT:
            if(quadrante == 2 && l2 > -10){
                l2--;
                r2--;
            }else if(quadrante == 3 && l3 > -10){
                l3--;
                r3--;
            }else if(quadrante == 4 && l4 > -10){
                l4--;
                r4--;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(quadrante == 2 && r2 < 10){
                l2++;
                r2++;
            }else if(quadrante == 3 && r3 < 10){
                l3++;
                r3++;
            }else if(quadrante == 4 && r4 < 10){
                l4++;
                r4++;
            }
            break;
    }
}

//Mouse callback
void mouse(int button, int state, int x, int y){
    //Inverte mouse para que a origem fique no canto inferior esquerdo da janela
    // por default, a origem   no canto superior esquerdo
    y = 400 - y;
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN) {
            if(x < 200 && y < 200){
                quadrante = 3;
            }else if(x < 200 && y > 200){
                quadrante = 1;
            }else if(x > 200 && y > 200) {
                quadrante = 2;
            }else{
                quadrante = 4;
            }
        }
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (20,20);
   glutCreateWindow ("Viewport Test");
   init ();
   glutDisplayFunc(desenha);
   glutSpecialFunc(keyboard);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
