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
    natural.setLuzDif(glm::vec3(.2f));
    natural.setLuzAmb(glm::vec3(.1f));
    natural.setLuzEsp(glm::vec3(1));

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

    glm::vec3 normal = glm::vec3(0,1,0);


    glm::vec3 mat_dif = glm::vec3(0.21f, 0.14f, 0.11f);
    glm::vec3 mat_esp = glm::vec3(1, 1, 1);

    lanterna.setMatDif(mat_dif);
    lanterna.setMatAmb(0.2f * mat_dif);
    lanterna.setMatEsp(mat_esp);
    lanterna.setMatExp(16);

    natural.setMatDif(mat_dif);
    natural.setMatAmb(0.2f * mat_dif);
    natural.setMatEsp(mat_esp);
    natural.setMatExp(16);

    glm::vec3 cor = glm::vec3(0,0,0);

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

            glVertex3fv(glm::value_ptr(vertices[i]));
        }


    glEnd();


}

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

    float vel = 0.05f; //adicionar velocidade do movimento

    glm::vec3 pos = camera.getEye();

    glm::vec3 direcao = glm::vec3(camera.getAt().x, 0, camera.getAt().z);

    switch(e->key()) {

        case Qt::Key_W: {
            pos += vel * direcao;

            break;
        }
        case Qt::Key_S: {
            pos -= vel * direcao;

            break;
        }
        case Qt::Key_A: {
            pos -= glm::normalize(glm::cross(camera.getAt(), camera.getUp())) * vel;

            break;
        }
        case Qt::Key_D: {
            pos += glm::normalize(glm::cross(camera.getAt(), camera.getUp())) * vel;

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

    camera.setEye(pos.x, pos.y, pos.z);

    update();

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

        if (delta.isNull()) // mouse didn't move
            return;

        float xoffset = delta.x();
        float yoffset = - delta.y();

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction = glm::normalize(direction);
        camera.setAt(direction.x, direction.y, direction.z);

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

