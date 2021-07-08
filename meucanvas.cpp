#include "meucanvas.h"

#define WIDTH 32
#define HEIGHT 24

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {

    total = 3;
    papeis_achados = 0;

    arvores[0].setPosicao(5,5);
    arvores[1].setPosicao(10,12);
    arvores[2].setPosicao(15,15);
    arvores[3].setPosicao(18,8);
    arvores[4].setPosicao(8,18);

    arvores[1].setAnotacao(true);
    arvores[4].setAnotacao(true);
    arvores[0].setAnotacao(true);

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

