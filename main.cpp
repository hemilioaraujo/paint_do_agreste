#define GLUT_DISABLE_ATEXIT_HACK

/*
======== OpenGL ==================
Nairon Neri Silva
Vers�o 1.0
Programa exemplo de funcionalidade do
mouse e teclado
========================================
*/

// #include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


int r=255,g=255,b=255;
int windowSizeX = 600;
int windowSizeY = 600;
int pontos[2][3];
int contador_de_pontos = 0;

// Fun��o callback para desenho
void desenha(void)
{
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da fun��o: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, windowSizeX, 0.0f, windowSizeY);

	//Limpa todos os pixels com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(r, g, b);

    glPointSize(5);

    switch (contador_de_pontos){
        case 0:
            break;
        case 1:
            glBegin(GL_POINTS);
                glVertex2i(pontos[0][0], pontos[1][0]);
            glEnd();
            break;
        case 2:
            glBegin(GL_POINTS);
                glVertex2i(pontos[0][0], pontos[1][0]);
                glVertex2i(pontos[0][1], pontos[1][1]);
            glEnd();
            break;
        case 3:
            glBegin(GL_TRIANGLES);
                glVertex2i(pontos[0][0],pontos[1][0]);
                glVertex2i(pontos[0][1],pontos[1][1]);
                glVertex2i(pontos[0][2],pontos[1][2]);
            glEnd();
            break;
        default:
            break;
    }
    

    // glutPostRedisplay();

	//Habilita a execu��o de comandos OpenGL
	glFlush();
}




// Keyboard callback
void keyboard(unsigned char key, int x, int y)
{
   switch(key)
   {
        case 27:
            exit(0);
            break;
        case 'e':
            
            break;
        case 'R':
            if (r!=255){r+=1;}
        break;

        case 'r':
            if (r!=0){r-=1;}
        break;

        case 'G':
            if (g!=255){g+=1;}
        break;

        case 'g':
            if (g!=0){g-=1;}
        break;

        case 'B':
            if (b!=255){b+=1;}
        break;

        case 'b':
            if (b!=0){b-=1;}
        break;
   }
   printf("Cores: RGB (%d,%d,%d)\n",r,g,b);
   glutPostRedisplay();
}


void specialKeys(int key, int x, int y)
{
   switch(key)
   {
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
            // [x1][x2][x3]
            // [y1][y2][y3]
            switch (contador_de_pontos){
                case 0:
                    pontos[0][0] = x;
                    pontos[1][0] = y;
                    contador_de_pontos++;
                    break;
                case 1:
                    pontos[0][1] = x;
                    pontos[1][1] = y;
                    contador_de_pontos++;
                    break;
                case 2:
                    pontos[0][2] = x;
                    pontos[1][2] = y;
                    contador_de_pontos++;
                    break;
                default:
                    contador_de_pontos = 0;
                    break;
            }

            printf("x: %d\ny: %d\n\n", x, y);
        }
    }
    glutPostRedisplay();
}


//Inicializa par�metros
void init (void)
{
    // Configura a cor de fundo como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//Configura o tamanho da janela
	glutInitWindowSize (windowSizeX, windowSizeY);
	//Configura a posi��o inicial da janela
	glutInitWindowPosition (100, 100);
	//Configura a janela
	glutCreateWindow("Mouse e Teclado no OpenGL");
	//configura o teclado
	glutKeyboardFunc(keyboard);
	//teclas especiais
	glutSpecialFunc(specialKeys);
	//mouse
	glutMouseFunc(mouse);
	//Chama a fun��o desenha
	glutDisplayFunc(desenha);
	//Inicializa o programa
	init();
	//Habilita o loop (m�quina de estados)
	glutMainLoop();
}
