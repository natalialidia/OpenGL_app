#include "meucanvas.h"

#define WIDTH 32
#define HEIGHT 24

MeuCanvas::MeuCanvas(QWidget * parent) : QOpenGLWidget(parent) {

    arvores[0].setPosicao(5,5);
    arvores[1].setPosicao(10,12);
    arvores[2].setPosicao(15,19);
    arvores[3].setPosicao(20,8);
    arvores[4].setPosicao(3,20);

    arvores[1].setAnotacao(true);
    arvores[4].setAnotacao(true);

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

    for (unsigned int i = 0; i < sizeof(arvores); i++)
        arvores[i].desenha();

    personagem.desenha();

}

void MeuCanvas::keyPressEvent(QKeyEvent *e) {

    switch(e->key()) {
        case Qt::Key_Up:

            personagem.andaVertical(0.5f);

            break;

        case Qt::Key_Down:

            personagem.andaVertical(-0.5f);

            break;

        case Qt::Key_Left:

            personagem.andaHorizontal(-0.5f);

            break;
        case Qt::Key_Right:

            personagem.andaHorizontal(0.5f);

            break;
    }

    update();

}

