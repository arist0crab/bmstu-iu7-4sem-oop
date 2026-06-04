#include "cabin.h"
#include "config.h"

#include <qdebug.h>

ElevatorCabin::ElevatorCabin(QObject* parent) : QObject(parent), state_(Unlocked)
{
    floorTimerPass_.setSingleShot(true);

    connect(this, &ElevatorCabin::requestOpenDoor, &door_, &ElevatorDoor::handleOpenDoor);
    connect(this, &ElevatorCabin::requestLockCabin, this, &ElevatorCabin::handleLockCabin);
    connect(&door_, &ElevatorDoor::doorClosed, this, &ElevatorCabin::handleUnlockCabin);
}

void ElevatorCabin::handleUnlockCabin()
{
    if (state_ != Locked)
    {
        return;
    }

    state_ = Unlocked;
    qInfo() << "Движение кабины разблокировано\n";

    emit cabinUnlocked();
}

void ElevatorCabin::handleLockCabin()
{
    if (state_ != Stopped)
    {
        return;
    }

    state_ = Locked;

    qInfo() << "Движение кабины заблокировано";

    emit requestOpenDoor();
}

void ElevatorCabin::handleMoveCabin()
{
    if (state_ == Locked || state_ == Stopped)
    {
        return;
    }

    auto prevState = state_;
    state_ = Moving;

    if (prevState != Moving)
    {
        qInfo() << "Кабина начала движение";
    }

    floorTimerPass_.start(ONE_FLOOR_MOVING_TIME);
}

void ElevatorCabin::handleStopCabin()
{
    if (state_ == Locked)
    {
        return;
    }
    state_ = Stopped;

    qInfo() << "Кабина остановилась";
    emit requestLockCabin();
}
