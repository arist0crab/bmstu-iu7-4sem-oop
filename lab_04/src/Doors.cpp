#include "Doors.hpp"

Doors::Doors(QObject* parent) : _state(DoorsState::CLOSE), _openTimer(this), _closeTimer(this)
{ 
    _openTimer.setSingleShot(true);
    _closeTimer.setSingleShot(true);

    connect(&_openTimer, &QTimer::timeout, this, &Doors::onOpenTimeout);
    connect(&_closeTimer, &QTimer::timeout, this, &Doors::onCloseTimeout);
    
    connect(this, &Doors::timerOpenedSignal, this, &Doors::openSlot);
    connect(this, &Doors::timerClosedSignal, this, &Doors::closeSlot);
}

DoorsState Doors::getState() const noexcept
{
    return _state;
}

void Doors::onOpenTimeout()
{
    emit timerOpenedSignal();
}

void Doors::onCloseTimeout()
{
    emit timerClosedSignal();
}

// === слоты ===

void Doors::startOpeningSlot()
{
    if (_state != DoorsState::CLOSE && _state != DoorsState::CLOSING)
        return;

    _closeTimer.stop();

    int remainingTime = DOOR_TIME;

    if (_state == DoorsState::CLOSING)
    {
        remainingTime = _closeTimer.remainingTime();
        remainingTime = (remainingTime <= 0) ? DOOR_TIME : remainingTime;
    }

    _openTimer.start(remainingTime);

    _state = DoorsState::OPENING;
    emit doorsStateChanged(_state);
}

void Doors::openSlot()
{
    if (_state != DoorsState::OPENING)
        return;

    _state = DoorsState::OPEN;
    emit doorsStateChanged(_state);
    emit doorsOpenedSignal();
}

void Doors::startClosingSlot()
{
    if (_state != DoorsState::OPEN)
        return;

    _openTimer.stop();
    _closeTimer.start(DOOR_TIME);

    _state = DoorsState::CLOSING;
    emit doorsStateChanged(_state);
}

void Doors::closeSlot()
{
    if (_state != DoorsState::CLOSING)
        return;

    _state = DoorsState::CLOSE;
    emit doorsStateChanged(_state);
    emit doorsClosedSignal();
}