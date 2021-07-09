#include "meucanvas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 32
#define HEIGHT 24

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {
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
}

int MeuCanvas::getTotal() {
    return this->total;
}

int MeuCanvas::getPapeisAchados() {
    return this->papeis_achados;
}

void MeuCanvas::initializeGL() {
    glClearColor(0.21f, 0.14f, 0.11f, 1);
}

void MeuCanvas::paintGL() {
    // limpa o frame buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // propriedades de visualização
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, -1,1);
    glMatrixMode(GL_MODELVIEW);

//    int qtd = sizeof(arvores);

//    for (int i = 0; i < qtd; i++)
//        arvores[i].desenha();

    arvores[0].desenha();
    arvores[1].desenha();
    arvores[2].desenha();
    arvores[3].desenha();
    arvores[4].desenha();
    arvores[5].desenha();
    arvores[6].desenha();
    arvores[7].desenha();
    arvores[8].desenha();
    arvores[9].desenha();
    personagem.desenha();

}

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

    switch(e->key()) {
        case Qt::Key_Up:

            personagem.andaVertical(0.25f);

            break;

        case Qt::Key_Down:

            personagem.andaVertical(-0.25f);

            break;

        case Qt::Key_Left:

            personagem.andaHorizontal(-0.25f);

            break;
        case Qt::Key_Right:

            personagem.andaHorizontal(0.25f);

            break;
        case Qt::Key_E:
            MeuCanvas::verificaLocal();

            break;
    }

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

