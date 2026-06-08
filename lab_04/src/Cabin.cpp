#include "Cabin.hpp"


Cabin::Cabin(QObject* parent) : QObject(parent), _state(CabinState::IDLE), _timer(this)
{
    _timer.setSingleShot(true);

    connect(&_timer, &QTimer::timeout, this, [this]() {
        if (_state == CabinState::MOVE) 
            emit floorReached(); 
        else if (_state == CabinState::WAIT)
            _doors.startClosingSlot();
    });

    connect(&_doors, &Doors::doorsStateChanged, this, [this](DoorsState doorState) {
        if (_state == CabinState::WAIT && doorState == DoorsState::OPEN)
            _timer.start(WAIT_TIME);
        emit doorsStateChanged(doorState);
    });
}


CabinState Cabin::getState() const noexcept
{
    return _state;
}


// =========================
//           Слоты
// =========================


void Cabin::moveSlot()
{
    _state = CabinState::MOVE;
    emit cabinStateChanged(_state);

    _timer.start(MOVE_TIME);
}


void Cabin::stopSlot()
{
    if (_state != CabinState::MOVE && _state != CabinState::IDLE)
        return;

    _timer.stop();
    _state = CabinState::WAIT;
    emit cabinStateChanged(_state);

    _doors.startOpeningSlot();
}


void Cabin::freeSlot()
{
    if (_state != CabinState::WAIT)
        return;

    _state = CabinState::IDLE;
    emit cabinStateChanged(_state);
}