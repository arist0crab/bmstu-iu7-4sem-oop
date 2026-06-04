#include "Controller.hpp"
#include <cmath>

Controller::Controller(Elevator* e1, Elevator* e2, QObject* parent) : QObject(parent), state(ControllerState::IDLE), el1(e1), el2(e2)
{
}

ControllerState Controller::getState() const
{
    return state;
}

void Controller::onCallReceived(int f, int d)
{
    queue.push_back({f, d});
    if (state == ControllerState::IDLE)
    {
        state = ControllerState::ROUTING;
        calculateRoute();
    }
}

void Controller::onElevatorStateChanged(int id, CabinState s)
{
}

void Controller::onDoorStateChanged(int id, DoorState s)
{
    if (state == ControllerState::WAITING_DOORS && s == DoorState::CLOSED)
    {
        if (queue.empty())
            state = ControllerState::IDLE;
        else
        {
            state = ControllerState::ROUTING;
            calculateRoute();
        }
    }
}

void Controller::onFloorPassed(int id, int f)
{
    Elevator* el = (id == 1) ? el1 : el2;
    if (state == ControllerState::WAITING_CABIN && f == el->getTarget())
    {
        el->getCabin()->stop();
        state = ControllerState::WAITING_DOORS;
    }
}

void Controller::calculateRoute()
{
    if (queue.empty())
        return;
    Call c = queue.front();
    queue.erase(queue.begin());
    int d1 = std::abs(el1->getCabin()->getFloor() - c.floor);
    int d2 = std::abs(el2->getCabin()->getFloor() - c.floor);
    Elevator* best = (d1 <= d2 && el1->getCabin()->getState() == CabinState::IDLE) ? el1 : el2;
    if (best->getCabin()->getState() != CabinState::IDLE)
        best = (el1->getCabin()->getState() == CabinState::IDLE) ? el1 : el2;
    best->assignTarget(c.floor);
    if (best->getCabin()->getFloor() == c.floor)
    {
        best->getCabin()->getDoors()->onOpenRequest();
        state = ControllerState::WAITING_DOORS;
    }
    else
    {
        if (best->getCabin()->getFloor() < c.floor)
            best->getCabin()->moveUp();
        else
            best->getCabin()->moveDown();
        state = ControllerState::WAITING_CABIN;
    }
}