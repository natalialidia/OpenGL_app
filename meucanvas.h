//Natália Lídia Lima Coelho - 472327

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

#include <vector>

class MeuCanvas : public QOpenGLWidget {

    Q_OBJECT

    private:
        QTime tempo;
        int total_papeis;
        int papeis_achados;
        bool pausado;

        Camera camera;
        int cam_frente, cam_tras, cam_esq, cam_dir;

        Personagem personagem;
        std::vector<Arvore> arvores;
        int num_arvores;

        Textura chao;

        Luz lanterna;
        Luz natural;

        void desenhaCenario();

    signals:
        void atualizaContador();

    public:
        MeuCanvas(QWidget * parent);

        QTime getTempo();
        void setTempo(QTime tempo);
        bool getPausado();
        void setPausado(bool pausado);
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
