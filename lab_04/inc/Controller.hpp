#pragma once

#include "data.hpp"
#include "Cabin.hpp"
#include <QObject>
#include <QList>

enum class ControllerState
{
    IDLE,
    ROUTING,
    WAITING_CABIN,
    WAITING_DOORS
};


class Controller : public QObject
{
    Q_OBJECT

    public:
        explicit Controller(Cabin &cabin, QObject* parent = nullptr);
        ~Controller() override = default;

        ControllerState getState() const noexcept;

    signals:
        void floorServicedSignal(int floor);
        void routeNextTargetSignal();

    public slots:
        void callReceivedSlot(int floor);
        void doorsStateChangedSlot(DoorsState state);
        void routeNextTargetSlot();
        void floorReachedSlot();

    private:
        Cabin &_cabin;
        ControllerState _state;
        QList<int> _queue;
        Direction _direction;
        int _curfloor;
        int _targetFloor;
};