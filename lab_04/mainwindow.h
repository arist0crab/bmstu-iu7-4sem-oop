#pragma once
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QVBoxLayout>

#include "elevator.h"

class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void onFloorPassed(int floor, int elevatorIndex);
    void onButtonPressed(int floor);
    void onFloorButtonPressed(int floor);

  private:
    void generateUI();
    Elevator* pickElevatorFor(int floor);

    Ui::MainWindow* ui;

    QMap<int, QPushButton*> elevatorButtons;
    Elevator elevator_;
    Elevator elevator2_;

    QLabel* labelElevator1Floor_{nullptr};
    QLabel* labelElevator2Floor_{nullptr};
};
