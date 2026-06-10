#include "Controller.hpp"


Controller::Controller(Cabin &cabin, QObject* parent) : QObject(parent), _cabin(cabin), _state(ControllerState::IDLE), _direction(Direction::NONE), _curfloor(START_FLOOR), _targetFloor(START_FLOOR)
{
    connect(&_cabin, &Cabin::cabinFloorReached, this, &Controller::floorReached);
    connect(&_cabin, &Cabin::cabinDoorsClosed, this, &Controller::doorsClosed);
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
    _state = ControllerState::ROUTING;

    if (_queue.isEmpty()) 
    {
        idleSlot();
        return;
    }

    _targetFloor = _queue.first();
    _direction = (_targetFloor > _curfloor) ? Direction::UP : Direction::DOWN;

    waitingCabinSlot();
}

void Controller::waitingCabinSlot()
{
    _state = ControllerState::WAITING_CABIN;
    _cabin.moveSlot();
}

void Controller::waitingDoorsSlot()
{
    _state = ControllerState::WAITING_DOORS;
    _cabin.serveSlot();
}

void Controller::doorsClosed()
{
    if (_state != ControllerState::WAITING_DOORS) 
        return;

    if (!_queue.isEmpty()) 
    {
        int currentFloor = _queue.first();
        _queue.removeFirst();
        emit floorServicedSignal(currentFloor);
    }
        
    routingSlot();
}

void Controller::floorReached()
{
    if (_state != ControllerState::WAITING_CABIN) 
        return;

    _curfloor += _direction;
    emit controllerFloorChanged(_curfloor); 

    if (_curfloor != _targetFloor)
        _cabin.moveSlot();
    else
        waitingDoorsSlot();
}