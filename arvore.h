#ifndef ARVORE_H
#define ARVORE_H

#include <QOpenGLWidget>

#include "glm/vec3.hpp"

#include "face.h"
#include "luz.h"
#include "camera.h"

#include <QString>
#include <vector>
using namespace std;

class Arvore {
    private:
        bool anotacao;
        glm::vec3 pos, vec_i, vec_j, vec_k;

        vector <glm::vec3> vertices;
        vector <glm::vec3> v_normais;
        vector <Face> faces;

        float x_min, y_min, z_min, x_max, y_max, z_max;

        void lerOBJ();
        void setVertices(QStringList fields);
        void setFaces(QStringList fields);
        void calcBoundingBox();


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
