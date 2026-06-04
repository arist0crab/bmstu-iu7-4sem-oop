#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <QObject>
#include "Cabin.hpp"

class Elevator : public QObject
{
    Q_OBJECT

    public:
        Elevator(int id, QObject* parent = nullptr);
        int getId() const;
        Cabin* getCabin();
        void assignTarget(int f);
        int getTarget() const;

    signals:
        void cabinStateChanged(int id, CabinState s);
        void doorStateChanged(int id, DoorState s);
        void floorPassed(int id, int f);

    public slots:
        void onCabinStopped();
        void onDoorsReady();

    private:
        int id;
        int targetFloor;
        Cabin cabin;
};

#endif