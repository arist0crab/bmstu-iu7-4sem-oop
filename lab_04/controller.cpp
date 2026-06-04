#include <QLabel>
#include <QPushButton>
#include <qdebug.h>

#include "cabin.h"
#include "config.h"
#include "controller.h"

ElevatorController::ElevatorController(QObject* parent)
    : QObject(parent), direction(Stop), state_(Waiting), currentFloor_(FIRST_FLOOR)
{
    connect(this, &ElevatorController::noTask, this, &ElevatorController::handleWait);
    connect(this, &ElevatorController::targetFloorReached, this, &ElevatorController::handleArrival);
    connect(this, &ElevatorController::noTargetFloorReached, this, &ElevatorController::handleMoveElevator);
}

void ElevatorController::handleAddFloor(int floor)
{
    state_ = HandlingTask;

    if (floor == currentFloor_)
    {
        emit targetFloorReached();
    }
    else
    {
        if (std::find(queueFloors_.begin(), queueFloors_.end(), floor) == queueFloors_.end())
        {
            emit floorButtonPressed(floor);
            queueAddFloor(floor);
        }
        emit noTargetFloorReached();
    }
}

void ElevatorController::handleStatusElevator()
{
    if (state_ != HandlingArrival && state_ != HandlingMove)
    {
        return;
    }

    state_ = HandlingTask;

    if (queueFloors_.empty())
    {
        emit noTask();
    }

    emit noTargetFloorReached();
}

void ElevatorController::handleMoveElevator()
{
    if (queueFloors_.empty())
    {
        return;
    }

    if (state_ != HandlingTask && state_ != HandlingMove)
    {
        return;
    }

    direction = determineDirection();
    int targetFloor = *queueFloors_.begin();

    auto prevState = state_;
    state_ = HandlingMove;
    if (prevState == HandlingMove)
    {
        currentFloor_ += direction;
        qInfo() << "Лифт на этаже:" << currentFloor_;
        emit onFloor(currentFloor_);
    }
    if (currentFloor_ != targetFloor)
    {
        emit requestMoveElevator();
    }
    else
    {
        queueFloors_.pop_front();
        emit targetFloorReached();
    }
}

void ElevatorController::handleArrival()
{
    if (state_ == Waiting)
    {
        return;
    }

    if (state_ != HandlingMove && state_ != HandlingTask)
    {
        return;
    }

    emit onFloor(currentFloor_);

    auto prevState = state_;
    state_ = HandlingArrival;
    qInfo() << "Лифт приехал на вызываемый этаж\n";

    if (prevState == HandlingMove || direction != Stop)
    {
        emit requestStopElevator();
    }
    else
    {
        emit requestLockElevator();
    }
}

void ElevatorController::handleWait()
{
    if (state_ == Waiting)
    {
        return;
    }

    if (state_ != HandlingTask)
    {
        return;
    }

    state_ = Waiting;
    direction = Stop;
    qInfo() << "Лифт в состоянии ожидания\n\n";
}

void ElevatorController::queueAddFloor(int floor)
{
    if (queueFloors_.empty())
    {
        queueFloors_.push_front(floor);
        return;
    }

    auto first = queueFloors_.begin();
    auto second = ++queueFloors_.begin();
    while (second != queueFloors_.end() && (*second - *first) * direction > 0)
    {
        ++first;
        ++second;
    }
    auto end = second;

    if ((floor - currentFloor_) * direction >= 0)
    {
        auto it = queueFloors_.begin();
        for (; it != end && (floor - *it) * direction > 0; ++it)
            ;
        queueFloors_.insert(it, floor);
    }
    else
    {
        auto it = end;
        for (; it != queueFloors_.end() && (floor - *it) * (-direction) > 0; ++it)
            ;
        queueFloors_.insert(it, floor);
    }
}

ElevatorController::Direction ElevatorController::determineDirection()
{
    if (currentFloor_ > queueFloors_.front())
    {
        return Down;
    }
    else
    {
        return Up;
    }
}
