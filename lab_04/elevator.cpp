#include "elevator.h"

#include <QPushButton>
#include <qdebug.h>

Elevator::Elevator(QObject* parent) : QObject(parent)
{
    connect(this, &Elevator::newFloor, &controller_, &ElevatorController::handleAddFloor);

    connect(&controller_, &ElevatorController::requestMoveElevator, &cabin_, &ElevatorCabin::handleMoveCabin);
    connect(&controller_, &ElevatorController::requestLockElevator, &cabin_, &ElevatorCabin::handleLockCabin);
    connect(&controller_, &ElevatorController::requestStopElevator, &cabin_, &ElevatorCabin::handleStopCabin);

    connect(&cabin_, &ElevatorCabin::cabinUnlocked, &controller_, &ElevatorController::handleStatusElevator);
    connect(&cabin_.floorTimerPass_, &QTimer::timeout, &controller_, &ElevatorController::handleMoveElevator);
}

void Elevator::newRequest(int floor)
{
    qInfo() << "Вызов на этаж № " << floor << '\n';
    emit newFloor(floor);
}
