#include "face.h"

Face::Face() {

}

void Face::setFaceVertices(int v1, int v2, int v3) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
}

void Face::setNormal(glm::vec3 normal) {
    this->normal = normal;
}

int Face::getVertice(int index){
    return vertices[index];
}

glm::vec3 Face::getNormal() {
    return normal;
}
