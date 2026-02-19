#include "description.h"
#include "figure.h"
#include "manager.h"
#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(figure_t &figure, QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget), figure(figure)
{
   ui->setupUi(this);

   QGraphicsScene *scene = new QGraphicsScene(this);

   ui->graphicsView->setScene(scene);
   ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
   ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

   connect(ui->ButtonLoadFile, &QPushButton::clicked, this, &MainWidget::ButtonLoadFile_clicked);
   connect(ui->ButtonOpenDescrioption, &QPushButton::clicked, this, &MainWidget::ButtonOpenDescrioption_clicked);
   connect(ui->ButtonMoveFigure, &QPushButton::clicked, this, &MainWidget::ButtonMoveFigure_clicked);

   figure_reset(this->figure);
}

MainWidget::~MainWidget()
{
   delete ui;
}

status_t MainWidget::draw()
{
   status_t sc;
   request_t request;
   QGraphicsScene *scene;
   double scene_width, scene_height;

   auto rcontent = ui->graphicsView->contentsRect();
   ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

   scene = ui->graphicsView->scene();
   scene_width = ui->graphicsView->scene()->width();
   scene_height = ui->graphicsView->scene()->height();

   request.type = DRAW_FIGURE;
   request.scene = { scene, scene_width, scene_height };

   sc = manage_request(request, this->figure);

   return sc;
}

// обработка нажатий на кнопки

status_t MainWidget::ButtonMoveFigure_clicked()
{
   status_t sc;
   request_t request;
   double dx, dy, dz;

   dx = ui->EnterMoveX->value();
   dy = ui->EnterMoveY->value();
   dz = ui->EnterMoveZ->value();

   request.type = MOVE_FIGURE;
   request.move_data = { dx, dy, dz };

   sc = manage_request(request, this->figure);
   if (sc == SUCCESS) sc = draw();

   // TODO add error manager

   return sc;
}

status_t MainWidget::ButtonLoadFile_clicked()
{
   status_t sc = SUCCESS;
   request_t request;
   
   QString path = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Text files (*.txt)");

   request.filename = path.toUtf8().data();
   request.type = LOAD_FIGURE;

   sc = manage_request(request, this->figure);
   if (sc == SUCCESS) sc = draw();

   // TODO add error manager   

   return sc;
}

status_t MainWidget::ButtonOpenDescrioption_clicked()
{
   QMessageBox::information(this, Description::TITLE,  Description::ABOUT_PROGRAM);

   return SUCCESS;
}