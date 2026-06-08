#include "Controller.hpp"


Controller::Controller(Cabin &cabin, QObject* parent) : QObject(parent), _cabin(cabin), _state(ControllerState::IDLE), _direction(Direction::NONE), _curfloor(START_FLOOR), _targetFloor(START_FLOOR)
{
    connect(&_cabin, &Cabin::floorReached, this, &Controller::floorReachedSlot);
    connect(&_cabin, &Cabin::doorsStateChanged, this, &Controller::doorsStateChangedSlot);
    connect(this, &Controller::routeNextTargetSignal, this, &Controller::routeNextTargetSlot, Qt::QueuedConnection);
}


ControllerState Controller::getState() const noexcept
{
    return _state;
}

size_t Controller::queueSize() const noexcept
{   
    return _queue.size();
}


// =========================
//           Слоты
// =========================


void Controller::callReceivedSlot(int floor)
{
    if (_curfloor == floor && _state == ControllerState::IDLE)
    {
        _state = ControllerState::WAITING_DOORS;
        _cabin.stopSlot();
        return; 
    }

    if (!_queue.contains(floor))
        _queue.append(floor);

    if (_state == ControllerState::IDLE)
    {
        _state = ControllerState::ROUTING;
        emit routeNextTargetSignal();
    }
}


void Controller::doorsStateChangedSlot(DoorsState state)
{
    if (_state != ControllerState::WAITING_DOORS) 
        return;

    if (state == DoorsState::CLOSE) 
    {
        if (!_queue.isEmpty()) 
        {
            int currentFloor = _queue.first();
            _queue.removeFirst();
            emit floorServicedSignal(currentFloor);
        }
            
        _cabin.freeSlot(); 

        _state = ControllerState::ROUTING;
        emit routeNextTargetSignal();
    }
}


void Controller::routeNextTargetSlot()
{
    if (_state != ControllerState::ROUTING) 
        return;

    if (_queue.isEmpty()) 
    {
        _state = ControllerState::IDLE;
        _direction = Direction::NONE;
        return;
    }

    _targetFloor = _queue.first();
    _direction = (_targetFloor > _curfloor) ? Direction::UP : Direction::DOWN;

    _state = ControllerState::WAITING_CABIN;
    _cabin.moveSlot();
}


void Controller::floorReachedSlot()
{
    if (_state != ControllerState::WAITING_CABIN) 
        return;

    _curfloor += _direction;

    emit floorChanged(_curfloor); 

    if (_curfloor == _targetFloor)
    {
        _state = ControllerState::WAITING_DOORS;
        _cabin.stopSlot(); 
    }
    else
    {
        _cabin.moveSlot(); 
    }
}