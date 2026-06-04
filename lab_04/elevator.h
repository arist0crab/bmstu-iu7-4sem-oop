#pragma once

#include "cabin.h"
#include "controller.h"
#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT

    friend class MainWindow;

  public:
    explicit Elevator(QObject* parent = nullptr);

  signals:
    void newFloor(int floor);
  public slots:
    void newRequest(int floor);

  private:
    ElevatorController controller_;
    ElevatorCabin cabin_;
};
