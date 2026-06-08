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

        void openDoorsSignal();
        void closeDoorsSignal();

    public slots:
        void moveSlot();  // MOVE
        void stopSlot();  // WAIT
        void freeSlot();  // IDLE

    private:
        Doors _doors;
        QTimer _timer;
        CabinState _state;
};