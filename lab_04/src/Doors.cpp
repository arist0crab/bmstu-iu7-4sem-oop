#include "Doors.hpp"

Doors::Doors(QObject* parent) : QObject(parent), state(DoorState::CLOSED)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &Doors::onStateTimeout);
}

DoorState Doors::getState() const
{
    return state;
}

void Doors::onOpenRequest()
{
    if (state == DoorState::CLOSED)
    {
        state = DoorState::OPENING;
        emit stateChanged(state);
        timer->start(1000);
    }
}

void Doors::onCloseRequest()
{
    if (state == DoorState::OPEN)
    {
        state = DoorState::CLOSING;
        emit stateChanged(state);
        timer->start(1000);
    }
}

void Doors::onStateTimeout()
{
    if (state == DoorState::OPENING)
    {
        state = DoorState::OPEN;
        emit stateChanged(state);
        emit opened();
        timer->start(2000);
    }
    else if (state == DoorState::OPEN)
    {
        state = DoorState::CLOSING;
        emit stateChanged(state);
        timer->start(1000);
    }
    else if (state == DoorState::CLOSING)
    {
        state = DoorState::CLOSED;
        emit stateChanged(state);
        emit closed();
    }
}