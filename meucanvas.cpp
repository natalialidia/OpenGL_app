//Natália Lídia Lima Coelho - 472327

#include "meucanvas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {
    setMouseTracking(true);

    tempo.setHMS(0,10,0); // tempo limite de 1 minuto
    total_papeis = 3; // total de 3 papeis;
    papeis_achados = 0;

    float mapa[10][2] = {{3,3},
                         {4,8},
                         {-10,12},
                         {-15,25},
                         {28,14},
                         {10,10},
                         {17,4},
                         {-5,22},
                         {22,29},
                         {7,25},
                        };

    num_arvores = 10;

    for (int i = 0; i < num_arvores; i++) {
        Arvore a;
        arvores.push_back(a);
        arvores[i].escala(.02f);
        arvores[i].translacao(mapa[i][0], 4.0f, mapa[i][1]);
        arvores[i].rotacao(i*36.0f);
    }

    srand(time(NULL));
    int id_arvore, repeticao, p[total_papeis];

    // anotações em árvores aleatórias
    for (int i = 0; i < total_papeis; i++) {
        id_arvore = rand()%num_arvores;
        repeticao = 0;

        for (int j = 0; j < total_papeis; j++) {
            if (id_arvore == p[j]) {
                repeticao++;
            }
        }

        if (repeticao == 0) {
            p[i]=id_arvore;
            arvores[id_arvore].setAnotacao(true);
        }

        if(repeticao != 0) {
            i--;
        }
    }

    camera.setEye(0,1.7f,5);
    camera.setAt(0, 0, 5);
    camera.setUp(0, 1, 0);

    lanterna.setTipo(1);
    lanterna.setAngLuz(12.0f);

    natural.setTipo(2);
    natural.setLuzDif(glm::vec3(1.0f));
    natural.setLuzAmb(glm::vec3(.5f));
    natural.setLuzEsp(glm::vec3(1.0f));

    pausado = true;
}

QTime MeuCanvas::getTempo() {
    return this->tempo;
}

void MeuCanvas::setTempo(QTime tempo) {
    this->tempo = tempo;
}

bool MeuCanvas::getPausado() {
    return this->pausado;
}

void MeuCanvas::setPausado(bool pausado) {
    this->pausado = pausado;
}

int MeuCanvas::getTotal() {
    return this->total_papeis;
}

int MeuCanvas::getPapeisAchados() {
    return this->papeis_achados;
}

void MeuCanvas::initializeGL() {
    glClearColor(.05f, .08f, .27f, 1);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    chao.carrega((char*)"debug/texturas/chao2.jpg");
}

void MeuCanvas::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    float ar = this->width()/ (float) this->height();

    glm::mat4 projMatrix = glm::perspective(glm::radians(50.0f),
                                            ar,
                                            0.1f,100.0f);

    glLoadMatrixf(glm::value_ptr(projMatrix));

    camera.setCamera();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // define a posição da lanterna em coordenada de câmera
    lanterna.setPosLuz(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)));

    // define a direção da lanterna em coordenada de câmera
    lanterna.setDirLuz(glm::vec3(glm::transpose(glm::inverse(camera.getCameraMatrix())) * glm::vec4(camera.getAt(), 0.0f)));

    // define a direção da luz natural em coordenada de câmera
    natural.setDirLuz(glm::vec3(glm::transpose(glm::inverse(camera.getCameraMatrix())) * glm::vec4(-1, -1, 0, 0)));

    this->desenhaCenario();

    for (int i = 0; i < num_arvores; i++) {
        arvores[i].desenha(lanterna, natural, camera);
    }
}

