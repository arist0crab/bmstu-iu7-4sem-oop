#include "Elevator.hpp"


Elevator::Elevator(QObject* parent) : QObject(parent), _state(ElevatorState::IDLE)
{
    // TODO кабину прикрутить
    // TODO контроллер прикрутить
}


ElevatorState Elevator::getState() const noexcept
{
    return _state;
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

