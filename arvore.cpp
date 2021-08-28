#include "arvore.h"

Arvore::Arvore() {
    pos   = glm::vec3(0,0,0);
    vec_i = glm::vec3(1,0,0);
    vec_j = glm::vec3(0,1,0);
    vec_k = glm::vec3(0,0,1);

    this->lerOBJ();

}

void Arvore::lerOBJ() {

    QFile file(":/models/piramide.obj");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Não foi possível abrir o arquivo";
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {

        QString line = in.readLine();

        QStringList fields = line.split(" ");

        // verifica pelo primeiro campo da linha
        // para definir a criação de vértices ou faces
        if (fields[0] == "v") {
            this->setVertices(fields);

        } else if (fields[0] == "f"){
            this->setFaces(fields);

        } else if (fields[0] == "vn") { // vetores normais, para iluminação
            this->setNormais(fields);
        }
    }

    file.close();

}

void Arvore::setVertices(QStringList fields) {

    float coordX = fields[1].toFloat();
    float coordY = fields[2].toFloat();
    float coordZ = fields[3].toFloat();

    vertices.push_back(glm::vec3(coordX, coordY, coordZ));
}

// método para teste de iluminação
void Arvore::setNormais(QStringList fields) {

    float coordX = fields[1].toFloat();
    float coordY = fields[2].toFloat();
    float coordZ = fields[3].toFloat();

    normais.push_back(glm::vec3(coordX, coordY, coordZ));
}

void Arvore::setFaces(QStringList fields) {

    // separa os valores das faces pelas barras
    QStringList f1 = fields[1].split("/");
    QStringList f2 = fields[2].split("/");
    QStringList f3 = fields[3].split("/");

    Face face;

    // utiliza o primeiro valor, que corresponde ao vértice
    face.setFaceVertices(f1[0].toInt() - 1,
                         f2[0].toInt() - 1,
                         f3[0].toInt() - 1);

    // verifica se existe índice do vetor normal, para iluminação
    if (f1.length() == 3 && f2.length() == 3 && f3.length() == 3) {
        face.setFaceNormais(f1[2].toInt() - 1,
                            f2[2].toInt() - 1,
                            f3[2].toInt() - 1);
    }

    faces.push_back(face);

}

bool Arvore::getAnotacao() {
    return this->anotacao;
}

void Arvore::setAnotacao(bool anotacao)  {
    this->anotacao = anotacao;
}

glm::vec3 Arvore::getPosicao() {
    return this->pos;
}

void Arvore::setPosicao(float x, float y, float z) {
    this->pos = glm::vec3(x,y,z);
}

void Arvore::desenha() {

    // cria a matriz de transformação
    glm::mat4 matrix = glm::mat4(1.0);
    matrix[0] = glm::vec4(vec_i, 0);
    matrix[1] = glm::vec4(vec_j, 0);
    matrix[2] = glm::vec4(vec_k, 0);
    matrix[3] = glm::vec4(pos,   1);

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix));

    // desenha o objeto percorrendo todas as faces
    // e os vértices de cada uma delas
    glBegin(GL_TRIANGLES);

        glColor3f(0, 0, .8f);

        for (auto i = faces.begin(); i != faces.end(); ++i) {

            for (int j = 0; j < 3; j++) {
                glVertex3fv(glm::value_ptr(vertices[(*i).getVertice(j)]));
            }

        }

    glEnd();

    glLineWidth(3);

    // desenha arestas para cada uma das faces do objeto
    glColor3f(0, 0, 0);
    for (auto i = faces.begin(); i != faces.end(); ++i) {
        glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 3; j++) {
                glVertex3fv(glm::value_ptr(vertices[(*i).getVertice(j)]));
            }
        glEnd();
    }

    glPopMatrix();
}
