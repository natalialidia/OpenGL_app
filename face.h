#ifndef FACE_H
#define FACE_H

#include "glm/vec3.hpp"
#include <GL/gl.h>

class Face {
    private:
        int vertices[3];
        int normais[3];


    public:
        Face();
        void setFaceVertices(int v1, int v2, int v3);
        void setFaceNormais(int vn1, int vn2, int vn3);
        int getVertice(int index);
        int getNormal(int index);
};

#endif // FACE_H
