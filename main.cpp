#define GLUT_DISABLE_ATEXIT_HACK

/*
======== OpenGL ==================
GRUPO:
    Hemílio, Matheus Barbosa, Vitor Bastos
Versao:
    1.0
Aplicação:
    Paint do Agrest
========================================
*/

// #include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


int r=0,g=0,b=0;
int windowSizeX = 600;
int windowSizeY = 600;
int pontos[2][2];
int contador_de_pontos = 0;
int espessura_da_linha = 0;
int tamanho_do_ponto = 1;

// PROTOTIPOS
void init(void);

// Fun��o callback para desenho
void desenha(void){
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da fun��o: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, windowSizeX, 0.0f, windowSizeY);

	//Limpa todos os pixels com a cor de fundo
	// glClear(GL_COLOR_BUFFER_BIT);

    // glColor3ub(r, g, b);

    glPointSize(tamanho_do_ponto);
    glLineWidth(espessura_da_linha);

    switch (contador_de_pontos-1){
        case 0:
            glBegin(GL_POINTS);
                glColor3ub(r, g, b);
                glVertex2i(pontos[0][0], pontos[1][0]);
            glEnd();
            break;
        case 1:
            glBegin(GL_POINTS);
                glColor3ub(r, g, b);
                glVertex2i(pontos[0][1], pontos[1][1]);
            glEnd();
            glBegin(GL_LINES);
                glColor3ub(r, g, b);
                glVertex2i(pontos[0][0], pontos[1][0]);
                glVertex2i(pontos[0][1], pontos[1][1]);
            glEnd();
            contador_de_pontos = 0;
            break;
        default:
            break;
    }
    

    // glutPostRedisplay();
    
	//Habilita a execu��o de comandos OpenGL
	glFlush();
}


// Keyboard callback
void keyboard(unsigned char key, int x, int y){
   switch(key){
        case 27:
            exit(0);
            break;
        case 'a':
            init();
            printf("Limpando tela\n");
            break;
        case '+':
            espessura_da_linha++;
            // printf("Espessura: %d", espessura_da_linha);
            break;
        case '-':
            if (espessura_da_linha > 0){
                espessura_da_linha--;
                // printf("Espessura: %d", espessura_da_linha);
            }
            break;   
        case '1':
            r=255, g=0, b=0;
            break;
        case '2':
            r=0, g=255, b=0;
            break;
        case '3':
            r=0, g=0, b=255;
            break;
        case '4':
            r=0, g=0, b=0;
            break;
        case '5':
            r=255, g=255, b=0;
            break;
        case '6':
            r=255, g=0, b=255;
            break;
        case '7':
            r=255, g=165, b=0;
            break;
        case '8':
            r=128, g=128, b=128;
            break;
        case '9':
            r=75, g=54, b=33;
            break;
    }

//    printf("Cores: RGB (%d,%d,%d)\n",r,g,b);
   glutPostRedisplay();
}


void specialKeys(int key, int x, int y){
   switch(key){
      case GLUT_KEY_UP:
         //seta para cima
         printf("Seta para cima pressionada\n");
      break;
      case GLUT_KEY_DOWN:
         //seta para baixo
         printf("Seta para baixo pressionada\n");
      break;
      case GLUT_KEY_RIGHT:
         //seta para direita
         printf("Seta para a direita pressionada\n");
      break;
      case GLUT_KEY_LEFT:
         //seta para esquerda
         printf("Seta para a esquerda pressionada\n");
      break;
   }
   glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void mouse(int button, int state, int x, int y){
//Inverte mouse para que a origem fique no canto inferior esquerdo da janela
//por default, a origem � no canto superior esquerdo
y = windowSizeY - y;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            //a��es com o bot�o direito pressionado
            // [x1][x2]
            // [y1][y2]
            switch (contador_de_pontos){
                case 0:
                    pontos[0][0] = x;
                    pontos[1][0] = y;
                    // printf("Clique: %d\n", contador_de_pontos);
                    contador_de_pontos++;
                    break;
                case 1:
                    pontos[0][1] = x;
                    pontos[1][1] = y;
                    // printf("Clique: %d\n", contador_de_pontos);
                    contador_de_pontos++;
                    break;
                default:
                    break;
            }

            // printf("x: %d\ny: %d\n\n", x, y);
            
        }
    }
    // glutDisplayFunc(desenha);
    glutPostRedisplay();
}


//Inicializa par�metros
void init (void){
    // Configura a cor de fundo como preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //Limpa todos os pixels com a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

//Principal
int main(int argc, char **argv){
    glutInit(&argc, argv);
    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//Configura o tamanho da janela
	glutInitWindowSize (windowSizeX, windowSizeY);
	//Configura a posição inicial da janela
	glutInitWindowPosition (100, 100);
	//Configura a janela
	glutCreateWindow("Paint Do Agreste");
	//configura o teclado
	glutKeyboardFunc(keyboard);
	//teclas especiais
	glutSpecialFunc(specialKeys);
	//mouse
	glutMouseFunc(mouse);
	//Chama a função desenha
	glutDisplayFunc(desenha);
	//Inicializa o programa
	init();
	//Habilita o loop (máquina de estados)
	glutMainLoop();
}
