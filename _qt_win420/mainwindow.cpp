#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMessageBox msgBox;
    msgBox.setText("privet");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
