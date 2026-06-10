#include "Controller.hpp"


Controller::Controller(Cabin &cabin, QObject* parent) : QObject(parent), _cabin(cabin), _state(ControllerState::IDLE), _direction(Direction::NONE), _curfloor(START_FLOOR), _targetFloor(START_FLOOR)
{
    connect(&_cabin, &Cabin::cabinFloorReached, this, &Controller::waitingCabinSlot);
    connect(&_cabin, &Cabin::cabinDoorsClosed, this, &Controller::routingSlot);
}

ControllerState Controller::getState() const noexcept
{
    return _state;
}

size_t Controller::queueSize() const noexcept
{   
    return _queue.size();
}

void Controller::callReceived(int floor)
{
    if (_curfloor == floor && _state == ControllerState::IDLE)
    {
        waitingDoorsSlot();
        return;
    }

    if (!_queue.contains(floor))
        _queue.append(floor);

    if (_state == ControllerState::IDLE)
        routingSlot();
}

// === слоты ===

void Controller::idleSlot()
{
    _state = ControllerState::IDLE;
    _direction = Direction::NONE;
}

void Controller::routingSlot()
{
    if (!canStartRouting())
        return;

    if (_queue.isEmpty())
    {
        idleSlot();
        return;
    }

    _state = ControllerState::ROUTING;
    
    _targetFloor = _queue.first();
    _direction = (_targetFloor > _curfloor) ? Direction::UP : Direction::DOWN;

    waitingCabinSlot();
}

void Controller::waitingCabinSlot()
{
    if (!canContinueMovement())
        return;

    _state = ControllerState::WAITING_CABIN;
    _curfloor += _direction;
    emit controllerFloorChanged(_curfloor);

    if (_curfloor != _targetFloor)
        _cabin.moveSlot();
    else 
        waitingDoorsSlot();
}

void Controller::waitingDoorsSlot()
{
    _state = ControllerState::WAITING_DOORS;
    removeCurrentFloorFromQueue();
    _cabin.serveSlot();
}

// === приватные методы ===

void Controller::removeCurrentFloorFromQueue()
{
    if (_queue.empty() || !_queue.contains(_curfloor))
        return;
    
    _queue.removeFirst();
    emit floorServicedSignal(_curfloor);
}

bool Controller::canStartRouting() const
{
    return _state == ControllerState::IDLE || _state == ControllerState::WAITING_DOORS;
}

bool Controller::canContinueMovement() const
{
    return _state == ControllerState::ROUTING || _state == ControllerState::WAITING_CABIN;
}