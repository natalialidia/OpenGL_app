#include "arvore.h"

Arvore::Arvore() {
    pos   = glm::vec3(0,0,0);
    vec_i = glm::vec3(1,0,0);
    vec_j = glm::vec3(0,1,0);
    vec_k = glm::vec3(0,0,1);

    this->lerOBJ();

    this->calcBoundingBox();
}

void Arvore::lerOBJ() {

    QFile file(":/models/tree3.obj");

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
            // this->setNormais(fields);
        }
    }

    file.close();

    // normaliza as normais dos vértices
    for (auto i = v_normais.begin(); i != v_normais.end(); ++i)
        (*i) = glm::normalize((*i));

}

void Arvore::setVertices(QStringList fields) {

    float coordX = fields[1].toFloat();
    float coordY = fields[2].toFloat();
    float coordZ = fields[3].toFloat();

    vertices.push_back(glm::vec3(coordX, coordY, coordZ));

    //inicia a normal do vértice
    v_normais.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
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

    // calcula a normal da face
    glm::vec3 u = vertices[face.getVertice(1)] - vertices[face.getVertice(0)];
    glm::vec3 v = vertices[face.getVertice(2)] - vertices[face.getVertice(0)];

    glm::vec3 n = glm::cross(u,v);
    n = glm::normalize(n);

    face.setNormal(n);

    // adiciona a face
    faces.push_back(face);

    // calcula as normais dos vértices da face
    v_normais[face.getVertice(0)] += n;
    v_normais[face.getVertice(1)] += n;
    v_normais[face.getVertice(2)] += n;
}

void Arvore::escala(float valor) {

    //cria a matriz de escala
    glm::mat4 mat_escala = glm::scale(glm::mat4(1.0),
                                      glm::vec3(valor));

    // aplica a escala nos vetores
    vec_i = glm::vec3(mat_escala * glm::vec4(vec_i,0));
    vec_j = glm::vec3(mat_escala * glm::vec4(vec_j,0));
    vec_k = glm::vec3(mat_escala * glm::vec4(vec_k,0));
}

void Arvore::translacao(float x, float y, float z) {

    //cria a matriz de translação
    glm::mat4 mat_translacao = glm::translate(glm::mat4(1.0),
                                              glm::vec3(x,y,z));

    // multiplica a matriz de translação pela posição
    pos = mat_translacao * glm::vec4(pos, 1.0f);
}

void Arvore::rotacao(float ang) {

    //cria a matriz de rotação utilizando o eixo definido
    glm::mat4 mat_rotacao = glm::rotate(glm::mat4(1.0),
                                        glm::radians(ang),
                                        glm::vec3(0,1,0));

    // rotaciona os vetores
    vec_i = glm::vec3(mat_rotacao * glm::vec4(vec_i,0));
    vec_j = glm::vec3(mat_rotacao * glm::vec4(vec_j,0));
    vec_k = glm::vec3(mat_rotacao * glm::vec4(vec_k,0));

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

void Arvore::calcBoundingBox() {

    x_min = y_min = z_min = FLT_MAX;
    x_max = y_max = z_max = FLT_MIN;

    for (auto i = vertices.begin(); i != vertices.end(); ++i) {

        if (x_min > (*i).x)
            x_min = (*i).x;

        if (y_min > (*i).y)
            y_min = (*i).y;

        if (z_min > (*i).z)
            z_min = (*i).z;

        if (x_max < (*i).x)
            x_max = (*i).x;

        if (y_max < (*i).y)
            y_max = (*i).y;

        if (z_max < (*i).z)
            z_max = (*i).z;

    }

}

void Arvore::desenha(Luz lanterna, Luz natural, Camera camera) {

    // cria a matriz de transformação
    glm::mat4 matrix = glm::mat4(1.0);
    matrix[0] = glm::vec4(vec_i, 0);
    matrix[1] = glm::vec4(vec_j, 0);
    matrix[2] = glm::vec4(vec_k, 0);
    matrix[3] = glm::vec4(pos,   1);

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix));

    glm::mat4 mv_matrix = camera.getCameraMatrix() * matrix; // model view matrix
    glm::mat4 n_matrix = glm::transpose(glm::inverse(mv_matrix)); // normal matrix

    // transforma a posição da câmera para coordenada de câmera
    glm::vec3 pos_camera = glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f));

    glm::vec3 cor = glm::vec3(0,0,0);

    glm::vec3 mat_dif = glm::vec3(0, .8f, 0);
    glm::vec3 mat_amb = 0.2f * mat_dif;
    glm::vec3 mat_esp = glm::vec3(1, 1, 1);
    float mat_exp = 16;

    lanterna.setMatDif(mat_dif);
    lanterna.setMatAmb(mat_amb);
    lanterna.setMatEsp(mat_esp);
    lanterna.setMatExp(mat_exp);

    natural.setMatDif(mat_dif);
    natural.setMatAmb(mat_amb);
    natural.setMatEsp(mat_esp);
    natural.setMatExp(mat_exp);

    // desenha o objeto percorrendo todas as faces
    // e os vértices de cada uma delas
    glBegin(GL_TRIANGLES);

        for (auto i = faces.begin(); i != faces.end(); ++i) {

            for (int j = 0; j < 3; j++) {

                cor = lanterna.calcIluminacao(pos_camera,
                                              vertices[(*i).getVertice(j)],
                                              v_normais[(*i).getVertice(j)],
                                              n_matrix,
                                              mv_matrix);

                cor += natural.calcIluminacao(pos_camera,
                                              vertices[(*i).getVertice(j)],
                                              v_normais[(*i).getVertice(j)],
                                              n_matrix,
                                              mv_matrix);

                glColor3fv(glm::value_ptr(cor));

                glVertex3fv(glm::value_ptr(vertices[(*i).getVertice(j)]));
            }

        }

    glEnd();


    if (anotacao) {

        mat_dif = glm::vec3(1, 1, 1);
        mat_amb = 0.2f * mat_dif;
        mat_esp = glm::vec3(1, 1, 1);
        mat_exp = 32;

        lanterna.setMatDif(mat_dif);
        lanterna.setMatAmb(mat_amb);
        lanterna.setMatEsp(mat_esp);
        lanterna.setMatExp(mat_exp);

        natural.setMatDif(mat_dif);
        natural.setMatAmb(mat_amb);
        natural.setMatEsp(mat_esp);
        natural.setMatExp(mat_exp);

        glBegin(GL_QUADS);

            cor = lanterna.calcIluminacao(pos_camera,
                                          glm::vec3(x_max-90, y_min+30, z_min+82),
                                          glm::vec3(0,1,0),
                                          n_matrix,
                                          mv_matrix);

            cor += natural.calcIluminacao(pos_camera,
                                          glm::vec3(x_max-90, y_min+30, z_min+82),
                                          glm::vec3(0,1,0),
                                          n_matrix,
                                          mv_matrix);

            glColor3fv(glm::value_ptr(cor));

            glVertex3f(x_max-100, y_min+30, z_min+75);
            glVertex3f(x_max-100, y_min+30, z_min+90);
            glVertex3f(x_max-80, y_min+30, z_min+90);
            glVertex3f(x_max-80, y_min+30, z_min+75);
        glEnd();

    }


    glPopMatrix();
}
