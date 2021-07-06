#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <QOpenGLWidget>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "glm/ext.hpp"
#include "glm/trigonometric.hpp"

class Personagem {
    private:
        glm::vec3 pos, vec_i, vec_j;

    public:

        Personagem();
        void andaVertical(float distancia);
        void andaHorizontal(float distancia);
        void gira(float angulo);
        void desenha();
};

#endif // PERSONAGEM_H
