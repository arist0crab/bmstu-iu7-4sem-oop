#pragma once 

#include <QMainWindow>
#include <QList>
#include <QLineEdit>
#include "Elevator.hpp"

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
        void onFloorCallRequested(int floor);

        void onFloorChangedA(int floor);
        void onStateChangedA(ElevatorState state);

        void onFloorChangedB(int floor);
        void onStateChangedB(ElevatorState state);

        void onDoorsStateChangedA(DoorsState state);
        void onDoorsStateChangedB(DoorsState state);

    private:
        Ui::MainWindow *ui;

        Elevator _elevatorA;
        Elevator _elevatorB;

        int _currentFloorA = START_FLOOR;
        int _currentFloorB = START_FLOOR;

        QList<QLineEdit*> _shaftA;
        QList<QLineEdit*> _shaftB;

        void setupConnections();
};