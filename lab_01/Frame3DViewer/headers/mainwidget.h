#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include "status.h"
#include "figure.h"
#include "manager.h"
#include <QWidget>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

        status_t draw();

    private:
        Ui::MainWidget *ui; 

    private slots:
        status_t ButtonLoadFile_clicked();
        status_t ButtonMoveFigure_clicked();
        status_t ButtonScaleFigure_clicked();
        status_t ButtonRotateFigure_clicked();
        status_t ButtonOpenDescrioption_clicked();
};

#endif