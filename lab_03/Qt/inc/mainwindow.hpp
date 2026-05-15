#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <QMainWindow>
#include <QApplication>
#include <QGraphicsScene>
#include <memory>
#include <vector>
#include <QFileDialog>

#include "Facade.hpp"
#include "Vertex.hpp"
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    private slots:
        void on_setCenterButton_clicked();
        void on_moveFigureButton_clicked();
        void on_scaleFigureButton_clicked();
        void on_rotateFigureButton_clicked();
        void on_loadFigureButton_clicked();
        void on_loadCameraButton_clicked();
        void on_deleteObjectButton_clicked();

    private:
        Ui::MainWindow *ui;
        Facade m_facade;

        std::vector<size_t> m_selected;
        size_t m_activeCamId;

        void drawScene();
        void getSelectedObjects();
        void createScene(QWidget *parent);
        void addModelToTable(const QString &filename);
        void insertRow(size_t id, const std::string &name, const Vertex &center, const std::string &type);

};

#endif