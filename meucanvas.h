#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include <QOpenGLWidget>
#include <QKeyEvent>

#include "personagem.h"
#include "arvore.h"
#include "camera.h"


class MeuCanvas : public QOpenGLWidget {

    Q_OBJECT

    private:
        Camera camera;
        Personagem personagem;
        Arvore arvores[10];
        int total;
        int papeis_achados;
        float mouse_lastX;
        float mouse_lastY;
        float yaw, pitch;
        bool mouse_start;

    signals:
        void atualizaContador();

    public:
        MeuCanvas(QWidget * parent);

        int getTotal();
        int getPapeisAchados();
        void initializeGL();
        void paintGL();
        void keyPressEvent(QKeyEvent *e);
        void mouseMoveEvent(QMouseEvent *event);
        void verificaLocal();
};

#endif // MEUCANVAS_H
