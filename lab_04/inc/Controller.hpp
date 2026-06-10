#pragma once

#include "data.hpp"
#include "Cabin.hpp"
#include <QObject>
#include <QList>

enum class ControllerState
{
    IDLE,  // состояние покоя
    ROUTING,  // маршрутизация
    WAITING_CABIN,  // процесс кабины
    WAITING_DOORS  // процесс дверей
};

class Controller : public QObject
{
    Q_OBJECT

    public:
        explicit Controller(Cabin &cabin, QObject* parent = nullptr);
        ~Controller() override = default;

        ControllerState getState() const noexcept;
        size_t queueSize() const noexcept;

        void callReceived(int floor);
        void floorReached();
        void doorsClosed();

    signals:
        void floorServicedSignal(int floor);
        void controllerFloorChanged(int floor);
        
        void moveCabinSignal();
        void stopCabinSignal();
        void freeCabinSignal();

    public slots:
        void idleSlot();
        void routingSlot();
        void waitingCabinSlot();
        void waitingDoorsSlot();

    private:
        void removeCurrentFloorFromQueue();
        bool canStartRouting() const;
        bool canContinueMovement() const;

        Cabin &_cabin;
        ControllerState _state;
        QList<int> _queue;
        Direction _direction;
        int _curfloor;
        int _targetFloor;
};