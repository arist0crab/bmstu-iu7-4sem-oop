#include "doors.h"
#include "config.h"

#include <qdebug.h>

ElevatorDoor::ElevatorDoor() : state_(Closed)
{
    QObject::connect(&doorOpeningTimer_, &QTimer::timeout, this, &ElevatorDoor::handleDoorOpened);
    QObject::connect(&doorClosingTimer_, &QTimer::timeout, this, &ElevatorDoor::handleDoorClosed);
    QObject::connect(&doorWaitingTimer_, &QTimer::timeout, this, &ElevatorDoor::handleCloseDoor);
}

void ElevatorDoor::handleDoorOpened()
{
    if (state_ != Opening)
    {
        return;
    }

    state_ = Opened;
    qInfo() << "Двери Открыты";

    doorWaitingTimer_.start(DOOR_WATING_TIME);
}

void ElevatorDoor::handleDoorClosed()
{
    if (state_ != Closing)
    {
        return;
    }

    state_ = Closed;
    qInfo() << "Двери закрыты";

    emit doorClosed();
}

void ElevatorDoor::handleCloseDoor()
{
    if (state_ != Opened)
    {
        return;
    }

    state_ = Closing;

    qInfo() << "Двери закрываются";

    doorClosingTimer_.start(DOOR_CLOSING_TIME);
}

void ElevatorDoor::handleOpenDoor()
{
    if (state_ == Opening || state_ == Opened)
    {
        return;
    }

    auto prevState = state_;
    state_ = Opening;

    qInfo() << "Двери открываются";

    if (prevState == Closed)
    {
        doorOpeningTimer_.start(DOOR_OPENING_TIME);
    }
    else
    {
        doorClosingTimer_.stop();
        qInfo() << "Закрытие прервано";
        qInfo() << "Повторное открытие";
        auto timeToOpen = DOOR_CLOSING_TIME - doorClosingTimer_.remainingTime();
        qInfo() << timeToOpen;
        doorOpeningTimer_.start(timeToOpen);
    }
}
