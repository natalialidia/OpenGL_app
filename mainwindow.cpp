#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {

    ui->setupUi(this);

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

    if (ui->canvas->getPapeisAchados() == ui->canvas->getTotal())
        ui->msgFinal->setText("Parabéns! Você achou todas as notas!");
}

