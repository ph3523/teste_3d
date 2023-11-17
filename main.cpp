#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "cores.h"
#include "primitivas.h"

float angleX = 0.0f;
float angleY = 0.0f;
GLfloat z = -50.0f;
GLfloat x = 0.0f;
GLfloat y = 0.0f;

void redimensiona(int w, int h);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void desenha();
void init();


static float angulo = 0.0f;

unsigned int esferaID[3];
unsigned int pontosID[1];

void redimenciona(int w, int h)
{
    glViewport(0, 0, w, h);

    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const float translationSpeed = 1.0f;

    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angleX += translationSpeed;
    }
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angleX -= translationSpeed;
    }
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angleY += translationSpeed;
    }
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angleY -= translationSpeed;
    }
    else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        y += translationSpeed;
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        y -= translationSpeed;
    }
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        x -= translationSpeed;
    }
    else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        x += translationSpeed;
    }
}


void desenha()
{
    glLoadIdentity();
    // z += 0.1;
    // if(z > 0.0)
    //     z = -100.0;

    glPushMatrix();
    glTranslatef(-30.0, 0.0, -50.0);
    glRotatef(angulo, 1.0, 1.0, 0.0);
    // glRotated(angleY, 0.0, 1.0, 0.0);
    glCallList(esferaID[0]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angleY, 1.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 1.0, 0.0);
    glCallList(esferaID[1]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.0, 0.0, -50.0);
    glRotatef(angulo, 1.0, 1.0, 0.0);
    glCallList(esferaID[2]);
    glPopMatrix();

    // angulo += 0.1;
    // if (angulo > 360.0)
    //     angulo = 0.0;



        angleX += 0.1;
        angleY += 0.1;
    if (angleX && angleY > 360.0)
        angleX = 0.0;
        angleY = 0.0;
}

void init()
{
    // glClearColor(0.0, 0.15, 0.25, 1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    esferaID[0] = glGenLists(3);
    esferaID[1] = esferaID[0] + 1;
    esferaID[2] = esferaID[0] + 2;

    pontosID[0] = glGenLists(1);

    desenhaEsfera(esferaID[0], verde, 10.0, 20.0, 20.0);
    desenhaEsfera(esferaID[1], laranja, 5.0, 20.0, 20.0);
    desenhaEsfera(esferaID[2], azul, 8.0, 20.0, 20.0);
    desenhaLinha(pontosID[0], vermelho, 15.0, 0.0, -50.0, x,0.0, z);
}

int main(void)
{
    const int largura = 800;
    const int altura = 600;

    glfwInit();

    GLFWwindow *window = glfwCreateWindow(largura, altura, "Cubo", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // inicio
    init();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int largura, altura;
        glfwGetFramebufferSize(window, &largura, &altura);

        redimenciona(largura, altura);
        desenha();

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}