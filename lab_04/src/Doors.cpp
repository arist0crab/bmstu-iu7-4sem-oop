#include "Doors.hpp"

Doors::Doors(QObject* parent) : _state(DoorsState::CLOSE), _openTimer(this), _closeTimer(this)
{ 
    _openTimer.setSingleShot(true);
    _closeTimer.setSingleShot(true);

    connect(&_openTimer, &QTimer::timeout, this, &Doors::onOpenTimeout);
    connect(&_closeTimer, &QTimer::timeout, this, &Doors::onCloseTimeout);
    
    connect(this, &Doors::openedSignal, this, &Doors::openSlot);
    connect(this, &Doors::closedSignal, this, &Doors::closeSlot);
}

DoorsState Doors::getState() const noexcept
{
    return _state;
}

void Doors::onOpenTimeout()
{
    if (_state == DoorsState::OPENING)
        emit openedSignal();
}

void Doors::onCloseTimeout()
{
    if (_state == DoorsState::CLOSING)
        emit closedSignal();
}

// === слоты ===

void Doors::startOpeningSlot()
{
    if (_state != DoorsState::CLOSE && _state != DoorsState::CLOSING)
        return;

    _state = DoorsState::OPENING;
    emit doorsStateChanged(_state);

    _closeTimer.stop();
    _openTimer.start(DOOR_TIME);
}

void Doors::openSlot()
{
    if (_state != DoorsState::OPENING)
        return;

    _state = DoorsState::OPEN;
    emit doorsStateChanged(_state);
}

void Doors::startClosingSlot()
{
    if (_state != DoorsState::OPEN)
        return;

    _state = DoorsState::CLOSING;
    emit doorsStateChanged(_state);

    _openTimer.stop();
    _closeTimer.start(DOOR_TIME);
}

void Doors::closeSlot()
{
    if (_state != DoorsState::CLOSING)
        return;

    _state = DoorsState::CLOSE;
    emit doorsStateChanged(_state);
}