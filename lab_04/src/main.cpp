#include "mainwindow.hpp"
#include <QMainWindow>
#include <QtWidgets>

int main(int argc, char *argv[]) 
{
  QApplication a(argc, argv);
  MainWindow w;

  w.show();

  return a.exec();
}