#pragma once

#include "Cabin.hpp"
#include "Controller.hpp"
#include <QObject>


enum class ElevatorState
{
    IDLE,
    BUSY
};


class Elevator : public QObject
{
    Q_OBJECT

    public:
        explicit Elevator(QObject* parent = nullptr);
        ~Elevator() override = default;

        ElevatorState getState() const noexcept;
        void sendCallToController(int floor);

    signals:
        void elevatorStateChanged(ElevatorState state);
        void doorsStateChangedSignal(DoorsState state);
        void floorChanged(int floor);

    public slots:
        void busySlot();
        void idleSlot();

    private:
        Cabin _cabin;
        ElevatorState _state;
        Controller _controller;
};