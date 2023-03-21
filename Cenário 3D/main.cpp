#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define BLOCO 20
#define TAM_CENARIO 2000
#define DIST_MOVIMENTO 5

GLfloat obs_x = 50, obs_z = 50;
GLfloat deslocamento_x = DIST_MOVIMENTO, deslocamento_z = 0;
GLfloat angle = 90, fAspect = 1, angulo_rotacao = 0;

GLfloat cor_material_trilho[] = { 0.12, 0.31, 0.51, 1.0 }; //cor usada no trilho
GLfloat cor_material_chao[] = { 0.4, 0.4, 0.4, 1.0 }; //cor usada no chão do cenário
GLfloat cor_material_teto[] = { 0.23, 0.23, 0.23, 1.0 }; //cor usada no teto do galpão
GLfloat cor_material_parede[] = { 0.3, 0.2, 0.1, 1.0 }; //cor usada na parede
GLfloat cor_material_banco[] = { 0, 0, 1, 1.0 }; //cor usada no banco
GLfloat cor_material_vagao[] = { 0.05, 0.21, 0.15, 1.0 }; //cor usada no vagão

int eixo_x = 0, eixo_y = 0, eixo_z = 0;

float altura = 0, alturaC = 0;

int colidiu = 0, andando = 0, andar = 1, escada1 = 0, escada2 = 0;

float velocidade = 0.5, velocidade2 = -0.5, posicaoZ = 1000, posicaoZ2 = 10, xs = 0, z = 0;

