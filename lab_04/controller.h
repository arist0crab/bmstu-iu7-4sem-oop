#pragma once

#include "cabin.h"
#include "config.h"
#include "doors.h"
#include <QVBoxLayout>
#include <QWidget>
#include <cstddef>

class ElevatorController : public QObject
{
    Q_OBJECT

    enum ControllerState
    {
        Waiting,
        HandlingTask,
        HandlingMove,
        HandlingArrival,
    };

    public:
        enum Direction
        {
            Down = -1,
            Stop = 0,
            Up = 1,
        };

      explicit ElevatorController(QObject* parent = nullptr);

      int currentFloor() const noexcept { return currentFloor_; }
      bool isIdle() const noexcept { return state_ == Waiting && queueFloors_.empty(); }
      std::size_t queueSize() const noexcept { return queueFloors_.size(); }

    signals:
        void requestMoveElevator();
        void requestLockElevator();

        void requestStopElevator();
        void noTask();
        void targetFloorReached();
        void noTargetFloorReached();

        void onFloor(int floor);
        void floorButtonPressed(int floor);

    public slots:
        void handleAddFloor(int floor);
        void handleStatusElevator();
        void handleMoveElevator();
        void handleArrival();
        void handleWait();

    private:
        Direction determineDirection();
        void queueAddFloor(int);

        std::list<int> queueFloors_;
        Direction direction;

        ControllerState state_;

        QTimer doorWaitTimer_;
        int currentFloor_;
};
