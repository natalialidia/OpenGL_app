#ifndef FACE_H
#define FACE_H

#include "glm/vec3.hpp"
#include <GL/gl.h>

class Face {
    private:
        int vertices[3];
        glm::vec3 normal;


    public:
        Face();
        void setFaceVertices(int v1, int v2, int v3);
        void setNormal(glm::vec3 normal);
        int getVertice(int index);
        glm::vec3 getNormal();
};

#endif // FACE_H
