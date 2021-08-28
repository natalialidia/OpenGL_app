#include "face.h"

Face::Face() {

}

void Face::setFaceVertices(int v1, int v2, int v3) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
}

// método adicionado para iluminação
void Face::setFaceNormais(int vn1, int vn2, int vn3) {
    normais[0] = vn1;
    normais[1] = vn2;
    normais[2] = vn3;
}

int Face::getVertice(int index){
    return vertices[index];
}

// método adicionado para iluminação
int Face::getNormal(int index) {
    return normais[index];
}
