#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <vector>
#include "Elevator.hpp"

enum class ControllerState
{
    IDLE,
    ROUTING,
    WAITING_CABIN,
    WAITING_DOORS
};

struct Call
{
    int floor;
    int direction;
};

class Controller : public QObject
{
    Q_OBJECT

    public:
        Controller(Elevator* e1, Elevator* e2, QObject* parent = nullptr);
        ControllerState getState() const;

    public slots:
        void onCallReceived(int f, int d);
        void onElevatorStateChanged(int id, CabinState s);
        void onDoorStateChanged(int id, DoorState s);
        void onFloorPassed(int id, int f);

    private:
        ControllerState state;
        Elevator* el1;
        Elevator* el2;
        std::vector<Call> queue;
        void calculateRoute();
};

#endif