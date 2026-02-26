#include <QtWidgets>
#include "figure.h"
#include "mainwidget.h"
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    w.show();

    return a.exec();
}