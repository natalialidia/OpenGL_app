#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include <QOpenGLWidget>
#include <QKeyEvent>

#include "personagem.h"
#include "arvore.h"


class MeuCanvas : public QOpenGLWidget {

    Q_OBJECT

    private:
        Personagem personagem;
        Arvore arvores[10];
        int total;
        int papeis_achados;

    signals:
        void atualizaContador();

    public:
        MeuCanvas(QWidget * parent);

        int getTotal();
        int getPapeisAchados();
        void initializeGL();
        void paintGL();
        void keyPressEvent(QKeyEvent *e);
        void verificaLocal();
};

#endif // MEUCANVAS_H
