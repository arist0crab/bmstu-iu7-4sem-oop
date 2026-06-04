#include "Cabin.hpp"

Cabin::Cabin(QObject* parent) : QObject(parent), state(CabinState::IDLE), floor(1)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &Cabin::onMoveTimeout);
}

CabinState Cabin::getState() const
{
    return state;
}

int Cabin::getFloor() const
{
    return floor;
}

void Cabin::moveUp()
{
    if (state == CabinState::IDLE)
    {
        state = CabinState::MOVING_UP;
        emit stateChanged(state);
        timer->start(1500);
    }
}

void Cabin::moveDown()
{
    if (state == CabinState::IDLE)
    {
        state = CabinState::MOVING_DOWN;
        emit stateChanged(state);
        timer->start(1500);
    }
}

void Cabin::stop()
{
    if (state != CabinState::IDLE)
    {
        timer->stop();
        state = CabinState::IDLE;
        emit stateChanged(state);
        emit stopped();
    }
}

Doors* Cabin::getDoors()
{
    return &doors;
}

void Cabin::onFloorReached()
{
    emit floorPassed(floor);
}

void Cabin::onMoveTimeout()
{
    if (state == CabinState::MOVING_UP)
        floor++;
    else if (state == CabinState::MOVING_DOWN)
        floor--;
    onFloorReached();
}