#include "Controller.hpp"


Controller::Controller(Cabin &cabin, QObject* parent = nullptr) : QObject(parent), _cabin(cabin), _state(ControllerState::IDLE), _direction(Direction::NONE), _curfloor(START_FLOOR), _targetFloor(START_FLOOR)
{
    // TODO соединить сигналы
}


ControllerState Controller::getState() const noexcept
{
    return _state;
}



// =========================
//           Слоты
// =========================


void Controller::callRecievedSlot(int floor)
{
    if (!_queue.contains(floor) && _curfloor != floor)
        _queue.append(floor);

    if (_state == ControllerState::IDLE)
    {
        _state = ControllerState::ROUTING;
        // TODO вызвать нужный метод
    }
}


void Controller::doorsStateChangedSlot(DoorsState state)
{
    if (_state != ControllerState::WAITING_DOORS) 
        return;

    if (state == DoorsState::OPEN) {}
        // _cabin.getDoors().startOpeningSlot(); TODO начать открывать двери
    else if (state == DoorsState::CLOSE) 
    {
        _queue.removeFirst();
        _cabin.freeSlot();

        _state = ControllerState::ROUTING;
        // TODO
        // QMetaObject::invokeMethod(this, "routeNextTargetSlot", Qt::QueuedConnection);
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

    _curfloor = _targetFloor;
    _state = ControllerState::WAITING_DOORS;

    _cabin.stopSlot();
    // TODO открыть двери
}
