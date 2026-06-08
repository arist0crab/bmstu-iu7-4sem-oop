#include "Cabin.hpp"


Cabin::Cabin(QObject* parent = nullptr) : QObject(parent), _state(CabinState::IDLE), _timer(this)
{
    _timer.setSingleShot(true);

    connect(&_timer, &QTimer::timeout, this, [this]() {
        if (_state == CabinState::MOVE)
            emit floorReached(); 
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
    if (_state == CabinState::MOVE)
        return;

    _state = CabinState::MOVE;
    emit cabinStateChanged(_state);

    _timer.start(MOVE_TIME);
}


void Cabin::stopSlot()
{
    if (_state != CabinState::MOVE)
        return;

    _timer.stop();
    _state = CabinState::WAIT;
    emit cabinStateChanged(_state);
}


void Cabin::freeSlot()
{
    if (_state != CabinState::WAIT)
        return;

    _state = CabinState::IDLE;
    emit cabinStateChanged(_state);
}