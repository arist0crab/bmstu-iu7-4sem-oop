#include "Controller.hpp"

Controller::Controller(Cabin &cabin, QObject* parent) : QObject(parent), _cabin(cabin), _state(ControllerState::IDLE), _direction(Direction::NONE), _curfloor(START_FLOOR), _targetFloor(START_FLOOR)
{
    connect(&_cabin, &Cabin::floorReached, this, &Controller::floorReached);
    connect(&_cabin, &Cabin::doorsClosed, this, &Controller::doorsClosed);
    
    connect(this, &Controller::moveCabinSignal, &_cabin, &Cabin::moveSlot);
    connect(this, &Controller::stopCabinSignal, &_cabin, &Cabin::stopSlot);
    connect(this, &Controller::freeCabinSignal, &_cabin, &Cabin::freeSlot);
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
    emit moveCabinSignal();
}

void Controller::waitingDoorsSlot()
{
    _state = ControllerState::WAITING_DOORS;
    emit stopCabinSignal();
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
        
    emit freeCabinSignal();
    routingSlot();
}

void Controller::floorReached()
{
    if (_state != ControllerState::WAITING_CABIN) 
        return;

    _curfloor += _direction;
    emit floorChanged(_curfloor); 

    if (_curfloor != _targetFloor)
        emit moveCabinSignal();
    else
        waitingDoorsSlot();
}