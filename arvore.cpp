#include "arvore.h"

Arvore::Arvore() {
    pos   = glm::vec3(0,0,0);
    vec_i = glm::vec3(1,0,0);
    vec_j = glm::vec3(0,1,0);
}

void Arvore::setAnotacao(bool anotacao)  {
    this->anotacao = anotacao;
}

void Arvore::setPosicao(float x, float y) {
    this->pos = glm::vec3(x,y,0);
}

void Arvore::desenha() {

    glm::mat4 matrix = glm::mat4(1.0);
    matrix[0] = glm::vec4(vec_i, 0);
    matrix[1] = glm::vec4(vec_j, 0);
    matrix[3] = glm::vec4(pos,   1);

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix));

    // OpenGL Legacy!!

    if (anotacao) {
        glColor3f(0,0.39f,0);
    } else {
        glColor3f(0,1,0);
    }

    glBegin(GL_TRIANGLES);
        glVertex2f(-1,-1);
        glVertex2f( 1,-1);
        glVertex2f( 0, 1);
    glEnd();

    glPopMatrix();
}
