#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float velocidadeX = 0.15;
float velocidadeY = 0.15;

float x1 = 500, y1 = 300, ye = 0, yd = 0;

int xqe = 10, yqe = 320 + ye;
int xqd = 990, yqd = 320 + yd;
float xb = 0, yb = 0;

float centroE, centroD, centroB;

int pontos1 = 0, pontos2 = 0;

char texto[3], texto2[3];

int terminou = 2;

void desenhaCenario(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
               glVertex2i(10, 580);
               glVertex2i(10, 560);
               glVertex2i(990, 560);
               glVertex2i(990, 580);
    glEnd();

    glBegin(GL_QUADS);
               glVertex2i(10, 40);
               glVertex2i(10, 20);
               glVertex2i(990, 20);
               glVertex2i(990, 40);
    glEnd();

    glPointSize(20);
    glBegin(GL_POINTS);
    for(int i = 30; i <= 580; i += 30){
        glVertex2i(500, i);
    }
    glEnd();
}

void desenhaQuadradoEsquerdo(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
               glVertex2i(10, 400);
               glVertex2i(10, 320);
               glVertex2i(30, 320);
               glVertex2i(30, 400);
    glEnd();
}

void desenhaQuadradoDireito(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
               glVertex2i(970, 400);
               glVertex2i(970, 320);
               glVertex2i(990, 320);
               glVertex2i(990, 400);
    glEnd();
}

void desenhaBola(){
    glColor3ub(0, 255, 0);
    glBegin(GL_QUADS);
                glVertex2i(30, 40);
                glVertex2i(30, 60);
                glVertex2i(50, 60);
                glVertex2i(50, 40);
    glEnd();
}

float modulo(float n){
    if(n < 0) return -n;
    return n;
}

int inteiro(float n){
    return (int) n;
}

void DesenhaTexto(char *string, int x, int y){
  	glPushMatrix();
        glColor3ub(255, 255, 255);
        // Posição no universo onde o texto será colocado
        glRasterPos2f(x, y);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
	glPopMatrix();
}

void finalizarJogo(int ganhador){
    if(ganhador == 1){
        DesenhaTexto("Jogador 1 foi o vencedor!", 365, 400);
    }else if(ganhador == 2){
        DesenhaTexto("Jogador 2 foi o vencedor!", 365, 400);
    }
    DesenhaTexto("Pressione F para jogar ou 0 para sair", 300, 300);
    DesenhaTexto("Teclas Jogador 1: W para subir e S para descer", 50, 150);
    DesenhaTexto("Teclas Jogador 2: seta para cima para subir e seta para baixo para descer", 50, 100);
}

void redefinirParametros(){
    velocidadeX = 0.15;
    velocidadeY = 0.15;
    x1 = 500;
    y1 = 300;
    ye = 0;
    yd = 0;
    xqe = 10;
    yqe = 320 + ye;
    xqd = 990;
    yqd = 320 + yd;
    xb = 0;
    yb = 0;
    pontos1 = 0;
    pontos2 = 0;
    terminou = 0;
    glutPostRedisplay();
}

//Função callback para desenho
void desenha(void)
{
    //Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da função: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, 1000.0f, 0.0f, 600.0f);

	//Limpa todos os pixels com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	if(!terminou){

	glPushMatrix();
        desenhaCenario();
    glPopMatrix();

    itoa(pontos1, texto, 10);
    itoa(pontos2, texto2, 10);

    DesenhaTexto(texto, 400, 520);
    DesenhaTexto(texto2, 590, 520);

    glPushMatrix();
        glTranslatef(0, ye, 0);
        desenhaQuadradoEsquerdo();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, yd, 0);
        desenhaQuadradoDireito();
    glPopMatrix();

    //Bola
    glPushMatrix();
        glTranslatef(x1, y1, 0);
        desenhaBola();
    glPopMatrix();

    x1 += velocidadeX;
    y1 += velocidadeY;

    xb = x1 + 40;
    yb = y1 + 40;

    centroE = yqe + 40;
    centroD = yqd + 40;
    centroB = yb + 10;

    if(yb >= 540 || yb <= 40){
        velocidadeY = -velocidadeY;
    }

    if(inteiro(xb) == 40 && modulo(centroE - centroB) <= 60){
        velocidadeX = -velocidadeX;
    }

    if(inteiro(xb) == 960 && modulo(centroD - centroB) <= 60){
        velocidadeX = -velocidadeX;
    }

    if(inteiro(xb) == 1000){
        pontos1++;
        x1 = 500;
        y1 = 300;
    }else if(inteiro(xb) == 0){
        pontos2++;
        x1 = 500;
        y1 = 300;
    }

    if(pontos1 == 10 || pontos2 == 10){
        terminou = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        if(pontos1 == 10) finalizarJogo(1);
        if(pontos2 == 10) finalizarJogo(2);
    }

    glutPostRedisplay();

	}else if(terminou == 2){
        finalizarJogo(0);
	}

	//Habilita a execução de comandos OpenGL
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'w':
            if(yqe < 480){
                yqe += 10;
                ye += 10;
            }
            break;
        case 's':
            if(yqe > 40){
                yqe -= 10;
                ye -= 10;
            }
            break;
        case 'f':
            if(terminou){
                redefinirParametros();
            }
            break;
        case '0':
            exit(0);
            break;
        default:
            break;
    }
}

void specialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_UP){
        if(yqd < 480){
            yqd += 10;
            yd += 10;
        }
    }

    if (key == GLUT_KEY_DOWN){
        if(yqd > 40){
            yqd -= 10;
            yd -= 10;
        }
    }
}

//Inicializa parâmetros
void init (void)
{
    // Configura a cor de fundo como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//Principal
int main(void)
{
    srand(time(NULL));
    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Configura o tamanho da janela
	glutInitWindowSize (1000, 600);

	//Configura a posição inicial da janela
	glutInitWindowPosition (100, 100);

	//Configura a janela
	glutCreateWindow("Jogo Pong");

	//Chama a função desenha
	glutDisplayFunc(desenha);

	//Callback de teclas normais
	glutKeyboardFunc(keyboard);

	//Callback de teclas especiais
	glutSpecialFunc(specialKeyboard);

	//Inicializa o programa
	init();

	//Habilita o loop (máquina de estados)
	glutMainLoop();
}