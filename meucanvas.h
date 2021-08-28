#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include <QOpenGLWidget>
#include <QKeyEvent>

#include "personagem.h"
#include "arvore.h"
#include "camera.h"
#include "luz.h"


class MeuCanvas : public QOpenGLWidget {

    Q_OBJECT

    private:
        Camera camera;
        float yaw, pitch;

        Personagem personagem;
        Arvore arvores[10];

        Luz lanterna;
        Luz natural;

        int total;
        int papeis_achados;
        bool pausado;


        void desenhaCenario();

    signals:
        void atualizaContador();

    public:
        MeuCanvas(QWidget * parent);

        int getTotal();
        int getPapeisAchados();
        void initializeGL();
        void paintGL();
        void keyPressEvent(QKeyEvent *e);
        void mousePressEvent(QMouseEvent* evt);
        void mouseMoveEvent(QMouseEvent *event);
        void verificaLocal();
};

#endif // MEUCANVAS_H