void espaco_cenario(){
    glPushMatrix();

    GLfloat cor_material_teste[] = { 0, 0.5, 0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teste);

    glPushMatrix();
        glTranslatef(825, -30, 0);
        glScalef(1650.0, 1.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(825, -30, 1650);
        glScalef(1650.0, 1.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-825, -30, 0);
        glScalef(1650.0, 1.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-825, -30, 1650);
        glScalef(1650.0, 1.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void salinha(){

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(850, 0, 300);

    // lateral esquerda
    glPushMatrix();
        glTranslatef(175.0, 0.0, -200.0);
        glScalef(150.0, 250.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // fundo
     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-137.5, 0.0, 249.5);
        glScalef(125.5, 250.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(137.5, 0.0, 249.5);
        glScalef(125.5, 250.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 100.0, 249.5);
        glScalef(150.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // lateral direita
    glPushMatrix();
        glTranslatef(175.0, 0.0, 200.0);
        glScalef(150.0, 250.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glTranslatef(850, 0, 300);

    //piso
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(125.0, 0.0, 54);
        glScalef(250.0, 400.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    // teto

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(182.5, 0.0, -130);
        glScalef(165.0, 430.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();

}

void galpao1(){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(700, 0, 300);

    // lateral esquerda
    glPushMatrix();
        glTranslatef(0.0, 0.0, -250.0);
        glScalef(500.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // recuo direita
    glPushMatrix();
        glTranslatef(-225.0, 0.0, 250.0);
        glScalef(50.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // fundo
     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-162.5, 0.0, 249.5);
        glScalef(175.5, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(162.0, 0.0, 249.5);
        glScalef(175.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 125.0, 249.5);
        glScalef(150.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // porta trilho
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-125.0, 0.0, -249.5);
        glScalef(250.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(200.0, 0.0, -249.5);
        glScalef(100.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(75.0, 125.0, -249.5);
        glScalef(150.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void teto1(){
    // teto galpao 1
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glTranslatef(700, 0, 300);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(89.0, 0.0, -155);
        glScalef(342.0, 520.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, -56.0, -155);
        glScalef(518.0, 410.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    //borda
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 250.0, -155);
        glScalef(520.0, 20.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(-250.0, 0.0, -155);
        glScalef(20.0, 520.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void piso1(){
    // Piso galpão 1
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glTranslatef(700, 0, 300);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, 54);
        glScalef(500.0, 500.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void segundo_andar_galpao1(){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(700, 200, 300);

    // lateral esquerda
    glPushMatrix();
        glTranslatef(0.0, 50.5, -220.0);
        glScalef(500.0, 200.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // lateral direita
    glPushMatrix();
        glTranslatef(225.0, 50.5, 250.0);
        glScalef(50.0, 200.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-75.0, 50.5, 250.0);
        glScalef(350.0, 200.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(150.0, 100.5, 250.0);
        glScalef(100.0, 100.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // fundo
     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-15.0, 0.0, 249.5);
        glScalef(470, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // porta trilho
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-125.0, 0.0, -249.5);
        glScalef(250.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(185.0, 0.0, -249.5);
        glScalef(70.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(75.0, 125.0, -249.5);
        glScalef(150.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void teto_segundo_andar_galpao1(){
    // teto segundo andar galpao 1
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glTranslatef(700, 200, 300);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 15.0, -155);
        glScalef(520.0, 490.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void galpao2(){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(724, 0, 800);

    // lateral direita
    glPushMatrix();
        glTranslatef(0.0, 0.0, 249.5);
        glScalef(450.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // fundo
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 0.0, 225.5);
        glScalef(500.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // porta trilho
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-162.0, 0.0, -224.5);
        glScalef(175.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(162.0, 0.0, -224.5);
        glScalef(175.0, 300.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 125.0, -224.5);
        glScalef(150.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void teto2(){
    // teto galpao 2
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glTranslatef(724, 0, 800);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -155);
        glScalef(470.0, 520.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void piso2(){
    //Piso galpao 2
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glTranslatef(724, 0, 800);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, 54);
        glScalef(450.0, 500.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void trilho(int x, int z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_trilho);

   glTranslatef(x, 0, z);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, 52);
        glScalef(70.0, 1200.0, 15.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void lateral_escada(float d_x){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    // sustentação rampa
    glPushMatrix();
        glTranslatef(d_x, -10, -49);
        glScalef(1.0, 19.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(d_x, 12.5, -25.8);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

        glPushMatrix();
        glTranslatef(d_x, 35.5, -2.6);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(d_x, 59, 20.5);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // encosto rampa
    glPushMatrix();
        glRotatef(-45, 1, 0, 0);
        glTranslatef(d_x, 34.5, 14);
        glScalef(1.0, 1.0, 100.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void lateral_base_escada(float d_x){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    // sustentação base
    glPushMatrix();
        glTranslatef(d_x, 10, 0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // encosto base
    glPushMatrix();
        glTranslatef(d_x, 20, 0);
        glScalef(1.0, 1.0, 40.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void lateral_plataforma(float d_x, float d_y, float d_z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    // sustentação base
    glPushMatrix();
        glTranslatef(d_x, d_y, d_z);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // encosto base
    glPushMatrix();
        glTranslatef(d_x, d_y+10, d_z);
        glScalef(1.0, 1.0, 40.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void escada(float x, float y, float z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(x, y, z);

    // rampa
    glPushMatrix();
        glRotatef(-45, 1, 0, 0);
        glTranslatef(0.0, 20.0, 0.0);
        glScalef(50.0, 1.0, 100.0);
        glutSolidCube(1);
    glPopMatrix();

    // laterais

    lateral_escada(-24.5);
    lateral_escada(24.5);

    glPopMatrix();
}

void base_escada(float x, float y, float z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glTranslatef(x, y, z);

    // base
    glPushMatrix();
        glScalef(50.0, 1.0, 40.0);
        glutSolidCube(1);
    glPopMatrix();

    // laterais
    lateral_base_escada(24.5);
    lateral_base_escada(-24.5);

    glPopMatrix();
}

void escada_completa(float x, float z, float angulo){
    glPushMatrix();

        glRotatef(angulo, 0, 1, 0);
        glTranslatef(x, 0, z);

        // escadas isoladas
        escada(0, 110, 128.5);
        escada(0, 39.7, 18.2);
        escada(0, -30.6, -92.1);

        // bases isoladas
        base_escada(0, 89, 59);
        base_escada(0, 18.8, -51.3);

    glPopMatrix();
}

void banco(int x, int z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_banco);

    glRotatef(-90, 0, 1, 0);
    glTranslatef(x, -40, z);

    // encosto
    glPushMatrix();
        glRotatef(-5, 1, 0, 0);
        glTranslatef(0.0, 21, -3.5);
        glScalef(60.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // assento
    glPushMatrix();
        glTranslatef(0.0, 10.5, 0.0);
        glScalef(60.0, 1.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    // em baixo do assento
    glPushMatrix();
        glTranslatef(0.0, 8.0, 0.0);
        glScalef(60.0, 4.0, 2.0);
        glutSolidCube(1);
    glPopMatrix();

    // pés
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(20.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void banco_2_andar(int x, int z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_banco);

    glRotatef(-90, 0, 1, 0);
    glTranslatef(x, 170, z);

    // encosto
    glPushMatrix();
        glRotatef(-5, 1, 0, 0);
        glTranslatef(0.0, 21, -3.5);
        glScalef(60.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // assento
    glPushMatrix();
        glTranslatef(0.0, 10.5, 0.0);
        glScalef(60.0, 1.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    // em baixo do assento
    glPushMatrix();
        glTranslatef(0.0, 8.0, 0.0);
        glScalef(60.0, 4.0, 2.0);
        glutSolidCube(1);
    glPopMatrix();

    // pés
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(20.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20.0, 0.0, 0.0);
        glScalef(1.0, 20.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void pilastra(int x, int z){
    glPushMatrix();

    glTranslatef(x, 0, z);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(1.0, 17.65, 1.0);
        glutSolidCube(17);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glPushMatrix();
        glTranslatef(0, -40.0, 0);
        glScalef(1.0, 1.0, 1.0);
        glutSolidCube(20);
    glPopMatrix();

    glPopMatrix();
}

void pilastra_de_fora(int x,float y, int z){
    glPushMatrix();

    glTranslatef(x, 0, z);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glPushMatrix();
        glTranslatef(0, -0.3, 0);
        glScalef(2.0, y, 2.0);
        glutSolidCube(17);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glPushMatrix();
        glTranslatef(0, -40.0, 0);
        glScalef(2.0, 2.0, 2.0);
        glutSolidCube(20);
    glPopMatrix();

    glPopMatrix();
}

void plataforma(){
    // plataforma
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glTranslatef(180, 0, 225);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -155);
        glScalef(522.0, 150.0, 10.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void esacada_interna(){
    // plataforma
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glTranslatef(479.5, 0, 500);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -48);
        glScalef(58.0, 100.0, 5.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        escada(525,-30, -560);
        escada(525,0, -530);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        escada(-475,71, 558);
        escada(-475,110.5, 597.5);
    glPopMatrix();

}

void mini_galpao_segundo_andar_galpao2(){
    glPushMatrix();

    glTranslatef(800, 230, 900);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    // lateral esquerda
    glPushMatrix();
        glTranslatef(50.0, 0.0, -75.0);
        glScalef(50.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50.0, 0.0, -75.0);
        glScalef(50.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 50.0, -75.0);
        glScalef(50.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // lateral direita
    glPushMatrix();
        glTranslatef(0.0, 0.0, 75.0);
        glScalef(150.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // fundo
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(50.0, 0.0, 74.5);
        glScalef(50.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-50.0, 0.0, 74.5);
        glScalef(50.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 50.0, 74.5);
        glScalef(50.0, 50.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // frente trilho
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0.0, 0.0, -74.5);
        glScalef(150.0, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // segundo andar
    glPushMatrix();
        glTranslatef(0.0, 250.0, 0.0);
        glScalef(1.0, 3.5, 1.0);
        glutSolidCube(100);
    glPopMatrix();

    // antena
    glPushMatrix();
        glTranslatef(0.0, 500.0, 0.0);
        glScalef(1.0, 10, 1.0);
        glutSolidCube(15);
    glPopMatrix();

    // teto 1
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_teto);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -75.0);
        glScalef(155.0, 155.0, 30.0);
        glutSolidCube(1);
    glPopMatrix();

    // teto 2
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -300.0);
        glScalef(180.0, 180.0, 50.0);
        glutSolidCube(1);
    glPopMatrix();

    // teto 3
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 0.0, -425.0);
        glScalef(155.0, 155.0, 25.0);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void vagoes(int x, int z){
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_vagao);

    glTranslatef(x, 0, z);

    glPushMatrix();
        glTranslatef(0.0, -30.0, 52);
        glScalef(50.0, 100.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(0.0, -30.0, 202);
        glScalef(50.0, 100.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

// porta do vagao esquerda
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-76.5, 0.0, 25);
        glScalef(50, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-176.5, 0.0, 25);
        glScalef(50, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    // porta do vagÃ£o direita

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-76.5, 0.0, -25);
        glScalef(50, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-176.5, 0.0, -25);
        glScalef(50, 150.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    //piso e teto

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 127.0, 42);
        glScalef(55.0, 155.0, 5.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.0, 127.0, -75);
        glScalef(55.0, 155.0, 5.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10.0, -10.0, 50);
        glScalef(10.0, 10.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10.0, -10.0, 50);
        glScalef(10.0, 10.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

        glPushMatrix();
        glTranslatef(10.0, -10.0, 204);
        glScalef(10.0, 10.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10.0, -10.0, 204);
        glScalef(10.0, 10.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();


    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(-75, -40.0, 28);
            glScalef(10.0, 10.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(-175, -40.0, 28);
            glScalef(10.0, 10.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(-75, -40.0, -28);
            glScalef(10.0, 10.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(-175, -40.0, -28);
            glScalef(10.0, 10.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();


    glPopMatrix();

}

int colisao(float ca_x, float ca_z, float centro_x, float centro_z, float tam_x, float tam_z){
    float x_min = centro_x - (tam_x / 2) - 5;
    float x_max = centro_x + (tam_x / 2) + 5;

    float z_min = centro_z - (tam_z / 2) - 5;
    float z_max = centro_z + (tam_z / 2) + 5;

    int cx = 0, cz = 0;

    if(ca_x >= x_min && ca_x <= x_max){
        cx = 1;
    }

    if(ca_z >= z_min && ca_z <= z_max){
        cz = 1;
    }

    if(cx && cz){
        colidiu = 1;
        obs_x = xs;
        obs_z = z;
        altura = alturaC;
        colidiu = 0;
    }
}

void verifica_colisoes(){
    // galpao 1
    colisao(obs_x, obs_z, 1000, 350, 500, 1); // lateral esquerda
    colisao(obs_x, obs_z, 775, 850, 50, 1); // recuo direita
    colisao(obs_x, obs_z, 1249.5, 437.5, 1, 175.5); // fundo 1
    colisao(obs_x, obs_z, 1249.5, 762, 1, 175.5); // fundo 2
    colisao(obs_x, obs_z, 750.5, 400, 1, 100); // porta trilho 1
    colisao(obs_x, obs_z, 750.5, 725, 1, 250); // porta trilho 2

    // segundo andar galpao 1
    if(andar == 2){
        colisao(obs_x, obs_z, 1000, 380, 500, 1); // lateral esquerda
        colisao(obs_x, obs_z, 1225, 850, 50, 1); // lateral direita 1
        colisao(obs_x, obs_z, 925, 850, 350, 1); // lateral direita 2
    }

    // galpao 2
    colisao(obs_x, obs_z, 1024, 1349.5, 450, 1); // lateral direita
    colisao(obs_x, obs_z, 1249.5, 1100, 1, 500); // fundo
    colisao(obs_x, obs_z, 799.5, 1262, 1, 175); // porta trilho 1
    colisao(obs_x, obs_z, 799.5, 938, 1, 175); // porta trilho 2

    // segundo andar galpao 2
    if(andar == 2){
        colisao(obs_x, obs_z, 799.5, 1100, 1, 150); // porta trilho 3

        // mini galpao
        colisao(obs_x, obs_z, 1150, 1125, 50, 1); // lateral esquerda 1
        colisao(obs_x, obs_z, 1050, 1125, 50, 1); // lateral esquerda 2
        colisao(obs_x, obs_z, 1100, 1275, 150, 1); // lateral direita
        colisao(obs_x, obs_z, 1174.5, 1150, 1, 50); // fundo 1
        colisao(obs_x, obs_z, 1174.5, 1250, 1, 50); // fundo 2
        colisao(obs_x, obs_z, 1025.5, 1200, 1, 150); // frente trilho

        // lateral plataforma
        colisao(obs_x, obs_z, 247.5, 599.5, 56.5, 1); // lateral 1
        colisao(obs_x, obs_z, 247.5, 450.5, 56.5, 1); // lateral 2
        colisao(obs_x, obs_z, 474.5, 599.5, 301, 1); // lateral 3
        colisao(obs_x, obs_z, 474.5, 450.5, 301, 1); // lateral 4
        colisao(obs_x, obs_z, 712.5, 599.5, 75.5, 1); // lateral 5
        colisao(obs_x, obs_z, 712.5, 450.5, 75.5, 1); // lateral 6
        colisao(obs_x, obs_z, 220, 525, 1, 150); // lateral 7
    }

    if(andar == 1){
        // salinha
        colisao(obs_x, obs_z, 1325, 400, 150, 1); // lateral esquerda
        colisao(obs_x, obs_z, 1325, 800, 150, 1); // lateral direita
        colisao(obs_x, obs_z, 1399.5, 737.5, 1, 125.5); // fundo 1
        colisao(obs_x, obs_z, 1399.5, 462.5, 1, 125.5); // fundo 2

        // pilastras dentro
        colisao(obs_x, obs_z, 900, 500, 17, 17); // pilastra 1
        colisao(obs_x, obs_z, 1100, 500, 17, 17); // pilastra 2
        colisao(obs_x, obs_z, 1100, 900, 17, 17); // pilastra 3
        colisao(obs_x, obs_z, 900, 900, 17, 17); // pilastra 4
        colisao(obs_x, obs_z, 1100, 1200, 17, 17); // pilastra 5
        colisao(obs_x, obs_z, 900, 1200, 17, 17); // pilastra 6

        // pilastras fora
        colisao(obs_x, obs_z, 300, 250, 34, 34); // pilastra 1
        colisao(obs_x, obs_z, 650, 250, 34, 34); // pilastra 2
        colisao(obs_x, obs_z, 300, 800, 34, 34); // pilastra 3
        colisao(obs_x, obs_z, 650, 800, 34, 34); // pilastra 4
        colisao(obs_x, obs_z, 300, 360, 34, 34); // pilastra 5
        colisao(obs_x, obs_z, 650, 360, 34, 34); // pilastra 6
        colisao(obs_x, obs_z, 300, 690, 34, 34); // pilastra 7
        colisao(obs_x, obs_z, 650, 690, 34, 34); // pilastra 8
        colisao(obs_x, obs_z, 300, 470, 34, 34); // pilastra 9
        colisao(obs_x, obs_z, 650, 470, 34, 34); // pilastra 10
        colisao(obs_x, obs_z, 300, 580, 34, 34); // pilastra 11
        colisao(obs_x, obs_z, 650, 580, 34, 34); // pilastra 12
    }

    // espaco do cenario
    colisao(obs_x, obs_z, 825, 0, 1650, 1); // lateral esquerda
    colisao(obs_x, obs_z, 825, 1650, 1650, 1); // lateral direita
    colisao(obs_x, obs_z, 0, 825, 1, 1650); // frente
    colisao(obs_x, obs_z, 1650, 825, 1, 1650); // fundo

    if(escada1){
        colisao(obs_x, obs_z, 275, 305, 1, 300); // lado direito
        colisao(obs_x, obs_z, 325, 305, 1, 300); // lado esquerdo
    }

    if(escada2){
        colisao(obs_x, obs_z, 625, 305, 1, 300); // lado direito
        colisao(obs_x, obs_z, 675, 305, 1, 300); // lado esquerdo
    }
}

void configura_iluminacao(){
    //configura a cor branca como luz ambiente
    GLfloat luzAmbiente[4] = {1.0,1.0,1.0,1.0};

    //configura luz difusa
    GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};

    //configura brilho
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};

    //configura a posição da luz
    GLfloat posicaoLuz[4] = {0.0, 1000.0, 0.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4] = {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS, especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

void desenha(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configura_iluminacao();

    glLoadIdentity();

    gluLookAt(obs_x, altura, obs_z, obs_x+deslocamento_x, altura,obs_z+deslocamento_z, 0,1,0);

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_chao);

    glBegin (GL_QUADS);
        glVertex3f(-TAM_CENARIO, -50, -TAM_CENARIO);
        glVertex3f(-TAM_CENARIO, -50, TAM_CENARIO);
        glVertex3f(TAM_CENARIO, -50, TAM_CENARIO);
        glVertex3f(TAM_CENARIO, -50, -TAM_CENARIO);
    glEnd();

    espaco_cenario();

    glPushMatrix();

    glTranslatef(300, 0, 300);

    galpao1();

    segundo_andar_galpao1();

    teto1();

    teto2();

    piso1();

    piso2();

    trilho(100, 650);

    trilho(230, 650);

    teto_segundo_andar_galpao1();

    galpao2();

    mini_galpao_segundo_andar_galpao2();

    salinha();

    esacada_interna();

    //bando galpao 2
    banco(750, -675);
    banco(850, -675);
    banco(950, -675);
    banco(750, -725);
    banco(850, -725);
    banco(950, -725);
    banco(750, -775);
    banco(850, -775);
    banco(950, -775);
    banco(750, -825);
    banco(850, -825);
    banco(950, -825);

    // banco galpao 1
    banco(500, -675);
    banco(400, -675);
    banco(300, -675);
    banco(500, -725);
    banco(400, -725);
    banco(300, -725);
    banco(500, -775);
    banco(400, -775);
    banco(300, -775);
    banco(500, -825);
    banco(400, -825);
    banco(300, -825);

    //banco 2andar
    banco_2_andar(350, -675);
    banco_2_andar(250, -675);
    banco_2_andar(150, -675);
    banco_2_andar(350, -725);
    banco_2_andar(250, -725);
    banco_2_andar(150, -725);
    banco_2_andar(350, -775);
    banco_2_andar(250, -775);
    banco_2_andar(150, -775);
    banco_2_andar(350, -825);
    banco_2_andar(250, -825);
    banco_2_andar(150, -825);

    pilastra(600, 200);
    pilastra(800, 200);
    pilastra(800, 600);
    pilastra(600, 600);
    pilastra(800, 900);
    pilastra(600, 900);

    pilastra_de_fora(0, 2.3, -50);
    pilastra_de_fora(350, 2.3, -50);
    pilastra_de_fora(0, 2.3, 500);
    pilastra_de_fora(350, 2.3, 500);

    pilastra_de_fora(0, 10.5, 60);
    pilastra_de_fora(350, 10.5, 60);
    pilastra_de_fora(0, 10.5, 390);
    pilastra_de_fora(350, 10.5, 390);

    pilastra_de_fora(0, 18, 170);
    pilastra_de_fora(350, 18, 170);
    pilastra_de_fora(0, 18, 280);
    pilastra_de_fora(350, 18, 280);

    plataforma();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        lateral_plataforma(-299.5,170,-59.5);
        lateral_plataforma(-299.5,170,-44);
        lateral_plataforma(-299.5,170,44);
        lateral_plataforma(-299.5,170,80);
        lateral_plataforma(-299.5,170,116);
        lateral_plataforma(-299.5,170,152);
        lateral_plataforma(-299.5,170,188);
        lateral_plataforma(-299.5,170,224);
        lateral_plataforma(-299.5,170,260);
        lateral_plataforma(-299.5,170,296);
        lateral_plataforma(-299.5,170,305);
        lateral_plataforma(-299.5,170,395);
        lateral_plataforma(-299.5,170,430.5);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        lateral_plataforma(-150.5,170,-59.5);
        lateral_plataforma(-150.5,170,-44);
        lateral_plataforma(-150.5,170,44);
        lateral_plataforma(-150.5,170,80);
        lateral_plataforma(-150.5,170,116);
        lateral_plataforma(-150.5,170,152);
        lateral_plataforma(-150.5,170,188);
        lateral_plataforma(-150.5,170,224);
        lateral_plataforma(-150.5,170,260);
        lateral_plataforma(-150.5,170,296);
        lateral_plataforma(-150.5,170,305);
        lateral_plataforma(-150.5,170,395);
        lateral_plataforma(-150.5,170,430.5);
    glPopMatrix();

        lateral_plataforma(-80,170,280);
        lateral_plataforma(-80,170,170);
        lateral_plataforma(-80,170,210);
        lateral_plataforma(-80,170,240);

    escada_completa(0, 0, 0);
    escada_completa(0, -450, 180);
    escada_completa(-350, -450, 180);
    escada_completa(350, 0, 0);

    vagoes(100, posicaoZ2);
    vagoes(230, posicaoZ);

    glPopMatrix();

    if(posicaoZ >= 1000 || posicaoZ <= 10) velocidade = -velocidade;
    if(posicaoZ2 >= 1000 || posicaoZ2 <= 10) velocidade2 = -velocidade2;

    posicaoZ += velocidade;
    posicaoZ2 += velocidade2;

    if(obs_x > 275 && obs_x < 325 && obs_z > 165 && obs_z < 445){
        escada1 = 1;
    }else{
        escada1 = 0;
    }

    if(obs_x > 625 && obs_x < 675 && obs_z > 165 && obs_z < 445){
        escada2 = 1;
    }else{
        escada2 = 0;
    }

    if(altura < 0) altura = 0;
    if(altura > 0){
        andar = 2;
    }else{
        andar = 1;
    }

    if(andando) verifica_colisoes();

    andando = 0;

    //printf("%f\n", altura);

    glLineWidth(5.0);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(eixo_x, eixo_y, eixo_z);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Special_Keys(int key, int x, int y)
{
    float r;

    if(key == GLUT_KEY_DOWN){
        printf("%f -- %f\n", obs_x, obs_z);

        andando = 1;

        if(!colidiu){
            xs = obs_x;
            z = obs_z;
            alturaC = altura;
        }

        if(escada1 || escada2 && !colidiu){
            if(angulo_rotacao >= 0 && angulo_rotacao < 180){
                altura -= 3.6;
            }else{
                altura += 3.6;
            }
        }

        if(!colidiu){
            obs_x -= deslocamento_x;
            obs_z -= deslocamento_z;
        }
    }

    else if(key == GLUT_KEY_UP){
        printf("%f -- %f\n", obs_x, obs_z);

        andando = 1;

        if(!colidiu){
            xs = obs_x;
            z = obs_z;
            alturaC = altura;
        }

        if(escada1 || escada2 && !colidiu){
            if(angulo_rotacao >= 180 && angulo_rotacao < 360){
                altura -= 3.6;
            }else{
                altura += 3.6;
            }
        }

        if(!colidiu){
            obs_x += deslocamento_x;
            obs_z += deslocamento_z;
        }
    }

    switch (key)
    {
        case GLUT_KEY_LEFT:
            angulo_rotacao = angulo_rotacao - 10;
            if(angulo_rotacao < 0) angulo_rotacao +=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x =  cos(r) * DIST_MOVIMENTO;
                deslocamento_z =  sin(r) * DIST_MOVIMENTO;

                printf("%f\n\n", angulo_rotacao);
            break;

        case GLUT_KEY_RIGHT:
            angulo_rotacao = angulo_rotacao + 10;
            if(angulo_rotacao >= 360) angulo_rotacao -=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x = cos(r) * DIST_MOVIMENTO;
                deslocamento_z = sin(r) * DIST_MOVIMENTO;

                printf("%f\n\n", angulo_rotacao);
            break;
 }
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case  'x': //sair
            eixo_x--;
            break;
        case  'X': //sair
            eixo_x++;
            break;
        case  'y': //sair
            eixo_y--;
            break;
        case  'Y': //sair
            eixo_y++;
            break;
        case  'z': //sair
            eixo_z--;
            break;
        case  'Z': //sair
            eixo_z++;
            break;


        case  '+': //sair
            altura++;
            break;
        case  '-': //sair
            altura--;
            break;


        case  27: //sair
            exit(0);
            break;
    }

    printf("%d %d %d\n", eixo_x, eixo_y, eixo_z);

}

void init(void)
{

    glClearColor(0.53, 0.81, 0.92, 0.0);

    glShadeModel (GL_SMOOTH);

    //habilita luz 0
    glEnable(GL_LIGHT0);
    //utiliza cor do objeto como material
    glEnable(GL_COLOR_MATERIAL );
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    //habilita luz
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle,fAspect,0.5,TAM_CENARIO);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cenário 3D");
    //habilita tela cheia
    glutFullScreen();
    init();
    glutDisplayFunc(desenha);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special_Keys);
    glutMainLoop();
}
