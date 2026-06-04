#ifndef CABIN_HPP
#define CABIN_HPP

#include <QObject>
#include <QTimer>
#include "Doors.hpp"

enum class CabinState
{
    IDLE,
    MOVING_UP,
    MOVING_DOWN
};

class Cabin : public QObject
{
    Q_OBJECT

    public:
        Cabin(QObject* parent = nullptr);
        CabinState getState() const;
        int getFloor() const;
        void moveUp();
        void moveDown();
        void stop();
        Doors* getDoors();

    signals:
        void floorPassed(int f);
        void stopped();
        void stateChanged(CabinState s);

    public slots:
        void onFloorReached();

    private slots:
        void onMoveTimeout();

    private:
        CabinState state;
        int floor;
        Doors doors;
        QTimer* timer;
};

#endif