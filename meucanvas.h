#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include <QOpenGLWidget>
#include <QKeyEvent>

#include "personagem.h"
#include "arvore.h"


class MeuCanvas : public QOpenGLWidget {
    private:
        Personagem personagem;
        Arvore arvores[5];

    public:
        MeuCanvas(QWidget * parent);

        void initializeGL();
        void paintGL();
        void keyPressEvent(QKeyEvent *e);
//        void keyReleaseEvent(QKeyEvent *e);
};

#endif // MEUCANVAS_H
