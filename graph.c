#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

GLuint texturaMario;

void inicializa() {
    glClearColor(1, 1, 1, 1);

    // habilita mesclagem de cores, para termos suporte a texturas (semi-)transparentes
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    texturaMario = SOIL_load_OGL_texture(
        "mario.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    if (texturaMario == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
}


void desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1, 1, 1);

    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, texturaMario);
    glBegin(GL_TRIANGLE_FAN);
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0, 0); glVertex3f(-1, -1,  0);
        glTexCoord2f(1, 0); glVertex3f( 1, -1,  0);
        glTexCoord2f(1, 1); glVertex3f( 1,  1,  0);
        glTexCoord2f(0, 1); glVertex3f(-1,  1,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void redimensiona(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
    }
}

void atualiza() {
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(400, 400);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Victor Franco Rezende");

   glutReshapeFunc(redimensiona);
   glutKeyboardFunc(teclado);
   glutDisplayFunc(desenha);
   glutIdleFunc(atualiza);

   inicializa();

   glutMainLoop();

   return 0;
}