void MeuCanvas::desenhaCenario() {

    float lado = 30;
    float altura = 5;

    glm::vec3 vertices[] = {
        glm::vec3( lado, 0, 0),
        glm::vec3(-lado, 0, 0),
        glm::vec3(-lado, 0, lado),
        glm::vec3( lado, 0, lado),

        glm::vec3( lado, altura, 0),
        glm::vec3(-lado, altura, 0),
        glm::vec3(-lado, altura, lado),
        glm::vec3( lado, altura, lado)
    };

    float tex_coords[4][2] = {{-lado,   -lado},
                              { lado+1, -lado},
                              { lado+1,  lado+1},
                              {-lado,    lado+1}};

    glm::vec3 mat_dif = glm::vec3(0, .4f, 0);
    glm::vec3 mat_esp = glm::vec3(1, 1, 1);

    lanterna.setMatDif(mat_dif);
    lanterna.setMatAmb(0.2f * mat_dif);
    lanterna.setMatEsp(mat_esp);
    lanterna.setMatExp(32);

    natural.setMatDif(mat_dif);
    natural.setMatAmb(0.2f * mat_dif);
    natural.setMatEsp(mat_esp);
    natural.setMatExp(32);

    glm::vec3 cor = glm::vec3(0,0,0);

    glBindTexture(GL_TEXTURE_2D, chao.getTexId());

    glBegin(GL_QUADS);

        cor = lanterna.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                       glm::vec3(0,0,lado/2),
                                       glm::vec3(0,1,0),
                                       glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                       camera.getCameraMatrix());

        cor += natural.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                      glm::vec3(0,0,lado/2),
                                      glm::vec3(0,1,0),
                                      glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                      camera.getCameraMatrix());

        glColor3fv(glm::value_ptr(cor));
        for (int i = 0; i < 4; i++) {
            glTexCoord2fv(tex_coords[i]);
            glVertex3fv(glm::value_ptr(vertices[i]));
        }


    glEnd();

    int indices_paredes[4][4] = {{5,6,2,1},
                                 {3,7,4,0},
                                 {2,6,7,3},
                                 {1,0,4,5}};


    glm::vec3 normais_paredes[4] = {glm::vec3(1,0,0),
                                    glm::vec3(-1,0,0),
                                    glm::vec3(0,0,1),
                                    glm::vec3(0,0,-1)};

    mat_dif = glm::vec3(.6f, .6f, .6f);
    mat_esp = glm::vec3(1, 1, 1);

    lanterna.setMatDif(mat_dif);
    lanterna.setMatAmb(0.2f * mat_dif);
    lanterna.setMatEsp(mat_esp);
    lanterna.setMatExp(32);

    natural.setMatDif(mat_dif);
    natural.setMatAmb(0.2f * mat_dif);
    natural.setMatEsp(mat_esp);
    natural.setMatExp(32);

    glBegin(GL_QUADS);

        for (int i = 0; i < 4; i++) {

            cor = lanterna.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                           vertices[i],
                                           normais_paredes[i],
                                           glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                           camera.getCameraMatrix());

            cor += natural.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                           vertices[i],
                                           normais_paredes[i],
                                           glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                           camera.getCameraMatrix());

            glColor3fv(glm::value_ptr(cor));
            for (int j = 0; j < 4; j++) {
                glVertex3fv(glm::value_ptr(vertices[indices_paredes[i][j]]));
            }
        }

    glEnd();

}

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

    if (!pausado) {

        switch(e->key()) {

            case Qt::Key_W: {
                cam_frente = 1;
                break;
            }
            case Qt::Key_S: {
                cam_tras = 1;
                break;
            }
            case Qt::Key_A: {
                cam_esq = 1;
                break;
            }
            case Qt::Key_D: {
                cam_dir = 1;
                break;
            }
            case Qt::Key_E: {
                MeuCanvas::verificaLocal();
                break;
            }
        }
    }

    if (e->key() == Qt::Key_Escape) {
        unsetCursor();
        pausado = true;
    }

}

void MeuCanvas::keyReleaseEvent(QKeyEvent *e) {

    switch(e->key()) {

        case Qt::Key_W: {
            cam_frente = 0;
            break;
        }
        case Qt::Key_S: {
            cam_tras = 0;
            break;
        }
        case Qt::Key_A: {
            cam_esq = 0;
            break;
        }
        case Qt::Key_D: {
            cam_dir = 0;
            break;
        }
    }

}

void MeuCanvas::mousePressEvent(QMouseEvent* event) {
    setCursor(Qt::BlankCursor);
    cursor().setPos(mapToGlobal(rect().center()));
    pausado = false;
}

void MeuCanvas::mouseMoveEvent(QMouseEvent* event) {

    if (event->pos() != rect().center() && !pausado) {

        QPoint centro = mapToGlobal(rect().center());
        QPointF delta = (event->globalPosition() - centro);

        camera.olha(delta.x(), - delta.y());

        update();

        cursor().setPos(mapToGlobal(rect().center()));
    }

}

void MeuCanvas::verificaLocal() {

    glm::vec3 camera_pos = camera.getEye();
    glm::vec3 arvore_pos;

    for (int i = 0; i < num_arvores; i++){

        arvore_pos = arvores[i].getPosicao();

        if (camera_pos.x <= arvore_pos.x + 1.8 && camera_pos.x >= arvore_pos.x - 1.8 &&
            camera_pos.z <= arvore_pos.z + 1.8 && camera_pos.z >= arvore_pos.z - 1.8) {

            if (arvores[i].getAnotacao()) {
                papeis_achados++;
                emit atualizaContador();
                arvores[i].setAnotacao(false);
            }

        }

    }

}

void MeuCanvas::idleGL() {

    camera.anda(cam_frente, cam_tras, cam_esq, cam_dir);

    update();

}

