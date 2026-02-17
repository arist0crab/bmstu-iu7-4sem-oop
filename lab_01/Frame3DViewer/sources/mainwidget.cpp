#include <iostream>  // TODO
using namespace std;  // TODO
#include "description.h"  // TODO 
#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
   ui->setupUi(this);

   connect(ui->ButtonLoadFile, &QPushButton::clicked, this, &MainWidget::ButtonLoadFile_clicked);
   connect(ui->ButtonOpenDescrioption, &QPushButton::clicked, this, &MainWidget::ButtonOpenDescrioption_clicked);
}

MainWidget::~MainWidget()
{
   delete ui;
}

// обработка нажатий на кнопки

status_t MainWidget::ButtonLoadFile_clicked()
{
   QString path = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Text files (*.txt)");
   cout << path.toUtf8().data() << endl;
   // TODO 

   return SUCCESS;
}

status_t MainWidget::ButtonOpenDescrioption_clicked()
{
   QMessageBox::information(this, Description::TITLE,  Description::ABOUT_PROGRAM);

   return SUCCESS;
}