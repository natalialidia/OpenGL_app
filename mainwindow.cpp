#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

//    papeisAchados = 0;

//    connect(ui->canvas, SIGNAL(atualizaContador()),this,SLOT(updatePaperCounter()));

    ui->canvas->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::updatePaperCounter() {
//    papeisAchados++;
//    ui->contador->display(papeisAchados);
//}

