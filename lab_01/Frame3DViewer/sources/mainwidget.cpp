#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
   ui->setupUi(this);

   QGraphicsScene *scene = new QGraphicsScene(this);

   ui->graphicsView->setScene(scene);
   ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
   ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

   connect(ui->ButtonLoadFile, &QPushButton::clicked, this, &MainWidget::ButtonLoadFile_clicked);
   connect(ui->ButtonOpenDescrioption, &QPushButton::clicked, this, &MainWidget::ButtonOpenDescrioption_clicked);
   connect(ui->ButtonMoveFigure, &QPushButton::clicked, this, &MainWidget::ButtonMoveFigure_clicked);
   connect(ui->ButtonRotateFigure, &QPushButton::clicked, this, &MainWidget::ButtonRotateFigure_clicked);
   connect(ui->ButtonScaleFigure, &QPushButton::clicked, this, &MainWidget::ButtonScaleFigure_clicked);
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

   sc = manage_request(request);

   return sc;
}

// обработка нажатий на кнопки

status_t MainWidget::ButtonScaleFigure_clicked()
{
   status_t sc;
   request_t request;
   double kx, ky, kz;

   kx = ui->EnterScaleX->value();
   ky = ui->EnterScaleY->value();
   kz = ui->EnterScaleZ->value();

   request.type = SCALE_FIGURE;
   request.scale_data = { kx, ky, kz };

   sc = manage_request(request);
   if (sc == SUCCESS) sc = draw();

   show_error_message(sc, this);

   return sc;
}

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

   sc = manage_request(request);
   if (sc == SUCCESS) sc = draw();

   show_error_message(sc, this);

   return sc;
}

status_t MainWidget::ButtonRotateFigure_clicked()
{
   status_t sc;
   request_t request;
   double ax, ay, az;

   ax = ui->EnterRotateX->value();
   ay = ui->EnterRotateY->value();
   az = ui->EnterRotateZ->value();

   request.type = ROTATE_FIGURE;
   request.rotate_data = { ax, ay, az };

   sc = manage_request(request);
   if (sc == SUCCESS) sc = draw();

   show_error_message(sc, this);

   return sc;
}

status_t MainWidget::ButtonLoadFile_clicked()
{
   status_t sc = SUCCESS;
   request_t request;
   
   QString path = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Text files (*.txt)");

   request.type = LOAD_FIGURE;
   request.filename = path.toUtf8().data();

   sc = manage_request(request);
   if (sc == SUCCESS) sc = draw();

   show_error_message(sc, this);

   return sc;
}

status_t MainWidget::ButtonOpenDescrioption_clicked()
{
   show_description_message(this);
   return SUCCESS;
}