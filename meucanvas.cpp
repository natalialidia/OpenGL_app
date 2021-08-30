#include "meucanvas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {
    setMouseTracking(true);


    srand(time(NULL));
    total = 3;
    int n, r, p[total];
    papeis_achados = 0;

    arvores[0].translacao(0,5,10);
    arvores[0].escala(.02f);

    arvores[1].translacao(3,5,13);
    arvores[1].escala(.02f);
    arvores[1].rotacao(45.0f);
//    arvores[1].setPosicao(10,13);
//    arvores[2].setPosicao(2,15);
//    arvores[3].setPosicao(18,8);
//    arvores[4].setPosicao(8,18);
//    arvores[5].setPosicao(10,3);
//    arvores[6].setPosicao(27,6);
//    arvores[7].setPosicao(20,18);
//    arvores[8].setPosicao(5,10);
//    arvores[9].setPosicao(28,20);
    for(int i =0; i<total;i++){
        n =rand()%10;
        r=0;
        for(int j=0; j<total; j++){
                if(n == p[j]){
                    r++;
                }
         }if(r==0){
            p[i]=n;
            arvores[n].setAnotacao(true);
         }if(r!=0){
            i--;
            }
    }

    camera.setEye(0,1.7f,0);
    camera.setAt(0, 0, 5);
    camera.setUp(0, 1, 0);

    lanterna.setTipo(1);
    lanterna.setAngLuz(12.0f);

    natural.setTipo(2);
    natural.setLuzDif(glm::vec3(.01));
    natural.setLuzAmb(glm::vec3(.005f));
    natural.setLuzEsp(glm::vec3(.1f));

    pausado = true;

}

int MeuCanvas::getTotal() {
    return this->total;
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

    glLineWidth(10);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(-100,0,0);
        glVertex3f(100,0,0);
        glColor3f(0, 1, 0);
        glVertex3f(0,-100,0);
        glVertex3f(0,100,0);
        glColor3f(0, 0, 1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();

    arvores[0].desenha(lanterna, natural, camera);
    arvores[1].desenha(lanterna, natural, camera);
//    arvores[2].desenha();
//    arvores[3].desenha();
//    arvores[4].desenha();
//    arvores[5].desenha();
//    arvores[6].desenha();
//    arvores[7].desenha();
//    arvores[8].desenha();
//    arvores[9].desenha();
//    personagem.desenha();

}

void MeuCanvas::desenhaCenario() {

    glm::vec3 vertices[4] = {glm::vec3(80,0,0),
                             glm::vec3(-80,0,0),
                             glm::vec3(-80,0,80),
                             glm::vec3(80,0,80)};

    float tex_coords[4][2] = {{-80, -80},
                              {81, -80},
                              {81, 81},
                              {-80, 81}};

    glm::vec3 normal = glm::normalize(glm::cross(vertices[0]-vertices[1], vertices[0] - vertices[3]));

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

        for (int i = 0; i < 4; i++) {

           cor = lanterna.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                          vertices[i],
                                          normal,
                                          glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                          camera.getCameraMatrix());

            cor += natural.calcIluminacao(glm::vec3(camera.getCameraMatrix() * glm::vec4(camera.getEye(), 1.0f)),
                                          vertices[i],
                                          normal,
                                          glm::transpose(glm::inverse(camera.getCameraMatrix())),
                                          camera.getCameraMatrix());

            glColor3fv(glm::value_ptr(cor));

            glTexCoord2fv(tex_coords[i]);
            glVertex3fv(glm::value_ptr(vertices[i]));
        }


    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);


}

void MeuCanvas::verificaColisao() {

    glm::vec3 cam_pos = camera.getEye();

    if (cam_pos.z <= 1.0f) {

        if (cam_frente) cam_frente = false;
        if (cam_tras) cam_tras = false;
        if (cam_esq) cam_esq = false;
        if (cam_dir) cam_dir = false;

    }

    qDebug() << cam_pos.z;

}

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

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
        case Qt::Key_E:
            MeuCanvas::verificaLocal();
            break;
        case Qt::Key_Escape: {
            unsetCursor();
            pausado = true;
            break;
        }
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

    glm::vec3 personagem_pos = personagem.getPos();
    glm::vec3 arvore_pos;

    for (unsigned int i = 0; i < sizeof(arvores); i++){

        arvore_pos = arvores[i].getPosicao();

        if (personagem_pos.x <= arvore_pos.x + 1.25 && personagem_pos.x >= arvore_pos.x - 1.25 &&
            personagem_pos.y <= arvore_pos.y + 1.25 && personagem_pos.y >= arvore_pos.y - 1.25) {

            if (arvores[i].getAnotacao()) {
                papeis_achados++;
                emit atualizaContador();
                arvores[i].setAnotacao(false);
            }

        }

    }

}

void MeuCanvas::idleGL() {

    this->verificaColisao();

    camera.anda(cam_frente, cam_tras, cam_esq, cam_dir);

    update();

}

