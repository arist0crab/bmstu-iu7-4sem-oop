#include "Elevator.hpp"

Elevator::Elevator(int id, QObject* parent) : QObject(parent), id(id), targetFloor(1)
{
    connect(&cabin, &Cabin::stateChanged, [this](CabinState s) { emit cabinStateChanged(this->id, s); });
    connect(cabin.getDoors(), &Doors::stateChanged, [this](DoorState s) { emit doorStateChanged(this->id, s); });
    connect(&cabin, &Cabin::floorPassed, [this](int f) { emit floorPassed(this->id, f); });
    connect(&cabin, &Cabin::stopped, this, &Elevator::onCabinStopped);
    connect(cabin.getDoors(), &Doors::closed, this, &Elevator::onDoorsReady);
}

int Elevator::getId() const
{
    return id;
}

Cabin* Elevator::getCabin()
{
    return &cabin;
}

void Elevator::assignTarget(int f)
{
    targetFloor = f;
}

int Elevator::getTarget() const
{
    return targetFloor;
}

void Elevator::onCabinStopped()
{
    cabin.getDoors()->onOpenRequest();
}

void Elevator::onDoorsReady()
{
}