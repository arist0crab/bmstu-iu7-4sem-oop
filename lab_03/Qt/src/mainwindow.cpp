#include "mainwindow.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // TODO
}


MainWindow::~MainWindow() 
{ 
    delete ui; 
}


void MainWindow::on_setCenterButton_clicked()
{
  // TODO
}

void MainWindow::on_moveFigureButton_clicked()
{
  // TODO
}

void MainWindow::on_scaleFigureButton_clicked()
{
  // TODO
}

void MainWindow::on_rotateFigureButton_clicked()
{
  // TODO
}

void MainWindow::on_loadFigureButton_clicked()
{
  // TODO
}

void MainWindow::on_loadCameraButton_clicked()
{
  // TODO
}

void MainWindow::on_removeButton_clicked()
{
  // TODO
}
