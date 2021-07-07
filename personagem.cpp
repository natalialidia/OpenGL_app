#include "personagem.h"

Personagem::Personagem() {
    pos   = glm::vec3(0,0,0);
    vec_i = glm::vec3(1,0,0);
    vec_j = glm::vec3(0,1,0);
}

glm::vec3 Personagem::getPos() {
    return this->pos;
}

void Personagem::andaVertical(float distancia) {

    pos = pos + distancia * vec_j;

}

void Personagem::andaHorizontal(float distancia) {

    pos = pos + distancia * vec_i;

}

void Personagem::gira(float angulo) {
    glm::mat4 mat_rotacao = glm::rotate(glm::mat4(1.0),
                                        glm::radians(angulo),
                                        glm::vec3(0,0,1));
    vec_i = glm::vec3(mat_rotacao * glm::vec4(vec_i, 0));
    vec_j = glm::vec3(mat_rotacao * glm::vec4(vec_j, 0));
}

void Personagem::desenha() {

    glm::mat4 matrix = glm::mat4(1.0);
    matrix[0] = glm::vec4(vec_i, 0);
    matrix[1] = glm::vec4(vec_j, 0);
    matrix[3] = glm::vec4(pos,   1);

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix));

    // OpenGL Legacy!!
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f,-0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();

    glPopMatrix();
}
