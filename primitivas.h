#pragma once
#include <vector>
// struct vec3{
//     float x, y, z;
//     vec3() : x(0.0f), y(0.0f), z(0.0f) {}
//     vec3(float x, float y, float z) : x(x), y(y), z(z) {}
// };

void rect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, color cor)
{
    glColor3fv(cor);
    glBegin(GL_QUADS);
    glVertex3fv(glm::value_ptr(p1));
    glVertex3fv(glm::value_ptr(p2));
    glVertex3fv(glm::value_ptr(p3));
    glVertex3fv(glm::value_ptr(p4));
    glEnd();
}

void desenhaCubo(float lado)
{
    float d = lado / 2.0; // metade do lado

    glm::vec3 v1 = {-d, d, d};
    glm::vec3 v2 = {-d, -d, d};
    glm::vec3 v3 = {d, -d, d};
    glm::vec3 v4 = {d, d, d};

    glm::vec3 v5 = {d, d, -d};
    glm::vec3 v6 = {d, -d, -d};
    glm::vec3 v7 = {-d, -d, -d};
    glm::vec3 v8 = {-d, d, -d};

    // frente
    rect(v1, v2, v3, v4, vermelho);
    // direita
    rect(v4, v3, v6, v5, azul);
    // tras
    rect(v5, v8, v7, v6, amarelo);
    // esquerda
    rect(v1, v8, v7, v2, verde);
    // cima
    rect(v1, v4, v5, v8, laranja);
    // baixo
    rect(v2, v7, v6, v3, violeta);
}

void desenhaLinha(unsigned int &id, color cor, float xp, float yp, float zp,float xe,float ye, float ze)
{
    glNewList(1, GL_COMPILE);
    glColor3fv(cor);
    glPointSize(5.0);
    glBegin(GL_LINES);
    glVertex3f(xe, ye, ze);
    glVertex3f(xp, yp, zp);

    glEnd();
    glEndList();
}

void desenhaEsfera(unsigned int &id, color cor, GLfloat raio, GLuint nStacks, GLuint nSectors)
{
    std::vector<std::vector<GLuint>> indices;
    std::vector<glm::vec3> pontos;

    GLfloat deltaPhi = M_PI / nStacks;
    GLfloat deltaTheta = 2 * M_PI / nSectors;

    for (GLuint i = 0; i <= nStacks; i++)
    {
        GLfloat phi = -M_PI / 2.0 + i * deltaPhi;
        GLfloat r = raio * cos(phi);
        GLfloat y = raio * sin(phi);
        std::vector<GLuint> pt;

        for (GLuint j = 0; j < nSectors; j++)
        {
            GLfloat theta = j * deltaTheta;
            GLfloat x = r * sin(theta);
            GLfloat z = r * cos(theta);

            pontos.push_back(glm::vec3(x, y, z));
            GLuint index = pontos.size() - 1;
            pt.push_back(index);
        } // next j
        indices.push_back(pt);
    } // next i

    // colocando pontos
    // glColor3fv(vermelho);
    // glPointSize(2.5);
    // glBegin(GL_POINTS);
    // for (GLuint i = 0; i < pontos.size(); i++)
    // {
    //     glVertex3fv(&pontos[i].x);
    // }
    // glEnd();

    glNewList(id, GL_COMPILE);
    glColor3fv(cor);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    for (GLuint i = 0; i < nStacks; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        for (GLuint j = 0; j < nSectors; j++)
        {
            GLuint index = indices[i][j];
            glVertex3fv(glm::value_ptr(pontos[index]));
            index = indices[i + 1][j];
            glVertex3fv(glm::value_ptr(pontos[index]));

            if (j == nSectors - 1)
            {
                index = indices[i][0];
                glVertex3fv(glm::value_ptr(pontos[index]));
                index = indices[i + 1][0];
                glVertex3fv(glm::value_ptr(pontos[index]));
            }
        }
        glEnd();
    }
    glEndList();

}