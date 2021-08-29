#ifndef ARVORE_H
#define ARVORE_H

#include <QOpenGLWidget>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "glm/ext.hpp"
#include "glm/trigonometric.hpp"

#include "face.h"
#include "luz.h"
#include "camera.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <vector>
using namespace std;

class Arvore {
    private:
        bool anotacao;
        glm::vec3 pos, vec_i, vec_j, vec_k;

        vector <glm::vec3> vertices;
        vector <glm::vec3> v_normais;
        vector <Face> faces;

        void lerOBJ();
        void setVertices(QStringList fields);
        void setFaces(QStringList fields);

    public:
        Arvore();
        bool getAnotacao();
        void setAnotacao(bool anotacao);
        glm::vec3 getPosicao();
        void setPosicao(float x, float y, float z);
        void escala(float valor);
        void translacao(float x, float y, float z);
        void rotacao(float ang);
        void desenha(Luz lanterna, Luz natural, Camera camera);
};

#endif // ARVORE_H
