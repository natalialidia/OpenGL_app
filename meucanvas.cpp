#include "meucanvas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 32
#define HEIGHT 24

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {
    setMouseTracking(true);


    srand(time(NULL));
    total = 3;
    int n, r, p[total];
    papeis_achados = 0;

    arvores[0].setPosicao(25,12);
    arvores[1].setPosicao(10,13);
    arvores[2].setPosicao(2,15);
    arvores[3].setPosicao(18,8);
    arvores[4].setPosicao(8,18);
    arvores[5].setPosicao(10,3);
    arvores[6].setPosicao(27,6);
    arvores[7].setPosicao(20,18);
    arvores[8].setPosicao(5,10);
    arvores[9].setPosicao(28,20);
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

    mouse_start = true;

}

int MeuCanvas::getTotal() {
    return this->total;
}

int MeuCanvas::getPapeisAchados() {
    return this->papeis_achados;
}

void MeuCanvas::initializeGL() {
    glClearColor(1, 1, 1, 1);
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

    //chão
    glColor3f(0.21f, 0.14f, 0.11f);
    glBegin(GL_QUADS);
        glVertex3f(80,0,0);
        glVertex3f(-80,0,0);
        glVertex3f(-80,0,80);
        glVertex3f(80,0,80);
    glEnd();

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

//    arvores[0].desenha();
//    arvores[1].desenha();
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

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

    float speed = 0.05f; //adicionar velocidade do movimento

    glm::vec3 pos = camera.getEye();

    switch(e->key()) {

        case Qt::Key_W: {
            pos += speed * camera.getAt();

            break;
        }
        case Qt::Key_S: {
            pos -= speed * camera.getAt();

            break;
        }
        case Qt::Key_A: {
            pos -= glm::normalize(glm::cross(camera.getAt(), camera.getUp())) * speed;

            break;
        }
        case Qt::Key_D: {
            pos += glm::normalize(glm::cross(camera.getAt(), camera.getUp())) * speed;

            break;
        }

        case Qt::Key_E:
            MeuCanvas::verificaLocal();

            break;
    }

    camera.setEye(pos.x, pos.y, pos.z);

    update();

}

void MeuCanvas::mouseMoveEvent(QMouseEvent* event) {

    if (mouse_start) {
        mouse_lastX = event->pos().x();
        mouse_lastY = event->pos().y();
        mouse_start = false;
    }

    float xoffset = event->pos().x() - mouse_lastX;
    float yoffset = mouse_lastY -  event->pos().y();
    mouse_lastX = event->pos().x();
    mouse_lastY = event->pos().y();

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    camera.setAt(direction.x, direction.y, direction.z);

    update();

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

