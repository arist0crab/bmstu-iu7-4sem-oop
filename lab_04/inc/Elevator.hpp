#pragma once

#include "Cabin.hpp"
#include <QObject>

class Controller;


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

    signals:
        void elevatorStateChanged(ElevatorState state);

    public slots:
        void busySlot();
        void idleSlot();

    private:
        Cabin _cabin;
        ElevatorState _state;
};