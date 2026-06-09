#pragma once

#include "data.hpp"
#include "Doors.hpp"
#include <QObject>
#include <QTimer>

enum class CabinState
{
    IDLE,
    MOVE,
    WAIT
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

        void floorReached();
        void doorsOpened();
        void doorsClosed();

    public slots:
        void moveSlot();
        void stopSlot();
        void freeSlot();

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