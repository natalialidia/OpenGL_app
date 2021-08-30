#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QDateTime>

#include "personagem.h"
#include "arvore.h"
#include "camera.h"
#include "luz.h"
#include "textura.h"


class MeuCanvas : public QOpenGLWidget {

    Q_OBJECT

    private:
        Camera camera;
        int cam_frente, cam_tras, cam_esq, cam_dir;

        Personagem personagem;
        Arvore arvores[10];

        Textura chao;

        Luz lanterna;
        Luz natural;

        int total;
        int papeis_achados;
        bool pausado;

        void desenhaCenario();
        void verificaColisao();

    signals:
        void atualizaContador();

    public:
        MeuCanvas(QWidget * parent);

        int getTotal();
        int getPapeisAchados();
        void initializeGL();
        void paintGL();
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void mousePressEvent(QMouseEvent* evt);
        void mouseMoveEvent(QMouseEvent *event);
        void verificaLocal();

    public slots:
        void idleGL();
};

#endif // MEUCANVAS_H
