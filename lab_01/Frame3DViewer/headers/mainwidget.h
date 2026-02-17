#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "status.h"
#include <QWidget>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

    private:
        Ui::MainWidget *ui; 

    private slots:
        // обработка нажатий на кнопки
        status_t ButtonLoadFile_clicked();
        status_t ButtonOpenDescrioption_clicked();
};

#endif