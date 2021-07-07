#ifndef ARVORE_H
#define ARVORE_H

#include <QOpenGLWidget>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "glm/ext.hpp"
#include "glm/trigonometric.hpp"

class Arvore {
    private:
        bool anotacao;
        glm::vec3 pos, vec_i, vec_j;

    public:
        Arvore();
        bool getAnotacao();
        void setAnotacao(bool anotacao);
        glm::vec3 getPosicao();
        void setPosicao(float x, float y);
        void desenha();
};

#endif // ARVORE_H
