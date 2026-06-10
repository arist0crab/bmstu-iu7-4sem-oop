#pragma once

#include "data.hpp"
#include "Doors.hpp"
#include <QObject>
#include <QTimer>

enum class CabinState
{
    IDLE,  // покой
    MOVE,  // движение
    SERVE  // обслуживание
};

class Cabin : public QObject
{
    Q_OBJECT

    public:
        explicit Cabin(QObject* parent = nullptr);
        ~Cabin() override = default;

        CabinState getState() const noexcept;

    signals:
        void cabinStateChanged(CabinState state);
        void doorsStateChanged(DoorsState state);

        void cabinFloorReached();
        void cabinDoorsOpened();
        void cabinDoorsClosed();

    public slots:
        void moveSlot();
        void idleSlot();
        void serveSlot();

    private:
        void onMoveTimeout();
        void onWaitTimeout();
        void onDoorsOpened();
        void onDoorsClosed();
        
        Doors _doors;
        QTimer _moveTimer;
        QTimer _waitTimer;
        CabinState _state;
};