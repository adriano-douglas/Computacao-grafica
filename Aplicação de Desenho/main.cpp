#define GLUT_DISABLE_ATEXIT_HACK

/*
======== Aplicação de desenho =========

Adriano Douglas Reis Rosa
Daniel Henrique Silva

Versão 1.0

=======================================
*/

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

float windowSizeX = 800.0f, windowSizeY = 600.0f;

int r = 255, g = 0, b = 0;

int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

int cont_click = 0, desenhar = 1, limpar = 1;

float espessura = 1.0f;

void menu(){
    printf("\n");
    printf("                COMANDOS\n");
    printf("\n");
    printf("  PARA FAZER UMA LINHA DEVE CLICAR EM DOIS PONTOS\n");
    printf("\n");
    printf("  MENU DE CORES\n");
    printf("\n");
    printf("   VERMELHO:     1\n");
    printf("   VERDE:        2\n");
    printf("   AZUL:         3\n");
    printf("   PRETO:        4\n");
    printf("   AMARELO:      5\n");
    printf("   ROSA:         6\n");
    printf("   LARANJA:      7\n");
    printf("   CINZA:        8\n");
    printf("   MARROM:       9\n");
    printf("\n");
    printf("  PARA CONTROLAR A ESPESSURA DA LINHAS\n");
    printf("\n");
    printf("   PARA AUMENTAR +\n");
    printf("   PARA DIMINUIR -\n");
    printf("\n");
}

void desenhaLinha(int x1, int y1, int x2, int y2){
    //Configura a cor
    glColor3ub(r, g, b);

    //Configura a espessura da linha
    glLineWidth(espessura);

    // Desenha uma linha preenchida com a cor corrente
    glBegin(GL_LINES);
               glVertex2i(x1, y1);
               glVertex2i(x2, y2);
    glEnd();
}

//Função callback para desenho
void desenha(void)
{
    //Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da função: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, windowSizeX, 0.0f, windowSizeY);

    //printf("x1: %d y1: %d - x2: %d y2: %d - ct: %d - l: %d - d: %d - e: %.1f\n", x1, y1, x2, y2, cont_click, limpar, desenhar, espessura);

	if(desenhar) desenhaLinha(x1, y1, x2, y2);

	if(limpar) glClear(GL_COLOR_BUFFER_BIT);

    glutPostRedisplay();

	//Habilita a execução de comandos OpenGL
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
    if(key != 'a') desenhar = 0;
	if(limpar) limpar = 0;
    switch(key){
        case '+':
            espessura++;
            if(espessura > 30){
                espessura = 30;
            }
            break;
        case '-':
            espessura--;
            if(espessura < 1){
                espessura = 1;
            }
            break;
        case 'a':
            if(!desenhar){
                    desenhar = 1;
                    if(cont_click % 2 != 0) cont_click--;
            }
            limpar = 1;
            break;
        case '1':
            r = 255; g = 0; b = 0;
            break;
        case '2':
            r = 0; g = 255; b = 0;
            break;
        case '3':
            r = 0; g = 0; b = 255;
            break;
        case '4':
            r = 0; g = 0; b = 0;
            break;
        case '5':
            r = 255; g = 255; b = 0;
            break;
        case '6':
            r = 255; g = 0; b = 132;
            break;
        case '7':
            r = 255; g = 165; b = 0;
            break;
        case '8':
            r = 128; g = 128; b = 128;

            break;
        case '9':
            r = 165; g = 42; b = 42;
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y){
    y = windowSizeY - y;

    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_UP){
            cont_click++;
            if(cont_click % 2 != 0){
                x1 = x;
                y1 = y;
                desenhar = 0;
                limpar = 0;
            }else{
                x2 = x;
                y2 = y;
                desenhar = 1;
            }
        }
    }
}

//Inicializa parâmetros
void init (void)
{
    // Configura a cor de fundo como branca
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

//Principal
int main(void)
{
    setlocale(LC_ALL,"Portuguese");
    menu();

    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Configura o tamanho da janela
	glutInitWindowSize (windowSizeX, windowSizeY);

	//Configura a posição inicial da janela
	glutInitWindowPosition (100, 100);

	//Configura a janela
	glutCreateWindow("Aplicação de desenho");

	//Chama a função desenha
	glutDisplayFunc(desenha);

	//Callback de teclas normais
	glutKeyboardFunc(keyboard);

	//Callback de teclas especiais
	//glutSpecialFunc(specialKeyboard);

	//Callback do Mouse
	glutMouseFunc(mouse);

	//Inicializa o programa
	init();

	//Habilita o loop (máquina de estados)
	glutMainLoop();
}
