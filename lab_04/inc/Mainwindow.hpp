#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Controller.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public slots:
        void updateUI();

    private:
        Ui::MainWindow* ui;
        Elevator* elA;
        Elevator* elB;
        Controller* controller;
        QTimer* uiTimer;
        void setupConnections();
};

#endif