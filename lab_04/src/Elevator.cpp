#include "Elevator.hpp"

Elevator::Elevator(QObject* parent) : QObject(parent), _cabin(this), _controller(_cabin, this) , _state(ElevatorState::IDLE)
{
    connect(&_controller, &Controller::floorChanged, this, &Elevator::floorChanged);
    connect(&_cabin, &Cabin::doorsStateChanged, this, &Elevator::doorsStateChangedSignal);
}


ElevatorState Elevator::getState() const noexcept
{
    return _state;
}

size_t Elevator::queueSize() const noexcept
{
    return _controller.queueSize();
}

void Elevator::sendCallToController(int floor)
{
    _controller.callReceivedSlot(floor); 
}

// =========================
//           Слоты
// =========================


void Elevator::busySlot()
{
    if (_state == ElevatorState::BUSY)  
        return;

    _state = ElevatorState::BUSY;
    emit elevatorStateChanged(_state);
}


void Elevator::idleSlot()
{
    if (_state == ElevatorState::IDLE)  
        return;

    _state = ElevatorState::IDLE;
    emit elevatorStateChanged(_state);
}