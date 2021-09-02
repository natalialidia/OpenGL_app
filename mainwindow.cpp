#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    countdown = new QTimer(this);
    connect(countdown, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    countdown->start(1000);

    ui->lcd_countdown->display(ui->canvas->getTempo().toString("mm:ss"));

    std::string str = "ACHE "+std::to_string(ui->canvas->getTotal())+" PAPÉIS!";

    ui->objetivo->setText(QString::fromStdString(str));
    ui->msgFinal->setText("");

    connect(ui->canvas, SIGNAL(atualizaContador()),this,SLOT(updatePaperCounter()));

    ui->canvas->setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->canvas, SLOT(idleGL()));
    timer->start(1000/30);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updatePaperCounter() {
    ui->contador->display(ui->canvas->getPapeisAchados());

    if (ui->canvas->getPapeisAchados() == ui->canvas->getTotal()) {
        ui->msgFinal->setText("Parabéns! Você achou todas as notas!");
        ui->canvas->setPausado(true);
    }
}

void MainWindow::updateCountdown() {
    if (!ui->canvas->getPausado()) {
        ui->canvas->setTempo(ui->canvas->getTempo().addSecs(-1));
        ui->lcd_countdown->display(ui->canvas->getTempo().toString("mm:ss"));

        if (ui->canvas->getTempo() == QTime(0,0,0)) {
            ui->msgFinal->setText("Você perdeu!");
            ui->canvas->setPausado(true);
        }
    }
}

